#ifndef MERGE_NODE_H
#define MERGE_NODE_H

#include "node_base.h"
#include <QString>

/**
 * @class MergeNode
 * @brief Compositing merge node with multiple blend modes
 * 
 * Supports standard compositing operations:
 * - Over (standard alpha composite)
 * - Under
 * - Screen
 * - Multiply
 * - Add/Plus
 * - Subtract
 * - Divide
 * - Difference
 * - ColorDodge
 * - ColorBurn
 * - Lighten
 * - Darken
 * - Overlay
 * - SoftLight
 * - HardLight
 */
class MergeNode : public NodeBase
{
public:
    enum BlendMode {
        OVER,
        UNDER,
        SCREEN,
        MULTIPLY,
        ADD,
        SUBTRACT,
        DIVIDE,
        DIFFERENCE,
        COLOR_DODGE,
        COLOR_BURN,
        LIGHTEN,
        DARKEN,
        OVERLAY,
        SOFT_LIGHT,
        HARD_LIGHT
    };

    MergeNode(const QString& name = "Merge");
    virtual ~MergeNode();

    void setBlendMode(BlendMode mode);
    BlendMode getBlendMode() const;

    void setOpacity(float opacity);
    float getOpacity() const { return getProperty("opacity").toFloat(); }

    void setMaskInput(bool enabled);
    bool getMaskInput() const { return getProperty("use_mask").toBool(); }

protected:
    bool processImage(cv::Mat& output, int frame) override;

private:
    cv::Mat blendOver(const cv::Mat& foreground, const cv::Mat& background, float opacity);
    cv::Mat blendUnder(const cv::Mat& foreground, const cv::Mat& background, float opacity);
    cv::Mat blendScreen(const cv::Mat& foreground, const cv::Mat& background, float opacity);
    cv::Mat blendMultiply(const cv::Mat& foreground, const cv::Mat& background, float opacity);
    cv::Mat applyMask(const cv::Mat& image, const cv::Mat& mask);
};

#endif // MERGE_NODE_H
