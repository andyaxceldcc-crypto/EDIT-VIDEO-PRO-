#include "node_connection.h"
#include "node_base.h"

NodeConnection::NodeConnection(NodeBase* sourceNode, int sourcePort,
                               NodeBase* destNode, int destPort,
                               QObject* parent)
    : QObject(parent)
    , m_sourceNode(sourceNode)
    , m_destNode(destNode)
    , m_sourcePort(sourcePort)
    , m_destPort(destPort)
    , m_selected(false)
{
}

NodeConnection::~NodeConnection()
{
}

QPointF NodeConnection::getSourcePoint() const
{
    if (m_sourceNode) {
        return m_sourceNode->getOutputPortRect(m_sourcePort).center();
    }
    return QPointF();
}

QPointF NodeConnection::getDestPoint() const
{
    if (m_destNode) {
        return m_destNode->getInputPortRect(m_destPort).center();
    }
    return QPointF();
}

bool NodeConnection::isValid() const
{
    return m_sourceNode != nullptr && m_destNode != nullptr;
}

void NodeConnection::setSelected(bool selected)
{
    m_selected = selected;
    emit connectionChanged();
}