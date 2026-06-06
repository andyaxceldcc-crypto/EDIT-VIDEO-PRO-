#pragma once

#include <QMainWindow>
#include <memory>

class NodeGraphWidget;
class ViewerWidget;
class PropertiesPanel;
class TimelineWidget;

/**
 * @class MainWindow
 * @brief Ventana principal de la aplicación
 */
class MainWindow : public QMainWindow {
    Q_OBJECT

public:
    MainWindow(QWidget* parent = nullptr);
    virtual ~MainWindow();

protected:
    void closeEvent(QCloseEvent* event) override;
    void dragEnterEvent(QDragEnterEvent* event) override;
    void dropEvent(QDropEvent* event) override;

private:
    void setupUI();
    void createMenuBar();
    void createDockWidgets();
    void connectSignals();
    void loadSettings();
    void saveSettings();

    // Widgets
    NodeGraphWidget* nodeGraphWidget = nullptr;
    ViewerWidget* viewerWidget = nullptr;
    PropertiesPanel* propertiesPanel = nullptr;
    TimelineWidget* timelineWidget = nullptr;

private slots:
    void onNewProject();
    void onOpenProject();
    void onSaveProject();
    void onSaveAsProject();
    void onNodeSelected(const std::string& nodeId);
    void onFrameChanged(int frame);
};
