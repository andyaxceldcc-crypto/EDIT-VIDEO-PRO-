#include "node_graph.h"
#include "node.h"
#include "connection.h"
#include <QSet>

void NodeGraph::addNode(std::shared_ptr<Node> node) {
    m_nodes.append(node);
}

std::shared_ptr<Connection> NodeGraph::connect(std::shared_ptr<Node> src, int srcPort, std::shared_ptr<Node> dst, int dstPort) {
    auto conn = std::make_shared<Connection>(src, srcPort, dst, dstPort);
    m_connections.append(conn);
    src->addOutputConnection(conn);
    dst->addInputConnection(conn);
    return conn;
}

void NodeGraph::execute() {
    QSet<Node*> processed;
    int total = m_nodes.size();
    int processedCount = 0;
    // Simple loop hasta que todos procesados o no cambios
    while (processedCount < total) {
        bool progress = false;
        for (auto &n : m_nodes) {
            if (processed.contains(n.get())) continue;
            // comprobar si todas las fuentes de sus inputs ya están procesadas
            bool ready = true;
            for (auto &conn : n->getInputConnections()) {
                auto src = conn->srcNode();
                if (src && !processed.contains(src.get())) { ready = false; break; }
            }
            if (!ready) continue;
            // procesar nodo
            n->process();
            processed.insert(n.get());
            processedCount++;
            progress = true;
        }
        if (!progress) {
            // posíble ciclo o dependencia faltante
            break;
        }
    }
}
