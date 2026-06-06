#ifndef KEYER_NODE_H
#define KEYER_NODE_H

#include "node_base.h"
#include <QString>

/**
 * @class KeyerNode
 * @brief Chroma/Luma keying for alpha extraction
 */
class KeyerNode : public NodeBase
{
public:
    enum KeyerType {
        CHROMA_KEY,
        LUMA_KEY,
        RANGE_KEY,
        DIFFERENCE_KEY
    };

    KeyerNode(const QString& name = "Keyer");
    virtual ~KeyerNode();

    void setKeyerType(KeyerType type);
    KeyerType getKeyerType() const;

    // Color to key out
    void setKeyColor(float r, float g, float b);

    // Keyer parameters
    void setThreshold(float threshold);
    void setSoftness(float softness);
    void setEdgeGrow(float grow);

protected:
    bool processImage(cv::Mat& output, int frame) override;

private:
    cv::Mat chromaKey(const cv::Mat& input);
    cv::Mat lumaKey(const cv::Mat& input);
    cv::Mat rangeKey(const cv::Mat& input);
};

#endif // KEYER_NODE_H
