#ifndef NODE_GRAPH_H
#define NODE_GRAPH_H

#include <QVector>
#include <memory>

class Node;
class Connection;

class NodeGraph {
public:
    NodeGraph() = default;
    ~NodeGraph() = default;

    void addNode(std::shared_ptr<Node> node);
    std::shared_ptr<Connection> connect(std::shared_ptr<Node> src, int srcPort, std::shared_ptr<Node> dst, int dstPort);

    // Ejecuta el grafo en orden topológico simple
    void execute();

    QVector<std::shared_ptr<Node>> nodes() const { return m_nodes; }

private:
    QVector<std::shared_ptr<Node>> m_nodes;
    QVector<std::shared_ptr<Connection>> m_connections;
};

#endif // NODE_GRAPH_H
