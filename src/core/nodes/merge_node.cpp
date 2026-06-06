#include "merge_node.h"
#include <opencv2/imgproc.hpp>
#include <QDebug>

MergeNode::MergeNode(const QString& name)
    : NodeBase(NodeType::MERGE, name)
{
    // Create inputs
    addInput("A", 4);
    addInput("B", 4);
    addInput("Mask", 1);

    // Create output
    addOutput("result", 4);

    // Initialize properties
    setProperty("blend_mode", static_cast<int>(BlendMode::OVER));
    setProperty("opacity", 1.0f);
    setProperty("use_mask", false);
}

MergeNode::~MergeNode()
{
}

void MergeNode::setBlendMode(BlendMode mode)
{
    setProperty("blend_mode", static_cast<int>(mode));
}

MergeNode::BlendMode MergeNode::getBlendMode() const
{
    return static_cast<BlendMode>(getProperty("blend_mode").toInt());
}

void MergeNode::setOpacity(float opacity)
{
    setProperty("opacity", qBound(0.0f, opacity, 1.0f));
}

void MergeNode::setMaskInput(bool enabled)
{
    setProperty("use_mask", enabled);
}

bool MergeNode::processImage(cv::Mat& output, int frame)
{
    cv::Mat imageA = getInputImage(0, frame);
    cv::Mat imageB = getInputImage(1, frame);

    if (imageA.empty() || imageB.empty())
    {
        qWarning() << "MergeNode: Missing input images";
        return false;
    }

    // Ensure same size
    if (imageA.size() != imageB.size())
    {
        cv::resize(imageB, imageB, imageA.size());
    }

    float opacity = getOpacity();
    BlendMode mode = getBlendMode();

    // Apply blend mode
    switch (mode)
    {
    case OVER:
        output = blendOver(imageA, imageB, opacity);
        break;
    case UNDER:
        output = blendUnder(imageA, imageB, opacity);
        break;
    case SCREEN:
        output = blendScreen(imageA, imageB, opacity);
        break;
    case MULTIPLY:
        output = blendMultiply(imageA, imageB, opacity);
        break;
    case ADD:
        cv::add(imageA, imageB * opacity, output);
        break;
    default:
        output = blendOver(imageA, imageB, opacity);
    }

    // Apply mask if enabled
    if (getProperty("use_mask").toBool())
    {
        cv::Mat mask = getInputImage(2, frame);
        if (!mask.empty())
        {
            output = applyMask(output, mask);
        }
    }

    return true;
}

cv::Mat MergeNode::blendOver(const cv::Mat& foreground, const cv::Mat& background, float opacity)
{
    cv::Mat result;
    cv::Mat fg = foreground.clone();
    cv::Mat bg = background.clone();

    // Standard alpha composite: A over B
    result.create(fg.size(), fg.type());

    for (int y = 0; y < fg.rows; y++)
    {
        for (int x = 0; x < fg.cols; x++)
        {
            cv::Vec4f fgPixel = fg.at<cv::Vec4f>(y, x);
            cv::Vec4f bgPixel = bg.at<cv::Vec4f>(y, x);

            float alpha = fgPixel[3] * opacity;
            cv::Vec4f output = cv::Vec4f(
                fgPixel[0] * alpha + bgPixel[0] * (1.0f - alpha),
                fgPixel[1] * alpha + bgPixel[1] * (1.0f - alpha),
                fgPixel[2] * alpha + bgPixel[2] * (1.0f - alpha),
                alpha + bgPixel[3] * (1.0f - alpha)
            );
            result.at<cv::Vec4f>(y, x) = output;
        }
    }

    return result;
}

cv::Mat MergeNode::blendUnder(const cv::Mat& foreground, const cv::Mat& background, float opacity)
{
    return blendOver(background, foreground, opacity);
}

cv::Mat MergeNode::blendScreen(const cv::Mat& foreground, const cv::Mat& background, float opacity)
{
    cv::Mat result;
    cv::Mat fg = foreground.clone();
    cv::Mat bg = background.clone();

    result.create(fg.size(), fg.type());

    for (int y = 0; y < fg.rows; y++)
    {
        for (int x = 0; x < fg.cols; x++)
        {
            cv::Vec4f fgPixel = fg.at<cv::Vec4f>(y, x);
            cv::Vec4f bgPixel = bg.at<cv::Vec4f>(y, x);

            float alpha = fgPixel[3] * opacity;
            cv::Vec4f output = cv::Vec4f(
                1.0f - (1.0f - fgPixel[0]) * (1.0f - bgPixel[0]) * alpha + bgPixel[0] * (1.0f - alpha),
                1.0f - (1.0f - fgPixel[1]) * (1.0f - bgPixel[1]) * alpha + bgPixel[1] * (1.0f - alpha),
                1.0f - (1.0f - fgPixel[2]) * (1.0f - bgPixel[2]) * alpha + bgPixel[2] * (1.0f - alpha),
                alpha + bgPixel[3] * (1.0f - alpha)
            );
            result.at<cv::Vec4f>(y, x) = output;
        }
    }

    return result;
}

cv::Mat MergeNode::blendMultiply(const cv::Mat& foreground, const cv::Mat& background, float opacity)
{
    cv::Mat result;
    cv::Mat fg = foreground.clone();
    cv::Mat bg = background.clone();

    result.create(fg.size(), fg.type());

    for (int y = 0; y < fg.rows; y++)
    {
        for (int x = 0; x < fg.cols; x++)
        {
            cv::Vec4f fgPixel = fg.at<cv::Vec4f>(y, x);
            cv::Vec4f bgPixel = bg.at<cv::Vec4f>(y, x);

            float alpha = fgPixel[3] * opacity;
            cv::Vec4f output = cv::Vec4f(
                fgPixel[0] * bgPixel[0] * alpha + bgPixel[0] * (1.0f - alpha),
                fgPixel[1] * bgPixel[1] * alpha + bgPixel[1] * (1.0f - alpha),
                fgPixel[2] * bgPixel[2] * alpha + bgPixel[2] * (1.0f - alpha),
                alpha + bgPixel[3] * (1.0f - alpha)
            );
            result.at<cv::Vec4f>(y, x) = output;
        }
    }

    return result;
}

cv::Mat MergeNode::applyMask(const cv::Mat& image, const cv::Mat& mask)
{
    cv::Mat result = image.clone();
    cv::Mat maskResize = mask.clone();

    if (maskResize.size() != image.size())
    {
        cv::resize(maskResize, maskResize, image.size());
    }

    for (int y = 0; y < result.rows; y++)
    {
        for (int x = 0; x < result.cols; x++)
        {
            float maskValue = 0.0f;
            if (maskResize.channels() == 1)
            {
                maskValue = maskResize.at<float>(y, x);
            }
            else
            {
                cv::Vec4f maskPixel = maskResize.at<cv::Vec4f>(y, x);
                maskValue = maskPixel[3];
            }

            cv::Vec4f pixel = result.at<cv::Vec4f>(y, x);
            pixel[3] *= maskValue;
            result.at<cv::Vec4f>(y, x) = pixel;
        }
    }

    return result;
}
