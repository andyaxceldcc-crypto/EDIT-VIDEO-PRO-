#ifndef VIEWER_NODE_H
#define VIEWER_NODE_H

#include "node_base.h"
#include <QString>
#include <opencv2/core.hpp>

/**
 * @class ViewerNode
 * @brief Interactive viewer for image preview and analysis
 * Based on Nuke Viewer and Blender compositor preview
 */
class ViewerNode : public NodeBase
{
public:
    enum DisplayMode {
        COLOR,
        RED,
        GREEN,
        BLUE,
        ALPHA,
        LUMINANCE,
        ZEBRA,
        HISTOGRAM,
        WAVEFORM
    };

    enum Colorspace {
        LINEAR,
        SRGB,
        REC709,
        DCI_P3
    };

    ViewerNode(const QString& name = "Viewer");
    virtual ~ViewerNode();

    // Display settings
    void setDisplayMode(DisplayMode mode);
    DisplayMode getDisplayMode() const;

    void setColorspace(Colorspace cs);
    Colorspace getColorspace() const;

    // Zoom & Pan
    void setZoom(float zoom);
    float getZoom() const { return getProperty("zoom").toFloat(); }

    void setPan(float x, float y);

    // Exposure
    void setExposure(float exposure);
    float getExposure() const { return getProperty("exposure").toFloat(); }

    void setGamma(float gamma);
    float getGamma() const { return getProperty("gamma").toFloat(); }

    // LUT
    void setLUTFile(const QString& path);
    void setDisplayLUT(bool enabled);

    // Analysis
    void enableHistogram(bool enabled);
    void enableWaveform(bool enabled);
    void enableVectorscope(bool enabled);

    // Get processed image
    cv::Mat getDisplayImage() const { return m_displayImage; }
    cv::Mat getHistogram() const { return m_histogram; }

protected:
    bool processImage(cv::Mat& output, int frame) override;

private:
    cv::Mat applyColorspace(const cv::Mat& input);
    cv::Mat applyExposure(const cv::Mat& input, float exposure, float gamma);
    cv::Mat applyLUT(const cv::Mat& input);
    cv::Mat generateHistogram(const cv::Mat& input);
    cv::Mat generateWaveform(const cv::Mat& input);

    cv::Mat m_displayImage;
    cv::Mat m_histogram;
    cv::Mat m_waveform;
};

#endif // VIEWER_NODE_H
