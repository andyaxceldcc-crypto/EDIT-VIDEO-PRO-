#ifndef NODE_GRAPH_PANEL_H
#define NODE_GRAPH_PANEL_H

#include <QDockWidget>
#include <QGraphicsView>
#include <QGraphicsScene>
#include <QToolBar>

class NodeGraph;

/**
 * @class NodeGraphPanel
 * @brief Panel containing the node graph editor
 */
class NodeGraphPanel : public QDockWidget
{
    Q_OBJECT

public:
    explicit NodeGraphPanel(QWidget* parent = nullptr);
    ~NodeGraphPanel();

    void setNodeGraph(std::shared_ptr<NodeGraph> graph);

public slots:
    void onAddNode(const QString& nodeType);
    void onDeleteSelected();
    void onZoomIn();
    void onZoomOut();
    void onFitToView();

private:
    void createToolbar();
    void setupScene();
    void updateFromGraph();

private:
    QGraphicsView* m_view;
    QGraphicsScene* m_scene;
    QToolBar* m_toolbar;
    std::shared_ptr<NodeGraph> m_nodeGraph;
};

#endif // NODE_GRAPH_PANEL_H