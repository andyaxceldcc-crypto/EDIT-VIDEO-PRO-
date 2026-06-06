#ifndef HUE_SATURATION_NODE_H
#define HUE_SATURATION_NODE_H

#include "node_base.h"
#include <QString>

/**
 * @class HueSaturationNode
 * @brief Hue, Saturation, and Lightness adjustment
 * Similar to Nuke HueShift, Blender Hue/Saturation
 */
class HueSaturationNode : public NodeBase
{
public:
    HueSaturationNode(const QString& name = "HueSaturation");
    virtual ~HueSaturationNode();

    // Global adjustments
    void setHue(float hue);
    float getHue() const { return getProperty("hue").toFloat(); }

    void setSaturation(float saturation);
    float getSaturation() const { return getProperty("saturation").toFloat(); }

    void setLightness(float lightness);
    float getLightness() const { return getProperty("lightness").toFloat(); }

    // Range-specific adjustments
    void setRedHue(float hue);
    void setGreenHue(float hue);
    void setBlueHue(float hue);
    void setYellowHue(float hue);
    void setCyanHue(float hue);
    void setMagentaHue(float hue);

    // Master vs individual
    void setMode(const QString& mode);  // "master", "red", "green", "blue", etc.

protected:
    bool processImage(cv::Mat& output, int frame) override;

private:
    cv::Mat rgbToHSV(const cv::Mat& rgb);
    cv::Mat hsvToRGB(const cv::Mat& hsv);
    float adjustHueRange(float hue, float rangeCenter, float rangeWidth, float adjustment);
};

#endif // HUE_SATURATION_NODE_H
