#include "videotimeline.h"
#include <QPainter>
#include <QMouseEvent>
#include <QWheelEvent>

VideoTimeline::VideoTimeline(QWidget *parent)
    : QWidget(parent), currentTime(0), zoomLevel(1.0), selectedClip(-1)
{
    setStyleSheet("background-color: #1a1a1a; border: 1px solid #444;");
    setMinimumHeight(150);
}

void VideoTimeline::addClip(const QString &filename, double startTime, double duration, int track)
{
    TimelineClip clip;
    clip.filename = filename;
    clip.startTime = startTime;
    clip.duration = duration;
    clip.track = track;
    clips.append(clip);
    update();
}

void VideoTimeline::removeClip(int index)
{
    if (index >= 0 && index < clips.size()) {
        clips.removeAt(index);
        update();
    }
}

void VideoTimeline::setCurrentTime(double time)
{
    currentTime = time;
    update();
}

double VideoTimeline::getCurrentTime() const
{
    return currentTime;
}

void VideoTimeline::paintEvent(QPaintEvent *event)
{
    QPainter painter(this);
    painter.fillRect(rect(), QColor("#1a1a1a"));
    
    drawTimeline(painter);
    drawClips(painter);
    drawPlayhead(painter);
}

void VideoTimeline::drawTimeline(QPainter &painter)
{
    int y = 20;
    painter.setPen(QPen(QColor("#666"), 1));
    
    // Dibujar marcas de tiempo cada segundo
    double pixelsPerSecond = 50 * zoomLevel;
    
    for (int i = 0; i < 300; i += 5) {
        int x = i * pixelsPerSecond / 5;
        if (x > width()) break;
        
        painter.drawLine(x, y - 5, x, y);
        
        if (i % 20 == 0) {
            painter.setPen(QPen(QColor("#999"), 1));
            painter.drawLine(x, y - 10, x, y);
            painter.drawText(x - 15, y + 15, QString::number(i / 5));
            painter.setPen(QPen(QColor("#666"), 1));
        }
    }
}

void VideoTimeline::drawClips(QPainter &painter)
{
    int trackHeight = 80;
    int yStart = 50;
    
    for (int i = 0; i < clips.size(); ++i) {
        const TimelineClip &clip = clips[i];
        
        double pixelsPerSecond = 50 * zoomLevel;
        int x = clip.startTime * pixelsPerSecond;
        int width = clip.duration * pixelsPerSecond;
        int y = yStart + clip.track * trackHeight;
        
        // Dibujar clip
        QColor color = (i == selectedClip) ? QColor("#0099ff") : QColor("#0066cc");
        painter.fillRect(x, y, width, trackHeight - 5, color);
        painter.drawRect(x, y, width, trackHeight - 5);
        
        // Dibujar nombre del clip
        painter.setPen(Qt::white);
        painter.drawText(x + 5, y + 25, clip.filename.mid(0, 15));
    }
}

void VideoTimeline::drawPlayhead(QPainter &painter)
{
    double pixelsPerSecond = 50 * zoomLevel;
    int x = currentTime * pixelsPerSecond;
    
    painter.setPen(QPen(QColor("#ff0000"), 2));
    painter.drawLine(x, 0, x, height());
}

void VideoTimeline::mousePressEvent(QMouseEvent *event)
{
    double pixelsPerSecond = 50 * zoomLevel;
    currentTime = event->x() / pixelsPerSecond;
    
    // Seleccionar clip
    int trackHeight = 80;
    int yStart = 50;
    
    for (int i = 0; i < clips.size(); ++i) {
        const TimelineClip &clip = clips[i];
        
        int x = clip.startTime * pixelsPerSecond;
        int width = clip.duration * pixelsPerSecond;
        int y = yStart + clip.track * trackHeight;
        
        if (event->x() >= x && event->x() <= x + width &&
            event->y() >= y && event->y() <= y + trackHeight) {
            selectedClip = i;
            emit clipSelected(i);
            break;
        }
    }
    
    emit timeClicked(currentTime);
    update();
}

void VideoTimeline::wheelEvent(QWheelEvent *event)
{
    if (event->angleDelta().y() > 0) {
        zoomLevel *= 1.2;
    } else {
        zoomLevel /= 1.2;
    }
    
    if (zoomLevel < 0.5) zoomLevel = 0.5;
    if (zoomLevel > 5.0) zoomLevel = 5.0;
    
    update();
}

void VideoTimeline::mouseMoveEvent(QMouseEvent *event)
{
    // Implementar arrastre de clips
}
