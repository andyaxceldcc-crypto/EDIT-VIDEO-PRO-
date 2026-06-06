#include "keyer_node.h"
#include <opencv2/imgproc.hpp>
#include <cmath>

KeyerNode::KeyerNode(const QString& name)
    : NodeBase(NodeType::KEYER, name)
{
    addInput("input", 4);
    addInput("matte", 1);
    addOutput("output", 4);

    setProperty("keyer_type", static_cast<int>(CHROMA_KEY));
    setProperty("key_color_r", 0.0f);
    setProperty("key_color_g", 1.0f);
    setProperty("key_color_b", 0.0f);
    setProperty("threshold", 0.1f);
    setProperty("softness", 0.0f);
    setProperty("edge_grow", 0.0f);
}

KeyerNode::~KeyerNode()
{
}

void KeyerNode::setKeyerType(KeyerType type)
{
    setProperty("keyer_type", static_cast<int>(type));
}

KeyerNode::KeyerType KeyerNode::getKeyerType() const
{
    return static_cast<KeyerType>(getProperty("keyer_type").toInt());
}

void KeyerNode::setKeyColor(float r, float g, float b)
{
    setProperty("key_color_r", r);
    setProperty("key_color_g", g);
    setProperty("key_color_b", b);
}

void KeyerNode::setThreshold(float threshold)
{
    setProperty("threshold", qBound(0.0f, threshold, 1.0f));
}

void KeyerNode::setSoftness(float softness)
{
    setProperty("softness", qBound(0.0f, softness, 1.0f));
}

void KeyerNode::setEdgeGrow(float grow)
{
    setProperty("edge_grow", grow);
}

bool KeyerNode::processImage(cv::Mat& output, int frame)
{
    cv::Mat input = getInputImage(0, frame);
    if (input.empty())
    {
        return false;
    }

    KeyerType type = getKeyerType();

    switch (type)
    {
    case CHROMA_KEY:
        output = chromaKey(input);
        break;
    case LUMA_KEY:
        output = lumaKey(input);
        break;
    case RANGE_KEY:
        output = rangeKey(input);
        break;
    default:
        output = input.clone();
    }

    return true;
}

cv::Mat KeyerNode::chromaKey(const cv::Mat& input)
{
    cv::Mat output = input.clone();
    float threshold = getProperty("threshold").toFloat();

    float keyR = getProperty("key_color_r").toFloat();
    float keyG = getProperty("key_color_g").toFloat();
    float keyB = getProperty("key_color_b").toFloat();

    // Simple chroma keying
    for (int y = 0; y < input.rows; y++)
    {
        for (int x = 0; x < input.cols; x++)
        {
            cv::Vec4f pixel = input.at<cv::Vec4f>(y, x);

            float dist = std::sqrt(
                (pixel[0] - keyR) * (pixel[0] - keyR) +
                (pixel[1] - keyG) * (pixel[1] - keyG) +
                (pixel[2] - keyB) * (pixel[2] - keyB)
            );

            if (dist < threshold)
            {
                pixel[3] = 0.0f;
            }

            output.at<cv::Vec4f>(y, x) = pixel;
        }
    }

    return output;
}

cv::Mat KeyerNode::lumaKey(const cv::Mat& input)
{
    cv::Mat output = input.clone();
    return output;
}

cv::Mat KeyerNode::rangeKey(const cv::Mat& input)
{
    cv::Mat output = input.clone();
    return output;
}
