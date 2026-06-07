#ifndef NODE_CONNECTION_H
#define NODE_CONNECTION_H

#include <QObject>
#include <QPointF>

class NodeBase;

/**
 * @class NodeConnection
 * @brief Represents a connection between two nodes
 */
class NodeConnection : public QObject
{
    Q_OBJECT

public:
    NodeConnection(NodeBase* sourceNode, int sourcePort,
                   NodeBase* destNode, int destPort,
                   QObject* parent = nullptr);
    ~NodeConnection();

    NodeBase* getSourceNode() const { return m_sourceNode; }
    NodeBase* getDestNode() const { return m_destNode; }
    int getSourcePort() const { return m_sourcePort; }
    int getDestPort() const { return m_destPort; }

    QPointF getSourcePoint() const;
    QPointF getDestPoint() const;

    bool isValid() const;
    void setSelected(bool selected);
    bool isSelected() const { return m_selected; }

signals:
    void connectionChanged();

private:
    NodeBase* m_sourceNode;
    NodeBase* m_destNode;
    int m_sourcePort;
    int m_destPort;
    bool m_selected;
};

#endif // NODE_CONNECTION_H