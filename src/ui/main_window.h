#ifndef MAIN_WINDOW_H
#define MAIN_WINDOW_H

#include <QMainWindow>
#include <QDockWidget>
#include <memory>

class NodeGraphPanel;
class PropertiesPanel;
class TimelinePanel;
class ViewerPanel;
class MediaPanel;
class NodeGraph;

/**
 * @class MainWindow
 * @brief Main application window for NUKE-PRO
 */
class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget* parent = nullptr);
    virtual ~MainWindow();

    void setupUI();
    void createMenuBar();
    void createDockPanels();
    void createConnections();

protected:
    void closeEvent(QCloseEvent* event) override;
    void dragEnterEvent(QDragEnterEvent* event) override;
    void dropEvent(QDropEvent* event) override;

private slots:
    void onFileNew();
    void onFileOpen();
    void onFileSave();
    void onFileSaveAs();
    void onFileExport();
    void onEditUndo();
    void onEditRedo();
    void onHelpAbout();

private:
    void applyDarkTheme();
    void loadSettings();
    void saveSettings();

    // UI Components
    NodeGraphPanel* m_nodeGraphPanel;
    PropertiesPanel* m_propertiesPanel;
    TimelinePanel* m_timelinePanel;
    ViewerPanel* m_viewerPanel;
    MediaPanel* m_mediaPanel;

    // Core
    std::shared_ptr<NodeGraph> m_nodeGraph;
};

#endif // MAIN_WINDOW_H
