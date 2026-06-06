#ifndef BLUR_NODE_H
#define BLUR_NODE_H

#include "node_base.h"
#include <QString>

/**
 * @class BlurNode
 * @brief Professional blur filters: Gaussian, Motion Blur, Radial Blur
 */
class BlurNode : public NodeBase
{
public:
    enum BlurType {
        GAUSSIAN,
        MOTION,
        RADIAL,
        BOX,
        MEDIAN
    };

    BlurNode(const QString& name = "Blur");
    virtual ~BlurNode();

    void setBlurType(BlurType type);
    BlurType getBlurType() const;

    void setSize(float size);
    float getSize() const { return getProperty("size").toFloat(); }

    // Motion blur specific
    void setMotionAngle(float angle);
    void setMotionLength(float length);

    // Radial blur
    void setRadialCenter(float x, float y);

protected:
    bool processImage(cv::Mat& output, int frame) override;

private:
    cv::Mat applyGaussianBlur(const cv::Mat& input, float size);
    cv::Mat applyMotionBlur(const cv::Mat& input, float angle, float length);
    cv::Mat applyRadialBlur(const cv::Mat& input, float centerX, float centerY, float amount);
};

#endif // BLUR_NODE_H
