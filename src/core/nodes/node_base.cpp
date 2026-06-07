#include "node_base.h"
#include <QRectF>
#include <QDebug>

NodeBase::NodeBase(NodeType type, const QString& name)
    : m_name(name.isEmpty() ? "Node" : name)
    , m_type(type)
    , m_position(0, 0)
    , m_selected(false)
    , m_bypassed(false)
    , m_cacheEnabled(true)
{
}

NodeBase::~NodeBase()
{
}

QString NodeBase::getTypeName() const
{
    switch (m_type) {
        case Read: return "Read";
        case Write: return "Write";
        case Viewer: return "Viewer";
        case Grade: return "Grade";
        case Merge: return "Merge";
        case Transform: return "Transform";
        case Blur: return "Blur";
        case ColorCorrect: return "ColorCorrect";
        case Keyer: return "Keyer";
        case Roto: return "Roto";
        case Tracker: return "Tracker";
        default: return "Other";
    }
}

QRectF NodeBase::getRect() const
{
    const qreal width = 140;
    const qreal height = 80;
    return QRectF(m_position.x() - width / 2, m_position.y() - height / 2, width, height);
}

QRectF NodeBase::getInputPortRect(int index) const
{
    const qreal portSize = 12;
    QRectF nodeRect = getRect();
    qreal y = nodeRect.top() + 20 + index * 20;
    return QRectF(nodeRect.left() - portSize / 2, y - portSize / 2, portSize, portSize);
}

QRectF NodeBase::getOutputPortRect(int index) const
{
    const qreal portSize = 12;
    QRectF nodeRect = getRect();
    qreal y = nodeRect.top() + 20 + index * 20;
    return QRectF(nodeRect.right() - portSize / 2, y - portSize / 2, portSize, portSize);
}

void NodeBase::setProperty(const QString& name, const QVariant& value)
{
    m_properties[name] = value;
}

QVariant NodeBase::getProperty(const QString& name) const
{
    return m_properties.value(name);
}

void NodeBase::addInput(const QString& name, int channels)
{
    Q_UNUSED(channels);
    m_inputs.append(name);
}

void NodeBase::addOutput(const QString& name, int channels)
{
    Q_UNUSED(channels);
    m_outputs.append(name);
}

bool NodeBase::processImage(cv::Mat& output, int frame)
{
    Q_UNUSED(output);
    Q_UNUSED(frame);
    return true;
}

cv::Mat NodeBase::getInputImage(int index, int frame)
{
    Q_UNUSED(index);
    Q_UNUSED(frame);
    return cv::Mat();
}

void NodeBase::clearCache()
{
    m_frameCache.clear();
}