#include "hue_saturation_node.h"
#include <cmath>

HueSaturationNode::HueSaturationNode(const QString& name)
    : NodeBase(NodeType::CUSTOM, name)
{
    addInput("input", 4);
    addOutput("output", 4);

    setProperty("hue", 0.0f);
    setProperty("saturation", 1.0f);
    setProperty("lightness", 0.0f);
    setProperty("mode", "master");
    setProperty("red_hue", 0.0f);
    setProperty("green_hue", 0.0f);
    setProperty("blue_hue", 0.0f);
}

HueSaturationNode::~HueSaturationNode()
{
}

void HueSaturationNode::setHue(float hue)
{
    setProperty("hue", hue);
}

void HueSaturationNode::setSaturation(float saturation)
{
    setProperty("saturation", qBound(0.0f, saturation, 2.0f));
}

void HueSaturationNode::setLightness(float lightness)
{
    setProperty("lightness", qBound(-1.0f, lightness, 1.0f));
}

void HueSaturationNode::setRedHue(float hue)
{
    setProperty("red_hue", hue);
}

void HueSaturationNode::setGreenHue(float hue)
{
    setProperty("green_hue", hue);
}

void HueSaturationNode::setBlueHue(float hue)
{
    setProperty("blue_hue", hue);
}

void HueSaturationNode::setYellowHue(float hue)
{
    setProperty("yellow_hue", hue);
}

void HueSaturationNode::setCyanHue(float hue)
{
    setProperty("cyan_hue", hue);
}

void HueSaturationNode::setMagentaHue(float hue)
{
    setProperty("magenta_hue", hue);
}

void HueSaturationNode::setMode(const QString& mode)
{
    setProperty("mode", mode);
}

bool HueSaturationNode::processImage(cv::Mat& output, int frame)
{
    cv::Mat input = getInputImage(0, frame);
    if (input.empty())
    {
        return false;
    }

    output = input.clone();

    // Convert to HSV
    cv::Mat hsv = rgbToHSV(output);

    float hue = getHue();
    float saturation = getSaturation();
    float lightness = getLightness();

    for (int y = 0; y < hsv.rows; y++)
    {
        for (int x = 0; x < hsv.cols; x++)
        {
            cv::Vec4f pixel = hsv.at<cv::Vec4f>(y, x);

            // Adjust hue
            pixel[0] += hue;
            if (pixel[0] < 0.0f)
                pixel[0] += 1.0f;
            else if (pixel[0] > 1.0f)
                pixel[0] -= 1.0f;

            // Adjust saturation
            pixel[1] *= saturation;
            pixel[1] = std::min(1.0f, pixel[1]);

            // Adjust lightness/value
            pixel[2] += lightness;
            pixel[2] = std::max(0.0f, std::min(1.0f, pixel[2]));

            hsv.at<cv::Vec4f>(y, x) = pixel;
        }
    }

    // Convert back to RGB
    output = hsvToRGB(hsv);
    return true;
}

cv::Mat HueSaturationNode::rgbToHSV(const cv::Mat& rgb)
{
    cv::Mat hsv = rgb.clone();

    for (int y = 0; y < rgb.rows; y++)
    {
        for (int x = 0; x < rgb.cols; x++)
        {
            cv::Vec4f pixel = rgb.at<cv::Vec4f>(y, x);
            float r = pixel[2];
            float g = pixel[1];
            float b = pixel[0];

            float cmax = std::max({r, g, b});
            float cmin = std::min({r, g, b});
            float delta = cmax - cmin;

            // Hue
            float h = 0.0f;
            if (delta > 0.0f)
            {
                if (cmax == r)
                    h = std::fmod((g - b) / delta, 6.0f) / 6.0f;
                else if (cmax == g)
                    h = ((b - r) / delta + 2.0f) / 6.0f;
                else
                    h = ((r - g) / delta + 4.0f) / 6.0f;
            }

            // Saturation
            float s = (cmax > 0.0f) ? (delta / cmax) : 0.0f;

            // Value
            float v = cmax;

            hsv.at<cv::Vec4f>(y, x) = cv::Vec4f(b, h, s, v);
        }
    }

    return hsv;
}

cv::Mat HueSaturationNode::hsvToRGB(const cv::Mat& hsv)
{
    cv::Mat rgb = hsv.clone();

    for (int y = 0; y < hsv.rows; y++)
    {
        for (int x = 0; x < hsv.cols; x++)
        {
            cv::Vec4f pixel = hsv.at<cv::Vec4f>(y, x);
            float h = pixel[1] * 6.0f;
            float s = pixel[2];
            float v = pixel[3];

            float c = v * s;
            float x_val = c * (1.0f - std::fabs(std::fmod(h, 2.0f) - 1.0f));
            float m = v - c;

            float r = 0.0f, g = 0.0f, b = 0.0f;

            if (h >= 0 && h < 1)
                r = c, g = x_val, b = 0;
            else if (h >= 1 && h < 2)
                r = x_val, g = c, b = 0;
            else if (h >= 2 && h < 3)
                r = 0, g = c, b = x_val;
            else if (h >= 3 && h < 4)
                r = 0, g = x_val, b = c;
            else if (h >= 4 && h < 5)
                r = x_val, g = 0, b = c;
            else
                r = c, g = 0, b = x_val;

            rgb.at<cv::Vec4f>(y, x) = cv::Vec4f(b + m, g + m, r + m, pixel[0]);
        }
    }

    return rgb;
}

float HueSaturationNode::adjustHueRange(float hue, float rangeCenter, float rangeWidth, float adjustment)
{
    float distance = std::abs(hue - rangeCenter);
    if (distance > 0.5f)
        distance = 1.0f - distance;

    if (distance < rangeWidth)
    {
        float influence = 1.0f - (distance / rangeWidth);
        return hue + adjustment * influence;
    }

    return hue;
}
