#include "grade_node.h"
#include <opencv2/imgproc.hpp>
#include <cmath>

GradeNode::GradeNode(const QString& name)
    : NodeBase(NodeType::GRADE, name)
{
    addInput("input", 4);
    addOutput("output", 4);

    // Initialize properties
    setProperty("lift_r", 0.0f);
    setProperty("lift_g", 0.0f);
    setProperty("lift_b", 0.0f);
    setProperty("gamma_r", 1.0f);
    setProperty("gamma_g", 1.0f);
    setProperty("gamma_b", 1.0f);
    setProperty("gain_r", 1.0f);
    setProperty("gain_g", 1.0f);
    setProperty("gain_b", 1.0f);
    setProperty("contrast", 1.0f);
    setProperty("saturation", 1.0f);
    setProperty("exposure", 0.0f);
}

GradeNode::~GradeNode()
{
}

void GradeNode::setLift(float r, float g, float b)
{
    setProperty("lift_r", r);
    setProperty("lift_g", g);
    setProperty("lift_b", b);
}

void GradeNode::setGamma(float r, float g, float b)
{
    setProperty("gamma_r", r);
    setProperty("gamma_g", g);
    setProperty("gamma_b", b);
}

void GradeNode::setGain(float r, float g, float b)
{
    setProperty("gain_r", r);
    setProperty("gain_g", g);
    setProperty("gain_b", b);
}

void GradeNode::setShadows(float r, float g, float b)
{
    setProperty("shadows_r", r);
    setProperty("shadows_g", g);
    setProperty("shadows_b", b);
}

void GradeNode::setMidtones(float r, float g, float b)
{
    setProperty("midtones_r", r);
    setProperty("midtones_g", g);
    setProperty("midtones_b", b);
}

void GradeNode::setHighlights(float r, float g, float b)
{
    setProperty("highlights_r", r);
    setProperty("highlights_g", g);
    setProperty("highlights_b", b);
}

void GradeNode::setContrast(float contrast)
{
    setProperty("contrast", contrast);
}

void GradeNode::setSaturation(float saturation)
{
    setProperty("saturation", saturation);
}

void GradeNode::setExposure(float exposure)
{
    setProperty("exposure", exposure);
}

bool GradeNode::processImage(cv::Mat& output, int frame)
{
    cv::Mat input = getInputImage(0, frame);
    if (input.empty())
    {
        return false;
    }

    output = input.clone();

    // Apply exposure
    float exposure = getProperty("exposure").toFloat();
    if (exposure != 0.0f)
    {
        output = adjustExposure(output, exposure);
    }

    // Apply saturation
    float saturation = getProperty("saturation").toFloat();
    if (saturation != 1.0f)
    {
        output = adjustSaturation(output, saturation);
    }

    return true;
}

cv::Mat GradeNode::applyCDL(const cv::Mat& input)
{
    cv::Mat output = input.clone();
    return output;
}

cv::Mat GradeNode::adjustExposure(const cv::Mat& input, float exposure)
{
    cv::Mat output;
    float multiplier = std::pow(2.0f, exposure);
    input.convertTo(output, -1, multiplier, 0);
    return output;
}

cv::Mat GradeNode::adjustSaturation(const cv::Mat& input, float saturation)
{
    cv::Mat output = input.clone();
    // Saturation adjustment implementation
    return output;
}
