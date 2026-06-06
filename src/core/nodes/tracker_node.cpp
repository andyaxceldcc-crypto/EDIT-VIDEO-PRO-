#include "tracker_node.h"
#include <opencv2/imgproc.hpp>
#include <opencv2/tracking.hpp>

TrackerNode::TrackerNode(const QString& name)
    : NodeBase(NodeType::TRACKER, name)
{
    addInput("input", 4);
    addOutput("output", 4);
    addOutput("track_data", 1);

    setProperty("stabilize", false);
    setProperty("search_width", 50.0f);
    setProperty("search_height", 50.0f);
}

TrackerNode::~TrackerNode()
{
}

void TrackerNode::setTrackPattern(const cv::Mat& pattern)
{
    m_trackPattern = pattern.clone();
    markDirty();
}

void TrackerNode::setSearchArea(float width, float height)
{
    setProperty("search_width", width);
    setProperty("search_height", height);
}

TrackerNode::TrackPoint TrackerNode::getTrackPoint(int frame) const
{
    for (const TrackPoint& tp : m_trackPoints)
    {
        if (tp.frame == frame)
        {
            return tp;
        }
    }
    return TrackPoint{0, 0, 0, 0, frame};
}

void TrackerNode::setStabilizeMode(bool enabled)
{
    setProperty("stabilize", enabled);
}

bool TrackerNode::processImage(cv::Mat& output, int frame)
{
    cv::Mat input = getInputImage(0, frame);
    if (input.empty())
    {
        return false;
    }

    output = trackFrame(input, frame);
    return true;
}

cv::Mat TrackerNode::trackFrame(const cv::Mat& current, int frame)
{
    if (m_trackPattern.empty())
    {
        return current.clone();
    }

    // Track using correlation
    cv::Mat result = correlationTrack(m_trackPattern, current);
    return result;
}

cv::Mat TrackerNode::correlationTrack(const cv::Mat& template_, const cv::Mat& image)
{
    cv::Mat result;
    cv::matchTemplate(image, template_, result, cv::TM_CCOEFF_NORMED);
    return result;
}
