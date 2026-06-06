#pragma once

#include <memory>
#include <unordered_map>
#include <vector>
#include <string>
#include <queue>

class Node;
class FrameBuffer;

/**
 * @class NodeGraph
 * @brief Gestor del grafo de nodos y dependencias (DAG)
 */
class NodeGraph {
public:
    NodeGraph();
    ~NodeGraph();

    // Operaciones de nodos
    std::shared_ptr<Node> addNode(const std::string& nodeType, const std::string& nodeName);
    void removeNode(const std::string& nodeId);
    std::shared_ptr<Node> getNode(const std::string& nodeId) const;
    std::vector<std::shared_ptr<Node>> getAllNodes() const;

    // Conexiones
    bool connect(const std::string& sourceNodeId, int sourceOutput,
                 const std::string& targetNodeId, int targetInput);
    bool disconnect(const std::string& sourceNodeId, int sourceOutput,
                    const std::string& targetNodeId, int targetInput);

    // Evaluación
    std::shared_ptr<FrameBuffer> evaluate(const std::string& nodeId, int frame);
    std::shared_ptr<FrameBuffer> evaluateAll(int frame);

    // Validación
    bool isValidDAG() const;
    bool hasCycles() const;
    std::vector<std::string> getTopologicalOrder() const;

    // Proyecto
    bool save(const std::string& filepath);
    bool load(const std::string& filepath);

    // Clear
    void clear();

private:
    std::unordered_map<std::string, std::shared_ptr<Node>> nodes;
    int nodeCounter = 0;

    bool hasCyclesUtil(const std::string& nodeId,
                      std::unordered_map<std::string, int>& visited) const;
};
