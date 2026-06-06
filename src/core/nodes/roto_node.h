#ifndef ROTO_NODE_H
#define ROTO_NODE_H

#include "node_base.h"
#include <QString>
#include <QVector>
#include <QPointF>

/**
 * @class RotoNode
 * @brief Rotoscoping node for creating animated masks
 */
class RotoNode : public NodeBase
{
public:
    struct RotoPoint
    {
        float x, y;
        float handleLeftX, handleLeftY;
        float handleRightX, handleRightY;
        bool isConnected;
    };

    RotoNode(const QString& name = "Roto");
    virtual ~RotoNode();

    // Shape management
    void addShape(const QString& name);
    void removeShape(const QString& name);

    // Point management
    void addPoint(const QString& shapeName, float x, float y);
    void removePoint(const QString& shapeName, int index);
    void updatePoint(const QString& shapeName, int index, float x, float y);

    // Animation
    void setKeyframe(const QString& shapeName, int frame);

protected:
    bool processImage(cv::Mat& output, int frame) override;

private:
    QMap<QString, QVector<RotoPoint>> m_shapes;
};

#endif // ROTO_NODE_H
