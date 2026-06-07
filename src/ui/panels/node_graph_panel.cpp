#include "node_graph_panel.h"
#include "../../core/graph/node_graph.h"
#include "../../core/nodes/node_base.h"
#include <QVBoxLayout>
#include <QMenu>
#include <QGraphicsItem>
#include <QDebug>

NodeGraphPanel::NodeGraphPanel(QWidget* parent)
    : QDockWidget(tr("Node Graph"), parent)
    , m_view(nullptr)
    , m_scene(nullptr)
    , m_toolbar(nullptr)
{
    setObjectName("NodeGraphPanel");
    
    QWidget* widget = new QWidget(this);
    QVBoxLayout* layout = new QVBoxLayout(widget);
    
    createToolbar();
    setupScene();
    
    layout->addWidget(m_toolbar);
    layout->addWidget(m_view);
    
    setWidget(widget);
}

NodeGraphPanel::~NodeGraphPanel()
{
}

void NodeGraphPanel::setNodeGraph(std::shared_ptr<NodeGraph> graph)
{
    m_nodeGraph = graph;
    updateFromGraph();
}

void NodeGraphPanel::createToolbar()
{
    m_toolbar = new QToolBar(this);
    
    QMenu* addMenu = new QMenu(this);
    addMenu->addAction("Read", this, [this]() { onAddNode("Read"); });
    addMenu->addAction("Write", this, [this]() { onAddNode("Write"); });
    addMenu->addAction("Viewer", this, [this]() { onAddNode("Viewer"); });
    addMenu->addAction("Grade", this, [this]() { onAddNode("Grade"); });
    addMenu->addAction("Merge", this, [this]() { onAddNode("Merge"); });
    addMenu->addAction("Transform", this, [this]() { onAddNode("Transform"); });
    
    QToolButton* addButton = new QToolButton(this);
    addButton->setText("+ Add Node");
    addButton->setMenu(addMenu);
    addButton->setPopupMode(QToolButton::InstantPopup);
    m_toolbar->addWidget(addButton);
    
    m_toolbar->addSeparator();
    
    QAction* deleteAction = m_toolbar->addAction("Delete");
    connect(deleteAction, &QAction::triggered, this, &NodeGraphPanel::onDeleteSelected);
    
    QAction* zoomInAction = m_toolbar->addAction("Zoom In");
    connect(zoomInAction, &QAction::triggered, this, &NodeGraphPanel::onZoomIn);
    
    QAction* zoomOutAction = m_toolbar->addAction("Zoom Out");
    connect(zoomOutAction, &QAction::triggered, this, &NodeGraphPanel::onZoomOut);
    
    QAction* fitAction = m_toolbar->addAction("Fit");
    connect(fitAction, &QAction::triggered, this, &NodeGraphPanel::onFitToView);
}

void NodeGraphPanel::setupScene()
{
    m_scene = new QGraphicsScene(this);
    m_scene->setSceneRect(-2000, -2000, 4000, 4000);
    
    m_view = new QGraphicsView(m_scene, this);
    m_view->setRenderHint(QPainter::Antialiasing);
    m_view->setDragMode(QGraphicsView::RubberBandDrag);
    m_view->setBackgroundBrush(QBrush(QColor("#1f1f1f")));
}

void NodeGraphPanel::updateFromGraph()
{
    if (!m_nodeGraph) return;
    
    m_scene->clear();
    
    for (NodeBase* node : m_nodeGraph->getNodes()) {
        QRectF rect = node->getRect();
        QGraphicsRectItem* item = new QGraphicsRectItem(rect);
        item->setFlag(QGraphicsItem::ItemIsSelectable);
        item->setFlag(QGraphicsItem::ItemIsMovable);
        item->setBrush(QBrush(QColor("#2d2d2d")));
        item->setPen(QPen(node->isSelected() ? QColor("#ff9d00") : QColor("#555555"), 2));
        item->setPos(node->getPosition());
        m_scene->addItem(item);
        
        QGraphicsTextItem* label = new QGraphicsTextItem(node->getName(), item);
        label->setDefaultTextColor(QColor("#e0e0e0"));
        label->setFont(QFont("Arial", 10));
        label->setPos(rect.width() / 2 - label->boundingRect().width() / 2, 5);
    }
}

void NodeGraphPanel::onAddNode(const QString& nodeType)
{
    qDebug() << "Adding node:" << nodeType;
}

void NodeGraphPanel::onDeleteSelected()
{
    qDebug() << "Deleting selected nodes";
}

void NodeGraphPanel::onZoomIn()
{
    m_view->scale(1.2, 1.2);
}

void NodeGraphPanel::onZoomOut()
{
    m_view->scale(0.8, 0.8);
}

void NodeGraphPanel::onFitToView()
{
    m_view->fitInView(m_scene->sceneRect(), Qt::KeepAspectRatio);
}