#ifndef VIEWER_PANEL_H
#define VIEWER_PANEL_H

#include <QDockWidget>
#include <QWidget>
#include <QLabel>
#include <QSlider>
#include <opencv2/core.hpp>

/**
 * @class ViewerPanel
 * @brief Panel for viewing rendered output
 */
class ViewerPanel : public QDockWidget
{
    Q_OBJECT

public:
    explicit ViewerPanel(QWidget* parent = nullptr);
    ~ViewerPanel();

    void setImage(const QImage& image);
    void setFrame(const cv::Mat& frame);
    void clear();

public slots:
    void onZoomIn();
    void onZoomOut();
    void onFitToView();
    void onSetZoom(int zoom);

signals:
    void zoomChanged(int zoom);

private:
    void createToolbar();
    void updateDisplay();

private:
    QWidget* m_viewerWidget;
    QLabel* m_infoLabel;
    QSlider* m_zoomSlider;
    QImage m_currentImage;
    int m_zoomLevel;
};

#endif // VIEWER_PANEL_H