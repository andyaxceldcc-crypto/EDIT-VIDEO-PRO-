#pragma once

#include <QOpenGLWidget>
#include <memory>
#include <glm/glm.hpp>

class FrameBuffer;
class NodeGraph;

/**
 * @class ViewerWidget
 * @brief Visor interactivo de composición
 */
class ViewerWidget : public QOpenGLWidget {
    Q_OBJECT

public:
    ViewerWidget(QWidget* parent = nullptr);
    virtual ~ViewerWidget();

    void setNodeGraph(std::shared_ptr<NodeGraph> graph);
    void setDisplayNode(const std::string& nodeId);
    void setFrame(int frame);
    void setZoom(float zoom);
    float getZoom() const { return zoomLevel; }
    
    enum class FitMode {
        ACTUAL_SIZE,
        FIT_WINDOW,
        FILL_WINDOW
    };
    void setFitMode(FitMode mode) { fitMode = mode; update(); }

protected:
    void initializeGL() override;
    void resizeGL(int w, int h) override;
    void paintGL() override;

    void mousePressEvent(QMouseEvent* event) override;
    void mouseMoveEvent(QMouseEvent* event) override;
    void wheelEvent(QWheelEvent* event) override;

private:
    void updateDisplay();
    void setupShaders();
    void renderToTexture();

    std::shared_ptr<NodeGraph> nodeGraph;
    std::shared_ptr<FrameBuffer> displayFrame;
    std::string displayNodeId;
    
    int currentFrame = 1;
    float zoomLevel = 1.0f;
    glm::vec2 panOffset = glm::vec2(0.0f);
    FitMode fitMode = FitMode::FIT_WINDOW;
    
    unsigned int displayTexture = 0;
    unsigned int shaderProgram = 0;
};
