#ifndef NODE_BASE_H
#define NODE_BASE_H

#include <QString>
#include <QPointF>
#include <QRectF>
#include <QList>
#include <QMap>
#include <QVariant>
#include <opencv2/core.hpp>

class NodeConnection;

/**
 * @class NodeBase
 * @brief Base class for all nodes in the compositor graph
 */
class NodeBase
{
    Q_OBJECT
public:
    enum NodeType {
        Read,
        Write,
        Viewer,
        Grade,
        Merge,
        Transform,
        Blur,
        ColorCorrect,
        Keyer,
        Roto,
        Tracker,
        Other
    };

    NodeBase(NodeType type, const QString& name = "");
    virtual ~NodeBase();

    // Node identification
    QString getName() const { return m_name; }
    void setName(const QString& name) { m_name = name; }
    NodeType getType() const { return m_type; }
    QString getTypeName() const;

    // Position and geometry
    QPointF getPosition() const { return m_position; }
    void setPosition(const QPointF& pos) { m_position = pos; }
    QRectF getRect() const;
    QRectF getInputPortRect(int index) const;
    QRectF getOutputPortRect(int index) const;

    // Properties
    void setProperty(const QString& name, const QVariant& value);
    QVariant getProperty(const QString& name) const;
    
    // Ports
    void addInput(const QString& name, int channels = 4);
    void addOutput(const QString& name, int channels = 4);
    QList<QString> getInputs() const { return m_inputs; }
    QList<QString> getOutputs() const { return m_outputs; }

    // Processing
    virtual bool processImage(cv::Mat& output, int frame);
    cv::Mat getInputImage(int index, int frame);

    // Caching
    void clearCache();
    void enableCache(bool enable) { m_cacheEnabled = enable; }

    // State
    void setSelected(bool selected) { m_selected = selected; }
    bool isSelected() const { return m_selected; }
    void setBypassed(bool bypassed) { m_bypassed = bypassed; }
    bool isBypassed() const { return m_bypassed; }

signals:
    void nodeUpdated();

protected:
    QString m_name;
    NodeType m_type;
    QPointF m_position;
    QMap<QString, QVariant> m_properties;
    QList<QString> m_inputs;
    QList<QString> m_outputs;
    bool m_selected;
    bool m_bypassed;
    bool m_cacheEnabled;
    QMap<int, cv::Mat> m_frameCache;
};

#endif // NODE_BASE_H