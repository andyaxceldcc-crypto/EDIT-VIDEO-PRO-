#include "roto_node.h"
#include <opencv2/imgproc.hpp>

RotoNode::RotoNode(const QString& name)
    : NodeBase(NodeType::ROTO, name)
{
    addInput("input", 4);
    addOutput("matte", 1);
    addOutput("output", 4);
}

RotoNode::~RotoNode()
{
}

void RotoNode::addShape(const QString& name)
{
    if (!m_shapes.contains(name))
    {
        m_shapes[name] = QVector<RotoPoint>();
        markDirty();
    }
}

void RotoNode::removeShape(const QString& name)
{
    if (m_shapes.contains(name))
    {
        m_shapes.remove(name);
        markDirty();
    }
}

void RotoNode::addPoint(const QString& shapeName, float x, float y)
{
    if (m_shapes.contains(shapeName))
    {
        RotoPoint point = {x, y, x, y, x, y, false};
        m_shapes[shapeName].append(point);
        markDirty();
    }
}

void RotoNode::removePoint(const QString& shapeName, int index)
{
    if (m_shapes.contains(shapeName))
    {
        if (index >= 0 && index < m_shapes[shapeName].size())
        {
            m_shapes[shapeName].removeAt(index);
            markDirty();
        }
    }
}

void RotoNode::updatePoint(const QString& shapeName, int index, float x, float y)
{
    if (m_shapes.contains(shapeName))
    {
        if (index >= 0 && index < m_shapes[shapeName].size())
        {
            m_shapes[shapeName][index].x = x;
            m_shapes[shapeName][index].y = y;
            markDirty();
        }
    }
}

void RotoNode::setKeyframe(const QString& shapeName, int frame)
{
    // Keyframe management
    markDirty();
}

bool RotoNode::processImage(cv::Mat& output, int frame)
{
    cv::Mat input = getInputImage(0, frame);
    if (input.empty())
    {
        return false;
    }

    output = input.clone();
    return true;
}
