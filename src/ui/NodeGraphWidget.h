#pragma once

#include <QGraphicsView>
#include <QGraphicsScene>
#include <memory>
#include <unordered_map>

class NodeGraph;
class NodeItem;
class ConnectionItem;

/**
 * @class NodeGraphWidget
 * @brief Widget para edición visual del grafo de nodos
 */
class NodeGraphWidget : public QGraphicsView {
    Q_OBJECT

public:
    NodeGraphWidget(QWidget* parent = nullptr);
    virtual ~NodeGraphWidget();

    void setNodeGraph(std::shared_ptr<NodeGraph> graph);
    void refresh();

    // Operaciones
    void addNode(const std::string& nodeType);
    void deleteSelectedNodes();
    void duplicateSelectedNodes();

protected:
    void mousePressEvent(QMouseEvent* event) override;
    void mouseMoveEvent(QMouseEvent* event) override;
    void mouseReleaseEvent(QMouseEvent* event) override;
    void wheelEvent(QWheelEvent* event) override;
    void contextMenuEvent(QContextMenuEvent* event) override;
    void dragEnterEvent(QDragEnterEvent* event) override;
    void dropEvent(QDropEvent* event) override;

private:
    void setupScene();
    void createConnections();

    std::shared_ptr<NodeGraph> nodeGraph;
    QGraphicsScene* scene = nullptr;
    std::unordered_map<std::string, NodeItem*> nodeItems;
    
    NodeItem* draggingNode = nullptr;
    QPointF dragStartPos;

signals:
    void nodeSelected(const std::string& nodeId);
    void nodeDoubleClicked(const std::string& nodeId);
};
