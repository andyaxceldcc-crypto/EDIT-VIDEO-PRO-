#include "viewer_panel.h"
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QToolBar>
#include <QPainter>
#include <QPaintEvent>

class ViewerWidget : public QWidget {
protected:
    void paintEvent(QPaintEvent* event) override {
        QPainter painter(this);
        painter.fillRect(event->rect(), Qt::black);
    }
};

ViewerPanel::ViewerPanel(QWidget* parent)
    : QDockWidget(tr("Viewer"), parent)
    , m_viewerWidget(nullptr)
    , m_infoLabel(nullptr)
    , m_zoomSlider(nullptr)
    , m_zoomLevel(100)
{
    setObjectName("ViewerPanel");
    
    QWidget* widget = new QWidget(this);
    QVBoxLayout* mainLayout = new QVBoxLayout(widget);
    
    createToolbar();
    
    m_viewerWidget = new ViewerWidget();
    m_viewerWidget->setMinimumSize(400, 300);
    mainLayout->addWidget(m_viewerWidget);
    
    m_infoLabel = new QLabel("No image loaded", this);
    m_infoLabel->setAlignment(Qt::AlignCenter);
    m_infoLabel->setStyleSheet("background-color: #000; color: #888; padding: 5px;");
    mainLayout->addWidget(m_infoLabel);
    
    QHBoxLayout* zoomLayout = new QHBoxLayout();
    zoomLayout->addWidget(new QLabel("Zoom:", this));
    
    m_zoomSlider = new QSlider(Qt::Horizontal, this);
    m_zoomSlider->setRange(10, 400);
    m_zoomSlider->setValue(100);
    connect(m_zoomSlider, &QSlider::valueChanged, this, &ViewerPanel::onSetZoom);
    zoomLayout->addWidget(m_zoomSlider);
    
    QLabel* zoomLabel = new QLabel("100%", this);
    zoomLabel->setMinimumWidth(50);
    zoomLayout->addWidget(zoomLabel);
    
    mainLayout->addLayout(zoomLayout);
    
    setWidget(widget);
}

ViewerPanel::~ViewerPanel()
{
}

void ViewerPanel::createToolbar()
{
    // Toolbar is simplified for this implementation
}

void ViewerPanel::setImage(const QImage& image)
{
    m_currentImage = image;
    
    if (!image.isNull()) {
        m_infoLabel->setText(QString("%1 x %2").arg(image.width()).arg(image.height()));
    }
    
    updateDisplay();
}

void ViewerPanel::setFrame(const cv::Mat& frame)
{
    if (frame.empty()) {
        clear();
        return;
    }
    
    cv::Mat rgbFrame;
    cv::cvtColor(frame, rgbFrame, cv::COLOR_BGR2RGB);
    
    QImage image(rgbFrame.data, rgbFrame.cols, rgbFrame.rows, 
                 rgbFrame.step, QImage::Format_RGB888);
    
    setImage(image.copy());
}

void ViewerPanel::clear()
{
    m_currentImage = QImage();
    m_infoLabel->setText("No image loaded");
    updateDisplay();
}

void ViewerPanel::onZoomIn()
{
    m_zoomLevel = qMin(400, m_zoomLevel + 25);
    m_zoomSlider->setValue(m_zoomLevel);
}

void ViewerPanel::onZoomOut()
{
    m_zoomLevel = qMax(10, m_zoomLevel - 25);
    m_zoomSlider->setValue(m_zoomLevel);
}

void ViewerPanel::onFitToView()
{
    if (m_currentImage.isNull()) return;
    
    double scaleX = (double)m_viewerWidget->width() / m_currentImage.width();
    double scaleY = (double)m_viewerWidget->height() / m_currentImage.height();
    double scale = qMin(scaleX, scaleY) * 100;
    
    m_zoomLevel = int(scale);
    m_zoomSlider->setValue(m_zoomLevel);
}

void ViewerPanel::onSetZoom(int zoom)
{
    m_zoomLevel = zoom;
    emit zoomChanged(zoom);
    updateDisplay();
}

void ViewerPanel::updateDisplay()
{
    if (m_viewerWidget) {
        m_viewerWidget->update();
    }
}