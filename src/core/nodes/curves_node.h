#ifndef CURVES_NODE_H
#define CURVES_NODE_H

#include "node_base.h"
#include <QString>
#include <QVector>
#include <QPointF>

/**
 * @class CurvesNode
 * @brief Professional curves adjustment node
 * Similar to Nuke Curves, Blender Color Curves, Photoshop Curves
 */
class CurvesNode : public NodeBase
{
public:
    enum CurveMode {
        RGB,
        RED,
        GREEN,
        BLUE,
        ALPHA,
        LUMINANCE
    };

    CurvesNode(const QString& name = "Curves");
    virtual ~CurvesNode();

    // Curve point management
    void addCurvePoint(CurveMode mode, float x, float y);
    void removeCurvePoint(CurveMode mode, int index);
    void updateCurvePoint(CurveMode mode, int index, float x, float y);
    void resetCurve(CurveMode mode);

    // Preset curves
    void applyCinematicCurve();
    void applyLinearCurve();
    void applyInverseCurve();

    // Interpolation
    void setCurveInterpolation(const QString& type);  // linear, bezier, smooth

protected:
    bool processImage(cv::Mat& output, int frame) override;

private:
    float evaluateCurve(CurveMode mode, float input);
    float interpolateCurve(const QVector<QPointF>& points, float x);
    float bezierInterpolate(QPointF p0, QPointF p1, QPointF p2, QPointF p3, float t);

    QMap<int, QVector<QPointF>> m_curves;  // mode -> points
    QString m_interpolationType;
};

#endif // CURVES_NODE_H
