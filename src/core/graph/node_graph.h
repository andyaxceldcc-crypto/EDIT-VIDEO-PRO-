#ifndef NODE_GRAPH_H
#define NODE_GRAPH_H

#include <QObject>
#include <QString>
#include <QList>
#include <QMap>
#include <QPointF>
#include <memory>

class NodeBase;
class NodeConnection;

/**
 * @class NodeGraph
 * @brief Manages the node graph for the compositor
 */
class NodeGraph : public QObject
{
    Q_OBJECT

public:
    explicit NodeGraph(QObject* parent = nullptr);
    ~NodeGraph();

    // Node management
    void addNode(NodeBase* node);
    void removeNode(NodeBase* node);
    NodeBase* getNode(const QString& name) const;
    QList<NodeBase*> getNodes() const { return m_nodes; }
    QList<NodeBase*> getNodesByType(NodeBase::NodeType type) const;
    void clear();

    // Connection management
    NodeConnection* createConnection(NodeBase* source, int sourcePort,
                                     NodeBase* dest, int destPort);
    void removeConnection(NodeConnection* connection);
    QList<NodeConnection*> getConnections() const { return m_connections; }

    // Execution
    bool executeFrame(int frame);
    void beginExecution();
    void endExecution();

    // Validation
    bool isValid() const;

signals:
    void nodeAdded(NodeBase* node);
    void nodeRemoved(NodeBase* node);
    void nodeUpdated(NodeBase* node);
    void connectionAdded(NodeConnection* connection);
    void connectionRemoved(NodeConnection* connection);
    void graphChanged();
    void executionStarted();
    void executionFinished();

private:
    void topologicalSort(QList<NodeBase*>& sortedNodes) const;

    QList<NodeBase*> m_nodes;
    QList<NodeConnection*> m_connections;
    bool m_executing;
};

#endif // NODE_GRAPH_H