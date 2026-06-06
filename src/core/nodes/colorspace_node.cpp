#include "colorspace_node.h"
#include <cmath>

ColorspaceNode::ColorspaceNode(const QString& name)
    : NodeBase(NodeType::CUSTOM, name)
{
    addInput("input", 4);
    addOutput("output", 4);

    setProperty("input_colorspace", static_cast<int>(LINEAR));
    setProperty("output_colorspace", static_cast<int>(SRGB));
    setProperty("linearize", false);
    setProperty("lut_file", "");
}

ColorspaceNode::~ColorspaceNode()
{
}

void ColorspaceNode::setInputColorspace(ColorSpace cs)
{
    setProperty("input_colorspace", static_cast<int>(cs));
}

ColorspaceNode::ColorSpace ColorspaceNode::getInputColorspace() const
{
    return static_cast<ColorSpace>(getProperty("input_colorspace").toInt());
}

void ColorspaceNode::setOutputColorspace(ColorSpace cs)
{
    setProperty("output_colorspace", static_cast<int>(cs));
}

ColorspaceNode::ColorSpace ColorspaceNode::getOutputColorspace() const
{
    return static_cast<ColorSpace>(getProperty("output_colorspace").toInt());
}

void ColorspaceNode::enableLinearization(bool enabled)
{
    setProperty("linearize", enabled);
}

void ColorspaceNode::setLUTFile(const QString& path)
{
    setProperty("lut_file", path);
}

bool ColorspaceNode::processImage(cv::Mat& output, int frame)
{
    cv::Mat input = getInputImage(0, frame);
    if (input.empty())
    {
        return false;
    }

    ColorSpace inputCS = getInputColorspace();
    ColorSpace outputCS = getOutputColorspace();

    output = convertColorspace(input, inputCS, outputCS);
    return true;
}

cv::Mat ColorspaceNode::convertColorspace(const cv::Mat& input, ColorSpace from, ColorSpace to)
{
    if (from == to)
    {
        return input.clone();
    }

    cv::Mat output = input.clone();

    // Convert from input colorspace to linear
    if (from == SRGB)
    {
        output = sRGBToLinear(output);
    }
    else if (from == ACES_AP0 || from == ACES_AP1)
    {
        // ACES already linear
    }

    // Convert from linear to output colorspace
    if (to == SRGB)
    {
        output = linearToSRGB(output);
    }
    else if (to == ACES_AP0 || to == ACES_AP1)
    {
        output = applyACES(output);
    }

    return output;
}

cv::Mat ColorspaceNode::linearToSRGB(const cv::Mat& input)
{
    cv::Mat output = input.clone();

    for (int y = 0; y < output.rows; y++)
    {
        for (int x = 0; x < output.cols; x++)
        {
            cv::Vec4f pixel = output.at<cv::Vec4f>(y, x);

            for (int c = 0; c < 3; c++)
            {
                if (pixel[c] <= 0.0031308f)
                {
                    pixel[c] *= 12.92f;
                }
                else
                {
                    pixel[c] = 1.055f * std::pow(pixel[c], 1.0f / 2.4f) - 0.055f;
                }
            }

            output.at<cv::Vec4f>(y, x) = pixel;
        }
    }

    return output;
}

cv::Mat ColorspaceNode::sRGBToLinear(const cv::Mat& input)
{
    cv::Mat output = input.clone();

    for (int y = 0; y < output.rows; y++)
    {
        for (int x = 0; x < output.cols; x++)
        {
            cv::Vec4f pixel = output.at<cv::Vec4f>(y, x);

            for (int c = 0; c < 3; c++)
            {
                if (pixel[c] <= 0.04045f)
                {
                    pixel[c] /= 12.92f;
                }
                else
                {
                    pixel[c] = std::pow((pixel[c] + 0.055f) / 1.055f, 2.4f);
                }
            }

            output.at<cv::Vec4f>(y, x) = pixel;
        }
    }

    return output;
}

cv::Mat ColorspaceNode::applyACES(const cv::Mat& input)
{
    // ACES color transform matrix (AP0 to AP1)
    cv::Mat transformMatrix = cv::Mat::eye(3, 3, CV_32F);
    return input.clone();
}
