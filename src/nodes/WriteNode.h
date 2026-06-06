#pragma once

#include "../core/Node.h"
#include <memory>

class FrameBuffer;

/**
 * @class WriteNode
 * @brief Nodo de escritura de imágenes y secuencias
 */
class WriteNode : public Node {
public:
    WriteNode(const std::string& nodeName = "Write");
    virtual ~WriteNode() = default;

    std::shared_ptr<FrameBuffer> compute(int frame) override;
    bool isSinkNode() const override { return true; }

private:
    std::string filepath;
    int startFrame = 1;
    int endFrame = 100;
    std::string format = "exr"; // exr, tiff, png
    int bitDepth = 16; // 8, 16, 32
    
    bool writeFrame(const std::shared_ptr<FrameBuffer>& frame, int frameNumber);
    std::string getSequencePath(int frame) const;
};
