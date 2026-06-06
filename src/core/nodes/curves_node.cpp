#include "curves_node.h"
#include <cmath>
#include <algorithm>

CurvesNode::CurvesNode(const QString& name)
    : NodeBase(NodeType::CUSTOM, name)
{
    addInput("input", 4);
    addOutput("output", 4);

    setProperty("interpolation", "bezier");

    // Initialize default linear curves
    for (int i = RGB; i <= LUMINANCE; i++)
    {
        QVector<QPointF> curve;
        curve.append(QPointF(0.0f, 0.0f));
        curve.append(QPointF(1.0f, 1.0f));
        m_curves[i] = curve;
    }

    m_interpolationType = "bezier";
}

CurvesNode::~CurvesNode()
{
}

void CurvesNode::addCurvePoint(CurveMode mode, float x, float y)
{
    if (m_curves.contains(mode))
    {
        QVector<QPointF>& curve = m_curves[mode];
        curve.append(QPointF(x, y));
        
        // Sort by x coordinate
        std::sort(curve.begin(), curve.end(),
                  [](const QPointF& a, const QPointF& b) { return a.x() < b.x(); });
        
        markDirty();
    }
}

void CurvesNode::removeCurvePoint(CurveMode mode, int index)
{
    if (m_curves.contains(mode) && index >= 0 && index < m_curves[mode].size())
    {
        // Don't remove endpoints
        if (index > 0 && index < m_curves[mode].size() - 1)
        {
            m_curves[mode].removeAt(index);
            markDirty();
        }
    }
}

void CurvesNode::updateCurvePoint(CurveMode mode, int index, float x, float y)
{
    if (m_curves.contains(mode) && index >= 0 && index < m_curves[mode].size())
    {
        m_curves[mode][index] = QPointF(x, y);
        
        // Sort again
        std::sort(m_curves[mode].begin(), m_curves[mode].end(),
                  [](const QPointF& a, const QPointF& b) { return a.x() < b.x(); });
        
        markDirty();
    }
}

void CurvesNode::resetCurve(CurveMode mode)
{
    if (m_curves.contains(mode))
    {
        QVector<QPointF> curve;
        curve.append(QPointF(0.0f, 0.0f));
        curve.append(QPointF(1.0f, 1.0f));
        m_curves[mode] = curve;
        markDirty();
    }
}

void CurvesNode::applyCinematicCurve()
{
    // Typical cinematic S-curve
    resetCurve(RGB);
    addCurvePoint(RGB, 0.2f, 0.1f);
    addCurvePoint(RGB, 0.5f, 0.5f);
    addCurvePoint(RGB, 0.8f, 0.9f);
}

void CurvesNode::applyLinearCurve()
{
    for (int i = RGB; i <= LUMINANCE; i++)
    {
        resetCurve(static_cast<CurveMode>(i));
    }
}

void CurvesNode::applyInverseCurve()
{
    resetCurve(RGB);
    addCurvePoint(RGB, 0.5f, 0.5f);
    m_curves[RGB][1] = QPointF(1.0f, 0.0f);
    m_curves[RGB][0] = QPointF(0.0f, 1.0f);
}

void CurvesNode::setCurveInterpolation(const QString& type)
{
    m_interpolationType = type;
}

bool CurvesNode::processImage(cv::Mat& output, int frame)
{
    cv::Mat input = getInputImage(0, frame);
    if (input.empty())
    {
        return false;
    }

    output = input.clone();

    for (int y = 0; y < output.rows; y++)
    {
        for (int x = 0; x < output.cols; x++)
        {
            cv::Vec4f pixel = output.at<cv::Vec4f>(y, x);

            // Apply RGB curve
            float r = evaluateCurve(RGB, pixel[0]);
            float g = evaluateCurve(RGB, pixel[1]);
            float b = evaluateCurve(RGB, pixel[2]);

            pixel[0] = r;
            pixel[1] = g;
            pixel[2] = b;

            output.at<cv::Vec4f>(y, x) = pixel;
        }
    }

    return true;
}

float CurvesNode::evaluateCurve(CurveMode mode, float input)
{
    if (!m_curves.contains(mode))
        return input;

    return interpolateCurve(m_curves[mode], input);
}

float CurvesNode::interpolateCurve(const QVector<QPointF>& points, float x)
{
    if (points.isEmpty())
        return x;

    // Clamp input
    x = std::max(0.0f, std::min(1.0f, x));

    // Find surrounding points
    int i = 0;
    while (i < points.size() - 1 && points[i + 1].x() < x)
    {
        i++;
    }

    QPointF p0 = points[i];
    QPointF p1 = (i + 1 < points.size()) ? points[i + 1] : p0;

    if (p0.x() == p1.x())
        return p0.y();

    // Linear interpolation
    float t = (x - p0.x()) / (p1.x() - p0.x());
    return p0.y() + t * (p1.y() - p0.y());
}

float CurvesNode::bezierInterpolate(QPointF p0, QPointF p1, QPointF p2, QPointF p3, float t)
{
    float mt = 1.0f - t;
    float mt2 = mt * mt;
    float mt3 = mt2 * mt;
    float t2 = t * t;
    float t3 = t2 * t;

    float x = mt3 * p0.x() + 3.0f * mt2 * t * p1.x() + 3.0f * mt * t2 * p2.x() + t3 * p3.x();
    float y = mt3 * p0.y() + 3.0f * mt2 * t * p1.y() + 3.0f * mt * t2 * p2.y() + t3 * p3.y();

    return y;
}
