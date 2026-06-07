#ifndef PROPERTIES_PANEL_H
#define PROPERTIES_PANEL_H

#include <QDockWidget>
#include <QWidget>
#include <QVBoxLayout>

class NodeBase;

/**
 * @class PropertiesPanel
 * @brief Panel for editing node properties
 */
class PropertiesPanel : public QDockWidget
{
    Q_OBJECT

public:
    explicit PropertiesPanel(QWidget* parent = nullptr);
    ~PropertiesPanel();

    void setNode(NodeBase* node);
    void clearProperties();

public slots:
    void onNodeUpdated(NodeBase* node);

private:
    void createPropertyWidgets();
    void updatePropertyValues();

private:
    QWidget* m_contentWidget;
    QVBoxLayout* m_layout;
    NodeBase* m_currentNode;
};

#endif // PROPERTIES_PANEL_H