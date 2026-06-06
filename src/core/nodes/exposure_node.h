#ifndef EXPOSURE_NODE_H
#define EXPOSURE_NODE_H

#include "node_base.h"
#include <QString>

/**
 * @class ExposureNode
 * @brief Professional exposure and tone mapping node
 * Similar to Nuke Exposure and Blender Exposure
 */
class ExposureNode : public NodeBase
{
public:
    ExposureNode(const QString& name = "Exposure");
    virtual ~ExposureNode();

    // Exposure control
    void setExposure(float exposure);
    float getExposure() const { return getProperty("exposure").toFloat(); }

    // Offset
    void setOffset(float offset);
    float getOffset() const { return getProperty("offset").toFloat(); }

    // Contrast
    void setContrast(float contrast);
    float getContrast() const { return getProperty("contrast").toFloat(); }

    // Gamma
    void setGamma(float gamma);
    float getGamma() const { return getProperty("gamma").toFloat(); }

    // Highlights/Shadows
    void setHighlights(float highlights);
    void setShadows(float shadows);

    // Clipping
    void setClipBlack(float clip);
    void setClipWhite(float clip);

protected:
    bool processImage(cv::Mat& output, int frame) override;

private:
    float tonemap(float value, float exposure, float gamma);
    float highlightCompress(float value, float compression);
};

#endif // EXPOSURE_NODE_H
