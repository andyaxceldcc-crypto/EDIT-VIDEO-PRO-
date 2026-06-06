#pragma once

#include "../core/Node.h"
#include <memory>

class FrameBuffer;

/**
 * @class ReadNode
 * @brief Nodo de lectura de imágenes y secuencias EXR
 */
class ReadNode : public Node {
public:
    ReadNode(const std::string& nodeName = "Read");
    virtual ~ReadNode() = default;

    std::shared_ptr<FrameBuffer> compute(int frame) override;
    bool isSourceNode() const override { return true; }

private:
    std::string filepath;
    int startFrame = 1;
    int endFrame = 100;
    int missingFrameMode = 0; // 0: error, 1: black, 2: hold
    
    std::shared_ptr<FrameBuffer> loadFrame(int frame);
    std::string getSequencePath(int frame) const;
};
