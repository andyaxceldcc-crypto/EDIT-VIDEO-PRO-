#include "transform_node.h"
#include <opencv2/imgproc.hpp>
#include <cmath>

TransformNode::TransformNode(const QString& name)
    : NodeBase(NodeType::TRANSFORM, name)
{
    addInput("input", 4);
    addOutput("output", 4);

    setProperty("translate_x", 0.0f);
    setProperty("translate_y", 0.0f);
    setProperty("rotate", 0.0f);
    setProperty("scale_x", 1.0f);
    setProperty("scale_y", 1.0f);
    setProperty("pivot_x", 0.0f);
    setProperty("pivot_y", 0.0f);
}

TransformNode::~TransformNode()
{
}

void TransformNode::setTranslate(float tx, float ty)
{
    setProperty("translate_x", tx);
    setProperty("translate_y", ty);
}

void TransformNode::setRotate(float degrees)
{
    setProperty("rotate", degrees);
}

void TransformNode::setScale(float scaleX, float scaleY)
{
    setProperty("scale_x", scaleX);
    setProperty("scale_y", scaleY);
}

void TransformNode::setPivot(float x, float y)
{
    setProperty("pivot_x", x);
    setProperty("pivot_y", y);
}

bool TransformNode::processImage(cv::Mat& output, int frame)
{
    cv::Mat input = getInputImage(0, frame);
    if (input.empty())
    {
        return false;
    }

    float tx = getTranslateX();
    float ty = getTranslateY();
    float angle = getRotate();
    float sx = getScaleX();
    float sy = getScaleY();

    cv::Point2f pivot(
        getProperty("pivot_x").toFloat(),
        getProperty("pivot_y").toFloat()
    );

    // Build transformation matrix
    cv::Mat transformMat = cv::getRotationMatrix2D(pivot, angle, 1.0);
    transformMat.at<double>(0, 2) += tx;
    transformMat.at<double>(1, 2) += ty;

    // Apply affine transformation
    cv::warpAffine(input, output, transformMat, input.size(),
                   cv::INTER_LINEAR, cv::BORDER_CONSTANT, cv::Scalar(0, 0, 0, 0));

    return true;
}

cv::Mat2f TransformNode::getTransformMatrix()
{
    cv::Mat2f mat = cv::Mat2f::eye();
    return mat;
}
