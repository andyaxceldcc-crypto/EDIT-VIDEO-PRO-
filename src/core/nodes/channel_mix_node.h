#ifndef CHANNEL_MIX_NODE_H
#define CHANNEL_MIX_NODE_H

#include "node_base.h"
#include <QString>
#include <array>

/**
 * @class ChannelMixNode
 * @brief Channel mixing and manipulation
 */
class ChannelMixNode : public NodeBase
{
public:
    ChannelMixNode(const QString& name = "ChannelMix");
    virtual ~ChannelMixNode();

    // Set channel mix matrix 4x4
    void setChannelMatrix(const std::array<float, 16>& matrix);

    // Shortcuts
    void swapRedGreen();
    void swapRedBlue();
    void swapGreenBlue();
    void monochrome();
    void preserveAlpha(bool preserve);

protected:
    bool processImage(cv::Mat& output, int frame) override;

private:
    std::array<float, 16> m_channelMatrix;
};

#endif // CHANNEL_MIX_NODE_H
