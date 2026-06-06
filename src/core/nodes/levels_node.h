#ifndef LEVELS_NODE_H
#define LEVELS_NODE_H

#include "node_base.h"
#include <QString>

/**
 * @class LevelsNode
 * @brief Histogram-based levels adjustment
 * Similar to Nuke Levels, Blender Levels
 */
class LevelsNode : public NodeBase
{
public:
    LevelsNode(const QString& name = "Levels");
    virtual ~LevelsNode();

    // Input levels
    void setInputBlackPoint(float value);
    void setInputGamma(float value);
    void setInputWhitePoint(float value);

    // Output levels
    void setOutputBlackPoint(float value);
    void setOutputWhitePoint(float value);

    // Auto levels
    void autoLevels();
    void autoBlackPoint();
    void autoWhitePoint();

protected:
    bool processImage(cv::Mat& output, int frame) override;

private:
    float applyLevels(float value);
    cv::Mat calculateHistogram(const cv::Mat& input);
};

#endif // LEVELS_NODE_H
