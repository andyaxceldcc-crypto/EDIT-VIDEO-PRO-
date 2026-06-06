#include "viewer_node.h"
#include <opencv2/imgproc.hpp>
#include <cmath>
#include <QDebug>

ViewerNode::ViewerNode(const QString& name)
    : NodeBase(NodeType::VIEWER, name)
{
    addInput("image", 4);
    addOutput("display", 4);

    setProperty("display_mode", static_cast<int>(COLOR));
    setProperty("colorspace", static_cast<int>(LINEAR));
    setProperty("zoom", 1.0f);
    setProperty("pan_x", 0.0f);
    setProperty("pan_y", 0.0f);
    setProperty("exposure", 0.0f);
    setProperty("gamma", 1.0f);
    setProperty("lut_file", "");
    setProperty("display_lut", false);
    setProperty("show_histogram", false);
    setProperty("show_waveform", false);
    setProperty("show_vectorscope", false);
}

ViewerNode::~ViewerNode()
{
}

void ViewerNode::setDisplayMode(DisplayMode mode)
{
    setProperty("display_mode", static_cast<int>(mode));
}

ViewerNode::DisplayMode ViewerNode::getDisplayMode() const
{
    return static_cast<DisplayMode>(getProperty("display_mode").toInt());
}

void ViewerNode::setColorspace(Colorspace cs)
{
    setProperty("colorspace", static_cast<int>(cs));
}

ViewerNode::Colorspace ViewerNode::getColorspace() const
{
    return static_cast<Colorspace>(getProperty("colorspace").toInt());
}

void ViewerNode::setZoom(float zoom)
{
    setProperty("zoom", qBound(0.1f, zoom, 10.0f));
}

void ViewerNode::setPan(float x, float y)
{
    setProperty("pan_x", x);
    setProperty("pan_y", y);
}

void ViewerNode::setExposure(float exposure)
{
    setProperty("exposure", exposure);
}

void ViewerNode::setGamma(float gamma)
{
    setProperty("gamma", qBound(0.1f, gamma, 5.0f));
}

void ViewerNode::setLUTFile(const QString& path)
{
    setProperty("lut_file", path);
}

void ViewerNode::setDisplayLUT(bool enabled)
{
    setProperty("display_lut", enabled);
}

void ViewerNode::enableHistogram(bool enabled)
{
    setProperty("show_histogram", enabled);
}

void ViewerNode::enableWaveform(bool enabled)
{
    setProperty("show_waveform", enabled);
}

void ViewerNode::enableVectorscope(bool enabled)
{
    setProperty("show_vectorscope", enabled);
}

bool ViewerNode::processImage(cv::Mat& output, int frame)
{
    cv::Mat input = getInputImage(0, frame);
    if (input.empty())
    {
        return false;
    }

    m_displayImage = input.clone();

    // Apply colorspace
    m_displayImage = applyColorspace(m_displayImage);

    // Apply exposure/gamma
    float exposure = getExposure();
    float gamma = getGamma();
    if (exposure != 0.0f || gamma != 1.0f)
    {
        m_displayImage = applyExposure(m_displayImage, exposure, gamma);
    }

    // Apply LUT if enabled
    if (getProperty("display_lut").toBool())
    {
        m_displayImage = applyLUT(m_displayImage);
    }

    // Generate analysis data
    if (getProperty("show_histogram").toBool())
    {
        m_histogram = generateHistogram(m_displayImage);
    }

    if (getProperty("show_waveform").toBool())
    {
        m_waveform = generateWaveform(m_displayImage);
    }

    output = m_displayImage;
    return true;
}

cv::Mat ViewerNode::applyColorspace(const cv::Mat& input)
{
    cv::Mat output = input.clone();
    Colorspace cs = getColorspace();
    DisplayMode mode = getDisplayMode();

    if (mode == RED)
    {
        // Extract red channel
        std::vector<cv::Mat> channels;
        cv::split(input, channels);
        if (channels.size() > 0)
        {
            output = channels[2];  // R in RGBA
        }
    }
    else if (mode == GREEN)
    {
        std::vector<cv::Mat> channels;
        cv::split(input, channels);
        if (channels.size() > 1)
        {
            output = channels[1];  // G in RGBA
        }
    }
    else if (mode == BLUE)
    {
        std::vector<cv::Mat> channels;
        cv::split(input, channels);
        if (channels.size() > 0)
        {
            output = channels[0];  // B in RGBA
        }
    }
    else if (mode == ALPHA)
    {
        std::vector<cv::Mat> channels;
        cv::split(input, channels);
        if (channels.size() > 3)
        {
            output = channels[3];  // A in RGBA
        }
    }
    else if (mode == LUMINANCE)
    {
        // Convert to grayscale (luminance)
        cv::Mat gray;
        cv::cvtColor(input, gray, cv::COLOR_RGBA2GRAY);
        cv::cvtColor(gray, output, cv::COLOR_GRAY2RGBA);
    }

    return output;
}

cv::Mat ViewerNode::applyExposure(const cv::Mat& input, float exposure, float gamma)
{
    cv::Mat output = input.clone();
    float multiplier = std::pow(2.0f, exposure);
    float invGamma = 1.0f / gamma;

    for (int y = 0; y < output.rows; y++)
    {
        for (int x = 0; x < output.cols; x++)
        {
            cv::Vec4f pixel = output.at<cv::Vec4f>(y, x);
            
            // Apply exposure
            pixel[0] *= multiplier;
            pixel[1] *= multiplier;
            pixel[2] *= multiplier;

            // Apply gamma
            pixel[0] = std::pow(pixel[0], invGamma);
            pixel[1] = std::pow(pixel[1], invGamma);
            pixel[2] = std::pow(pixel[2], invGamma);

            output.at<cv::Vec4f>(y, x) = pixel;
        }
    }

    return output;
}

cv::Mat ViewerNode::applyLUT(const cv::Mat& input)
{
    // LUT application implementation
    return input.clone();
}

cv::Mat ViewerNode::generateHistogram(const cv::Mat& input)
{
    cv::Mat hist;
    int histSize = 256;
    float range[] = {0, 256};
    const float* ranges = range;

    // Calculate histogram for each channel
    std::vector<cv::Mat> channels;
    cv::split(input, channels);

    cv::Mat histR, histG, histB;
    if (channels.size() > 0)
        cv::calcHist(&channels[0], 1, 0, cv::Mat(), histR, 1, &histSize, &ranges);
    if (channels.size() > 1)
        cv::calcHist(&channels[1], 1, 0, cv::Mat(), histG, 1, &histSize, &ranges);
    if (channels.size() > 2)
        cv::calcHist(&channels[2], 1, 0, cv::Mat(), histB, 1, &histSize, &ranges);

    return histR;
}

cv::Mat ViewerNode::generateWaveform(const cv::Mat& input)
{
    // Waveform generation (advanced visualization)
    cv::Mat waveform(input.rows, input.cols, CV_32F, cv::Scalar(0));
    return waveform;
}
