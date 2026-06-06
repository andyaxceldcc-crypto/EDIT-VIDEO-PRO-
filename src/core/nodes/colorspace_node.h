#ifndef COLORSPACE_NODE_H
#define COLORSPACE_NODE_H

#include "node_base.h"
#include <QString>

/**
 * @class ColorspaceNode
 * @brief Color space conversion node
 * Supports: sRGB, Linear, Rec709, DCI-P3, ACES, Log
 */
class ColorspaceNode : public NodeBase
{
public:
    enum ColorSpace {
        LINEAR,
        SRGB,
        REC709,
        DCI_P3,
        ACES_AP0,
        ACES_AP1,
        LOG_C,
        ALEXA_LOG_C,
        RED_LOG3G10,
        SONY_SLOG3
    };

    ColorspaceNode(const QString& name = "Colorspace");
    virtual ~ColorspaceNode();

    void setInputColorspace(ColorSpace cs);
    ColorSpace getInputColorspace() const;

    void setOutputColorspace(ColorSpace cs);
    ColorSpace getOutputColorspace() const;

    void enableLinearization(bool enabled);
    void setLUTFile(const QString& path);

protected:
    bool processImage(cv::Mat& output, int frame) override;

private:
    cv::Mat convertColorspace(const cv::Mat& input, ColorSpace from, ColorSpace to);
    cv::Mat linearToSRGB(const cv::Mat& input);
    cv::Mat sRGBToLinear(const cv::Mat& input);
    cv::Mat applyACES(const cv::Mat& input);
};

#endif // COLORSPACE_NODE_H
