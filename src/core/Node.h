#pragma once

#include <memory>
#include <vector>
#include <string>
#include <map>
#include <variant>
#include <functional>

class FrameBuffer;

enum class InputType {
    IMAGE,
    FLOAT,
    INT,
    BOOL,
    COLOR,
    CURVE
};

enum class OutputType {
    IMAGE,
    FLOAT,
    INT,
    BOOL,
    COLOR
};

/**
 * @struct Knob
 * @brief Parámetro ajustable de un nodo
 */
struct Knob {
    std::string name;
    std::string type; // "float", "int", "bool", "color"
    std::variant<float, int, bool, float*> value; // RGBA
    float minValue = 0.0f;
    float maxValue = 1.0f;
    bool animated = false;
};

/**
 * @class Node
 * @brief Clase base para todos los nodos de composición
 */
class Node : public std::enable_shared_from_this<Node> {
public:
    Node(const std::string& nodeType, const std::string& nodeName);
    virtual ~Node() = default;

    // Identidad
    std::string getNodeId() const { return nodeId; }
    std::string getNodeType() const { return nodeType; }
    std::string getNodeName() const { return nodeName; }
    void setNodeName(const std::string& name) { nodeName = name; }

    // Conectores
    virtual void addInput(const std::string& inputName, InputType type);
    virtual void addOutput(const std::string& outputName, OutputType type);
    
    // Propiedades
    virtual void setKnob(const std::string& knobName, const std::variant<float, int, bool>& value);
    virtual std::variant<float, int, bool> getKnob(const std::string& knobName) const;
    const std::vector<Knob>& getKnobs() const { return knobs; }

    // Conexiones
    virtual bool connectInput(int inputIndex, std::shared_ptr<Node> sourceNode, int sourceOutput);
    virtual std::shared_ptr<Node> getInputNode(int inputIndex) const;
    virtual int getInputNodeOutput(int inputIndex) const;

    // Compute
    virtual std::shared_ptr<FrameBuffer> compute(int frame) = 0;
    virtual bool isSourceNode() const { return false; }
    virtual bool isSinkNode() const { return false; }

    // Position (para UI)
    float posX = 0.0f, posY = 0.0f;
    
protected:
    std::string nodeId;
    std::string nodeType;
    std::string nodeName;
    
    std::vector<std::pair<std::string, InputType>> inputs;
    std::vector<std::pair<std::string, OutputType>> outputs;
    std::vector<Knob> knobs;
    
    std::vector<std::shared_ptr<Node>> inputNodes;
    std::vector<int> inputNodeOutputs;
};
