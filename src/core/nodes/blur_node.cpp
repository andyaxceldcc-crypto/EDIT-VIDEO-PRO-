#include "blur_node.h"
#include <opencv2/imgproc.hpp>
#include <cmath>

BlurNode::BlurNode(const QString& name)
    : NodeBase(NodeType::BLUR, name)
{
    addInput("input", 4);
    addOutput("output", 4);

    setProperty("blur_type", static_cast<int>(GAUSSIAN));
    setProperty("size", 1.0f);
    setProperty("motion_angle", 0.0f);
    setProperty("motion_length", 10.0f);
    setProperty("radial_center_x", 0.5f);
    setProperty("radial_center_y", 0.5f);
}

BlurNode::~BlurNode()
{
}

void BlurNode::setBlurType(BlurType type)
{
    setProperty("blur_type", static_cast<int>(type));
}

BlurNode::BlurType BlurNode::getBlurType() const
{
    return static_cast<BlurType>(getProperty("blur_type").toInt());
}

void BlurNode::setSize(float size)
{
    setProperty("size", qBound(0.0f, size, 100.0f));
}

void BlurNode::setMotionAngle(float angle)
{
    setProperty("motion_angle", angle);
}

void BlurNode::setMotionLength(float length)
{
    setProperty("motion_length", qBound(0.0f, length, 1000.0f));
}

void BlurNode::setRadialCenter(float x, float y)
{
    setProperty("radial_center_x", x);
    setProperty("radial_center_y", y);
}

bool BlurNode::processImage(cv::Mat& output, int frame)
{
    cv::Mat input = getInputImage(0, frame);
    if (input.empty())
    {
        return false;
    }

    float size = getSize();
    BlurType type = getBlurType();

    switch (type)
    {
    case GAUSSIAN:
        output = applyGaussianBlur(input, size);
        break;
    case MOTION:
    {
        float angle = getProperty("motion_angle").toFloat();
        float length = getProperty("motion_length").toFloat();
        output = applyMotionBlur(input, angle, length);
        break;
    }
    case RADIAL:
    {
        float cx = getProperty("radial_center_x").toFloat();
        float cy = getProperty("radial_center_y").toFloat();
        output = applyRadialBlur(input, cx, cy, size);
        break;
    }
    case BOX:
    {
        int kernelSize = static_cast<int>(size) * 2 + 1;
        cv::blur(input, output, cv::Size(kernelSize, kernelSize));
        break;
    }
    case MEDIAN:
    {
        int kernelSize = static_cast<int>(size) * 2 + 1;
        cv::medianBlur(input, output, kernelSize);
        break;
    }
    default:
        output = input.clone();
    }

    return true;
}

cv::Mat BlurNode::applyGaussianBlur(const cv::Mat& input, float size)
{
    cv::Mat output;
    int kernelSize = static_cast<int>(size) * 2 + 1;
    float sigma = size / 3.0f;

    cv::GaussianBlur(input, output, cv::Size(kernelSize, kernelSize), sigma, sigma);
    return output;
}

cv::Mat BlurNode::applyMotionBlur(const cv::Mat& input, float angle, float length)
{
    cv::Mat output = input.clone();
    int kernelSize = static_cast<int>(length) * 2 + 1;

    // Create motion blur kernel
    cv::Mat kernel = cv::getRotationMatrix2D(cv::Point2f(kernelSize / 2.0f, kernelSize / 2.0f),
                                             angle, 1.0);

    cv::filter2D(input, output, input.depth(), kernel);
    return output;
}

cv::Mat BlurNode::applyRadialBlur(const cv::Mat& input, float centerX, float centerY, float amount)
{
    cv::Mat output = input.clone();
    // Radial blur implementation
    return output;
}
