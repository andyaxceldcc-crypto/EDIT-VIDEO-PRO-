#include "levels_node.h"
#include <cmath>

LevelsNode::LevelsNode(const QString& name)
    : NodeBase(NodeType::CUSTOM, name)
{
    addInput("input", 4);
    addOutput("output", 4);

    setProperty("input_black", 0.0f);
    setProperty("input_gamma", 1.0f);
    setProperty("input_white", 1.0f);
    setProperty("output_black", 0.0f);
    setProperty("output_white", 1.0f);
}

LevelsNode::~LevelsNode()
{
}

void LevelsNode::setInputBlackPoint(float value)
{
    setProperty("input_black", qBound(0.0f, value, 1.0f));
}

void LevelsNode::setInputGamma(float value)
{
    setProperty("input_gamma", qBound(0.1f, value, 5.0f));
}

void LevelsNode::setInputWhitePoint(float value)
{
    setProperty("input_white", qBound(0.0f, value, 1.0f));
}

void LevelsNode::setOutputBlackPoint(float value)
{
    setProperty("output_black", qBound(0.0f, value, 1.0f));
}

void LevelsNode::setOutputWhitePoint(float value)
{
    setProperty("output_white", qBound(0.0f, value, 1.0f));
}

void LevelsNode::autoLevels()
{
    cv::Mat input = getInputImage(0, 0);
    if (input.empty())
        return;

    // TODO: Analyze histogram and set auto levels
}

void LevelsNode::autoBlackPoint()
{
    // TODO: Find minimum non-zero value
}

void LevelsNode::autoWhitePoint()
{
    // TODO: Find maximum value
}

bool LevelsNode::processImage(cv::Mat& output, int frame)
{
    cv::Mat input = getInputImage(0, frame);
    if (input.empty())
    {
        return false;
    }

    output = input.clone();

    for (int y = 0; y < output.rows; y++)
    {
        for (int x = 0; x < output.cols; x++)
        {
            cv::Vec4f pixel = output.at<cv::Vec4f>(y, x);

            for (int c = 0; c < 3; c++)
            {
                pixel[c] = applyLevels(pixel[c]);
            }

            output.at<cv::Vec4f>(y, x) = pixel;
        }
    }

    return true;
}

float LevelsNode::applyLevels(float value)
{
    float inputBlack = getProperty("input_black").toFloat();
    float inputGamma = getProperty("input_gamma").toFloat();
    float inputWhite = getProperty("input_white").toFloat();
    float outputBlack = getProperty("output_black").toFloat();
    float outputWhite = getProperty("output_white").toFloat();

    // Remap input
    if (inputWhite > inputBlack)
    {
        value = (value - inputBlack) / (inputWhite - inputBlack);
    }

    // Clamp
    value = std::max(0.0f, std::min(1.0f, value));

    // Apply gamma
    if (inputGamma != 1.0f && value > 0.0f)
    {
        value = std::pow(value, 1.0f / inputGamma);
    }

    // Remap output
    value = outputBlack + value * (outputWhite - outputBlack);

    return value;
}

cv::Mat LevelsNode::calculateHistogram(const cv::Mat& input)
{
    cv::Mat hist;
    return hist;
}
