#include "properties_panel.h"
#include "../../core/nodes/node_base.h"
#include <QVBoxLayout>
#include <QGroupBox>
#include <QLabel>
#include <QFormLayout>
#include <QDebug>

PropertiesPanel::PropertiesPanel(QWidget* parent)
    : QDockWidget(tr("Properties"), parent)
    , m_contentWidget(nullptr)
    , m_layout(nullptr)
    , m_currentNode(nullptr)
{
    setObjectName("PropertiesPanel");
    
    m_contentWidget = new QWidget(this);
    m_layout = new QVBoxLayout(m_contentWidget);
    m_layout->setAlignment(Qt::AlignTop);
    
    QLabel* placeholder = new QLabel("Select a node to view properties", m_contentWidget);
    placeholder->setAlignment(Qt::AlignCenter);
    placeholder->setStyleSheet("color: #666666; padding: 50px;");
    m_layout->addWidget(placeholder);
    
    setWidget(m_contentWidget);
}

PropertiesPanel::~PropertiesPanel()
{
}

void PropertiesPanel::setNode(NodeBase* node)
{
    if (m_currentNode == node) return;
    
    m_currentNode = node;
    clearProperties();
    
    if (!node) {
        QLabel* placeholder = new QLabel("Select a node to view properties", m_contentWidget);
        placeholder->setAlignment(Qt::AlignCenter);
        placeholder->setStyleSheet("color: #666666; padding: 50px;");
        m_layout->addWidget(placeholder);
        return;
    }
    
    QGroupBox* infoGroup = new QGroupBox("Node Information", m_contentWidget);
    QFormLayout* infoLayout = new QFormLayout(infoGroup);
    
    infoLayout->addRow("Name:", new QLabel(node->getName(), this));
    infoLayout->addRow("Type:", new QLabel(node->getTypeName(), this));
    
    m_layout->addWidget(infoGroup);
    createPropertyWidgets();
    m_layout->addStretch();
}

void PropertiesPanel::clearProperties()
{
    QLayoutItem* item;
    while ((item = m_layout->takeAt(0)) != nullptr) {
        if (item->widget()) {
            delete item->widget();
        }
        delete item;
    }
}

void PropertiesPanel::onNodeUpdated(NodeBase* node)
{
    if (node == m_currentNode) {
        updatePropertyValues();
    }
}

void PropertiesPanel::createPropertyWidgets()
{
    if (!m_currentNode) return;
    
    QGroupBox* transformGroup = new QGroupBox("Transform", m_contentWidget);
    QFormLayout* transformLayout = new QFormLayout(transformGroup);
    
    QLabel* posLabel = new QLabel(
        QString("X: %1, Y: %2").arg(m_currentNode->getPosition().x()).arg(m_currentNode->getPosition().y()),
        this);
    transformLayout->addRow("Position:", posLabel);
    
    m_layout->addWidget(transformGroup);
}

void PropertiesPanel::updatePropertyValues()
{
    // Update property values when node changes
}