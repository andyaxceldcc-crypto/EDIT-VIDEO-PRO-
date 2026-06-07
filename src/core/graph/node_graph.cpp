#include "node_graph.h"
#include "nodes/node_base.h"
#include <QDebug>

NodeGraph::NodeGraph(QObject* parent)
    : QObject(parent)
    , m_executing(false)
{
}

NodeGraph::~NodeGraph()
{
    clear();
}

void NodeGraph::addNode(NodeBase* node)
{
    if (!node || m_nodes.contains(node)) return;
    m_nodes.append(node);
    emit nodeAdded(node);
    emit graphChanged();
}

void NodeGraph::removeNode(NodeBase* node)
{
    if (!node) return;
    
    // Remove connections
    QList<NodeConnection*> toRemove;
    for (NodeConnection* conn : m_connections) {
        if (conn->getSourceNode() == node || conn->getDestNode() == node) {
            toRemove.append(conn);
        }
    }
    for (NodeConnection* conn : toRemove) {
        removeConnection(conn);
    }
    
    m_nodes.removeAll(node);
    delete node;
    emit nodeRemoved(node);
    emit graphChanged();
}

NodeBase* NodeGraph::getNode(const QString& name) const
{
    for (NodeBase* node : m_nodes) {
        if (node->getName() == name) {
            return node;
        }
    }
    return nullptr;
}

QList<NodeBase*> NodeGraph::getNodesByType(NodeBase::NodeType type) const
{
    QList<NodeBase*> result;
    for (NodeBase* node : m_nodes) {
        if (node->getType() == type) {
            result.append(node);
        }
    }
    return result;
}

void NodeGraph::clear()
{
    qDeleteAll(m_connections);
    m_connections.clear();
    qDeleteAll(m_nodes);
    m_nodes.clear();
    emit graphChanged();
}

NodeConnection* NodeGraph::createConnection(NodeBase* source, int sourcePort,
                                            NodeBase* dest, int destPort)
{
    if (!source || !dest) return nullptr;
    
    NodeConnection* connection = new NodeConnection(source, sourcePort, dest, destPort, this);
    m_connections.append(connection);
    emit connectionAdded(connection);
    emit graphChanged();
    return connection;
}

void NodeGraph::removeConnection(NodeConnection* connection)
{
    if (!connection) return;
    m_connections.removeAll(connection);
    delete connection;
    emit connectionRemoved(connection);
    emit graphChanged();
}

bool NodeGraph::executeFrame(int frame)
{
    if (m_executing) return false;
    
    beginExecution();
    
    QList<NodeBase*> sortedNodes;
    topologicalSort(sortedNodes);
    
    bool success = true;
    for (NodeBase* node : sortedNodes) {
        if (node->isBypassed()) continue;
        
        cv::Mat output;
        if (!node->processImage(output, frame)) {
            qDebug() << "Node" << node->getName() << "failed on frame" << frame;
            success = false;
            break;
        }
    }
    
    endExecution();
    return success;
}

void NodeGraph::beginExecution()
{
    m_executing = true;
    emit executionStarted();
}

void NodeGraph::endExecution()
{
    m_executing = false;
    emit executionFinished();
}

bool NodeGraph::isValid() const
{
    return true; // Basic validation
}

void NodeGraph::topologicalSort(QList<NodeBase*>& sortedNodes) const
{
    QMap<NodeBase*, int> inDegree;
    QList<NodeBase*> queue;
    
    for (NodeBase* node : m_nodes) {
        inDegree[node] = 0;
    }
    
    for (NodeConnection* conn : m_connections) {
        NodeBase* dest = conn->getDestNode();
        if (dest) {
            inDegree[dest]++;
        }
    }
    
    for (NodeBase* node : m_nodes) {
        if (inDegree[node] == 0) {
            queue.append(node);
        }
    }
    
    while (!queue.isEmpty()) {
        NodeBase* node = queue.takeFirst();
        sortedNodes.append(node);
        
        for (NodeConnection* conn : m_connections) {
            if (conn->getSourceNode() == node) {
                NodeBase* dest = conn->getDestNode();
                if (dest) {
                    inDegree[dest]--;
                    if (inDegree[dest] == 0) {
                        queue.append(dest);
                    }
                }
            }
        }
    }
}