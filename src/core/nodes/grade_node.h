#ifndef GRADE_NODE_H
#define GRADE_NODE_H

#include "node_base.h"
#include <QString>

/**
 * @class GradeNode
 * @brief Professional color grading and correction node
 */
class GradeNode : public NodeBase
{
public:
    GradeNode(const QString& name = "Grade");
    virtual ~GradeNode();

    // Lift/Gamma/Gain (LGG)
    void setLift(float r, float g, float b);
    void setGamma(float r, float g, float b);
    void setGain(float r, float g, float b);

    // Shadows/Midtones/Highlights
    void setShadows(float r, float g, float b);
    void setMidtones(float r, float g, float b);
    void setHighlights(float r, float g, float b);

    // Overall adjustments
    void setContrast(float contrast);
    void setSaturation(float saturation);
    void setExposure(float exposure);

protected:
    bool processImage(cv::Mat& output, int frame) override;

private:
    cv::Mat applyCDL(const cv::Mat& input);
    cv::Mat adjustExposure(const cv::Mat& input, float exposure);
    cv::Mat adjustSaturation(const cv::Mat& input, float saturation);
};

#endif // GRADE_NODE_H
