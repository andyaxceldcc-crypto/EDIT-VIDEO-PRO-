#include "exposure_node.h"
#include <cmath>

ExposureNode::ExposureNode(const QString& name)
    : NodeBase(NodeType::CUSTOM, name)
{
    addInput("input", 4);
    addOutput("output", 4);

    setProperty("exposure", 0.0f);
    setProperty("offset", 0.0f);
    setProperty("contrast", 1.0f);
    setProperty("gamma", 1.0f);
    setProperty("highlights", 1.0f);
    setProperty("shadows", 1.0f);
    setProperty("clip_black", 0.0f);
    setProperty("clip_white", 1.0f);
}

ExposureNode::~ExposureNode()
{
}

void ExposureNode::setExposure(float exposure)
{
    setProperty("exposure", exposure);
}

void ExposureNode::setOffset(float offset)
{
    setProperty("offset", offset);
}

void ExposureNode::setContrast(float contrast)
{
    setProperty("contrast", qBound(0.0f, contrast, 10.0f));
}

void ExposureNode::setGamma(float gamma)
{
    setProperty("gamma", qBound(0.1f, gamma, 5.0f));
}

void ExposureNode::setHighlights(float highlights)
{
    setProperty("highlights", highlights);
}

void ExposureNode::setShadows(float shadows)
{
    setProperty("shadows", shadows);
}

void ExposureNode::setClipBlack(float clip)
{
    setProperty("clip_black", qBound(0.0f, clip, 1.0f));
}

void ExposureNode::setClipWhite(float clip)
{
    setProperty("clip_white", qBound(0.0f, clip, 1.0f));
}

bool ExposureNode::processImage(cv::Mat& output, int frame)
{
    cv::Mat input = getInputImage(0, frame);
    if (input.empty())
    {
        return false;
    }

    output = input.clone();

    float exposure = getExposure();
    float offset = getOffset();
    float contrast = getContrast();
    float gamma = getGamma();
    float highlights = getHighlights();
    float shadows = getShadows();

    float exposureMultiplier = std::pow(2.0f, exposure);
    float invGamma = 1.0f / gamma;
    float clipBlack = getProperty("clip_black").toFloat();
    float clipWhite = getProperty("clip_white").toFloat();

    for (int y = 0; y < output.rows; y++)
    {
        for (int x = 0; x < output.cols; x++)
        {
            cv::Vec4f pixel = output.at<cv::Vec4f>(y, x);

            for (int c = 0; c < 3; c++)
            {
                // Apply exposure
                float value = pixel[c] * exposureMultiplier + offset;

                // Apply contrast
                value = 0.5f + (value - 0.5f) * contrast;

                // Apply gamma
                if (value > 0.0f)
                {
                    value = std::pow(value, invGamma);
                }

                // Clamp
                value = std::max(clipBlack, std::min(clipWhite, value));

                pixel[c] = value;
            }

            output.at<cv::Vec4f>(y, x) = pixel;
        }
    }

    return true;
}

float ExposureNode::tonemap(float value, float exposure, float gamma)
{
    float exposureMultiplier = std::pow(2.0f, exposure);
    float invGamma = 1.0f / gamma;

    float mapped = value * exposureMultiplier;
    if (mapped > 0.0f)
    {
        mapped = std::pow(mapped, invGamma);
    }

    return mapped;
}

float ExposureNode::highlightCompress(float value, float compression)
{
    // Highlight compression using a smooth curve
    if (value > 1.0f)
    {
        float overexposed = value - 1.0f;
        return 1.0f + (overexposed / (1.0f + overexposed * compression));
    }
    return value;
}
