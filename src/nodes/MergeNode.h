#pragma once

#include "../core/Node.h"
#include <memory>

class FrameBuffer;

/**
 * @class MergeNode
 * @brief Nodo de composición con múltiples operaciones blend
 */
class MergeNode : public Node {
public:
    enum class BlendMode {
        OVER,
        UNDER,
        ADD,
        SUBTRACT,
        MULTIPLY,
        SCREEN,
        OVERLAY,
        SOFT_LIGHT
    };

    MergeNode(const std::string& nodeName = "Merge");
    virtual ~MergeNode() = default;

    std::shared_ptr<FrameBuffer> compute(int frame) override;

private:
    BlendMode blendMode = BlendMode::OVER;
    float mix = 1.0f;
    
    std::shared_ptr<FrameBuffer> blendFrames(const std::shared_ptr<FrameBuffer>& a,
                                            const std::shared_ptr<FrameBuffer>& b);
};
