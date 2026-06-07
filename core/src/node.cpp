#include "node.h"
#include "connection.h"

Node::Node(const QString& name, Node::NodeType type)
    : m_name(name), m_type(type)
{
}

QString Node::getTypeString() const {
    switch (m_type) {
        case INPUT: return "INPUT";
        case OUTPUT: return "OUTPUT";
        case EFFECT: return "EFFECT";
        case TRANSFORM: return "TRANSFORM";
        case COLOR: return "COLOR";
        case KEYING: return "KEYING";
        case MERGE: return "MERGE";
        default: return "CUSTOM";
    }
}

void Node::addInputConnection(std::shared_ptr<Connection> connection) {
    m_inputConnections.append(connection);
}

void Node::addOutputConnection(std::shared_ptr<Connection> connection) {
    m_outputConnections.append(connection);
}

QVector<std::shared_ptr<Connection>> Node::getInputConnections() const {
    return m_inputConnections;
}

QVector<std::shared_ptr<Connection>> Node::getOutputConnections() const {
    return m_outputConnections;
}

void Node::setParameter(const QString& name, const QVariant& value) {
    m_parameters.insert(name, value);
}

QVariant Node::getParameter(const QString& name) const {
    return m_parameters.value(name, QVariant());
}
