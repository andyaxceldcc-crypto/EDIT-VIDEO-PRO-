#ifndef VIDEOTIMELINE_H
#define VIDEOTIMELINE_H

#include <QWidget>
#include <QList>
#include <QPoint>

struct TimelineClip
{
    QString filename;
    double startTime;
    double duration;
    int track;
};

class VideoTimeline : public QWidget
{
    Q_OBJECT

public:
    explicit VideoTimeline(QWidget *parent = nullptr);
    void addClip(const QString &filename, double startTime, double duration, int track = 0);
    void removeClip(int index);
    void setCurrentTime(double time);
    double getCurrentTime() const;

protected:
    void paintEvent(QPaintEvent *event) override;
    void mousePressEvent(QMouseEvent *event) override;
    void mouseMoveEvent(QMouseEvent *event) override;
    void wheelEvent(QWheelEvent *event) override;

signals:
    void timeClicked(double time);
    void clipSelected(int clipIndex);

private:
    QList<TimelineClip> clips;
    double currentTime;
    double zoomLevel;
    int selectedClip;
    
    void drawTimeline(QPainter &painter);
    void drawClips(QPainter &painter);
    void drawPlayhead(QPainter &painter);
};

#endif // VIDEOTIMELINE_H
