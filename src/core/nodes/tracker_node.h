#ifndef TRACKER_NODE_H
#define TRACKER_NODE_H

#include "node_base.h"
#include <QString>
#include <QVector>
#include <QPointF>

/**
 * @class TrackerNode
 * @brief Motion tracking node for analyzing and stabilizing footage
 */
class TrackerNode : public NodeBase
{
public:
    struct TrackPoint
    {
        float x, y;
        float vx, vy; // velocity
        int frame;
    };

    TrackerNode(const QString& name = "Tracker");
    virtual ~TrackerNode();

    // Tracking parameters
    void setTrackPattern(const cv::Mat& pattern);
    void setSearchArea(float width, float height);

    // Tracking results
    const QVector<TrackPoint>& getTrackPoints() const { return m_trackPoints; }
    TrackPoint getTrackPoint(int frame) const;

    // Stabilization
    void setStabilizeMode(bool enabled);
    bool getStabilizeMode() const { return getProperty("stabilize").toBool(); }

protected:
    bool processImage(cv::Mat& output, int frame) override;

private:
    cv::Mat trackFrame(const cv::Mat& current, int frame);
    cv::Mat correlationTrack(const cv::Mat& template_, const cv::Mat& image);

    QVector<TrackPoint> m_trackPoints;
    cv::Mat m_trackPattern;
};

#endif // TRACKER_NODE_H
