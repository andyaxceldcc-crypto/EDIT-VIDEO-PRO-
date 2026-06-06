#include "channel_mix_node.h"
#include <cstring>

ChannelMixNode::ChannelMixNode(const QString& name)
    : NodeBase(NodeType::CUSTOM, name)
{
    addInput("input", 4);
    addOutput("output", 4);

    setProperty("preserve_alpha", true);

    // Initialize to identity matrix
    m_channelMatrix = {{
        1, 0, 0, 0,
        0, 1, 0, 0,
        0, 0, 1, 0,
        0, 0, 0, 1
    }};
}

ChannelMixNode::~ChannelMixNode()
{
}

void ChannelMixNode::setChannelMatrix(const std::array<float, 16>& matrix)
{
    m_channelMatrix = matrix;
    markDirty();
}

void ChannelMixNode::swapRedGreen()
{
    m_channelMatrix = {{
        0, 1, 0, 0,
        1, 0, 0, 0,
        0, 0, 1, 0,
        0, 0, 0, 1
    }};
    markDirty();
}

void ChannelMixNode::swapRedBlue()
{
    m_channelMatrix = {{
        0, 0, 1, 0,
        0, 1, 0, 0,
        1, 0, 0, 0,
        0, 0, 0, 1
    }};
    markDirty();
}

void ChannelMixNode::swapGreenBlue()
{
    m_channelMatrix = {{
        1, 0, 0, 0,
        0, 0, 1, 0,
        0, 1, 0, 0,
        0, 0, 0, 1
    }};
    markDirty();
}

void ChannelMixNode::monochrome()
{
    // Convert to grayscale using luminance weights
    m_channelMatrix = {{
        0.299f, 0.587f, 0.114f, 0,
        0.299f, 0.587f, 0.114f, 0,
        0.299f, 0.587f, 0.114f, 0,
        0, 0, 0, 1
    }};
    markDirty();
}

void ChannelMixNode::preserveAlpha(bool preserve)
{
    setProperty("preserve_alpha", preserve);
}

bool ChannelMixNode::processImage(cv::Mat& output, int frame)
{
    cv::Mat input = getInputImage(0, frame);
    if (input.empty())
    {
        return false;
    }

    output = input.clone();
    bool preserveAlpha = getProperty("preserve_alpha").toBool();

    for (int y = 0; y < output.rows; y++)
    {
        for (int x = 0; x < output.cols; x++)
        {
            cv::Vec4f inPixel = input.at<cv::Vec4f>(y, x);
            cv::Vec4f outPixel;

            // Apply matrix multiplication
            // outPixel[i] = sum(matrix[i][j] * inPixel[j])
            for (int i = 0; i < 4; i++)
            {
                float sum = 0.0f;
                for (int j = 0; j < 4; j++)
                {
                    sum += m_channelMatrix[i * 4 + j] * inPixel[j];
                }
                outPixel[i] = sum;
            }

            if (preserveAlpha)
            {
                outPixel[3] = inPixel[3];
            }

            output.at<cv::Vec4f>(y, x) = outPixel;
        }
    }

    return true;
}
