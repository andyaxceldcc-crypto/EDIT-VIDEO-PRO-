#ifndef TIMELINE_PANEL_H
#define TIMELINE_PANEL_H

#include <QDockWidget>
#include <QWidget>
#include <QSlider>
#include <QSpinBox>
#include <QLabel>
#include <QPushButton>

/**
 * @class TimelinePanel
 * @brief Panel for timeline navigation and playback control
 */
class TimelinePanel : public QDockWidget
{
    Q_OBJECT

public:
    explicit TimelinePanel(QWidget* parent = nullptr);
    ~TimelinePanel();

    void setFrameRange(int start, int end);
    void setCurrentFrame(int frame);
    int getCurrentFrame() const;

public slots:
    void onPlay();
    void onStop();
    void onFrameChanged(int frame);

signals:
    void frameChanged(int frame);
    void playbackStarted();
    void playbackStopped();

private:
    void createControls();
    void updateTimeDisplay();

private:
    QSlider* m_frameSlider;
    QSpinBox* m_frameSpinBox;
    QLabel* m_currentTimeLabel;
    QLabel* m_durationLabel;
    QPushButton* m_playButton;
    QPushButton* m_stopButton;
    
    int m_startFrame;
    int m_endFrame;
    int m_currentFrame;
    int m_playbackSpeed;
};

#endif // TIMELINE_PANEL_H