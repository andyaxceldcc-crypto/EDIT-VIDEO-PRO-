#include "timeline_panel.h"
#include <QVBoxLayout>
#include <QHBoxLayout>

TimelinePanel::TimelinePanel(QWidget* parent)
    : QDockWidget(tr("Timeline"), parent)
    , m_frameSlider(nullptr)
    , m_frameSpinBox(nullptr)
    , m_currentTimeLabel(nullptr)
    , m_durationLabel(nullptr)
    , m_playButton(nullptr)
    , m_stopButton(nullptr)
    , m_startFrame(0)
    , m_endFrame(100)
    , m_currentFrame(0)
    , m_playbackSpeed(24)
{
    setObjectName("TimelinePanel");
    
    QWidget* widget = new QWidget(this);
    QVBoxLayout* mainLayout = new QVBoxLayout(widget);
    
    createControls();
    
    mainLayout->addWidget(m_frameSlider);
    
    QHBoxLayout* controlsLayout = new QHBoxLayout();
    controlsLayout->addWidget(m_playButton);
    controlsLayout->addWidget(m_stopButton);
    controlsLayout->addWidget(m_frameSpinBox);
    controlsLayout->addWidget(m_currentTimeLabel);
    controlsLayout->addWidget(new QLabel("/"));
    controlsLayout->addWidget(m_durationLabel);
    
    mainLayout->addLayout(controlsLayout);
    
    setWidget(widget);
}

TimelinePanel::~TimelinePanel()
{
}

void TimelinePanel::createControls()
{
    m_frameSlider = new QSlider(Qt::Horizontal, this);
    m_frameSlider->setRange(m_startFrame, m_endFrame);
    m_frameSlider->setValue(m_currentFrame);
    connect(m_frameSlider, &QSlider::valueChanged, this, &TimelinePanel::onFrameChanged);
    
    m_frameSpinBox = new QSpinBox(this);
    m_frameSpinBox->setRange(m_startFrame, m_endFrame);
    m_frameSpinBox->setValue(m_currentFrame);
    connect(m_frameSpinBox, &QSpinBox::valueChanged, this, &TimelinePanel::onFrameChanged);
    
    m_playButton = new QPushButton("Play", this);
    connect(m_playButton, &QPushButton::clicked, this, &TimelinePanel::onPlay);
    
    m_stopButton = new QPushButton("Stop", this);
    connect(m_stopButton, &QPushButton::clicked, this, &TimelinePanel::onStop);
    
    m_currentTimeLabel = new QLabel("00:00:00", this);
    m_durationLabel = new QLabel("00:00:00", this);
    
    updateTimeDisplay();
}

void TimelinePanel::setFrameRange(int start, int end)
{
    m_startFrame = start;
    m_endFrame = end;
    
    if (m_frameSlider) m_frameSlider->setRange(start, end);
    if (m_frameSpinBox) m_frameSpinBox->setRange(start, end);
    
    updateTimeDisplay();
}

void TimelinePanel::setCurrentFrame(int frame)
{
    m_currentFrame = frame;
    
    if (m_frameSlider) m_frameSlider->setValue(frame);
    if (m_frameSpinBox) m_frameSpinBox->setValue(frame);
    
    updateTimeDisplay();
}

int TimelinePanel::getCurrentFrame() const
{
    return m_currentFrame;
}

void TimelinePanel::onPlay()
{
    emit playbackStarted();
}

void TimelinePanel::onStop()
{
    setCurrentFrame(m_startFrame);
    emit playbackStopped();
}

void TimelinePanel::onFrameChanged(int frame)
{
    m_currentFrame = frame;
    
    if (m_frameSlider && m_frameSlider->value() != frame) m_frameSlider->setValue(frame);
    if (m_frameSpinBox && m_frameSpinBox->value() != frame) m_frameSpinBox->setValue(frame);
    
    updateTimeDisplay();
    emit frameChanged(frame);
}

void TimelinePanel::updateTimeDisplay()
{
    int fps = m_playbackSpeed;
    int currentSeconds = m_currentFrame / fps;
    int currentMinutes = currentSeconds / 60;
    int currentHours = currentMinutes / 60;
    
    int totalSeconds = m_endFrame / fps;
    int totalMinutes = totalSeconds / 60;
    int totalHours = totalMinutes / 60;
    
    QString currentTime = QString("%1:%2:%3")
        .arg(currentHours, 2, 10, QChar('0'))
        .arg(currentMinutes % 60, 2, 10, QChar('0'))
        .arg(currentSeconds % 60, 2, 10, QChar('0'));
    
    QString totalTime = QString("%1:%2:%3")
        .arg(totalHours, 2, 10, QChar('0'))
        .arg(totalMinutes % 60, 2, 10, QChar('0'))
        .arg(totalSeconds % 60, 2, 10, QChar('0'));
    
    if (m_currentTimeLabel) m_currentTimeLabel->setText(currentTime);
    if (m_durationLabel) m_durationLabel->setText(totalTime);
}