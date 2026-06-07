#ifndef NODE_H
#define NODE_H

#include <QString>
#include <QVector>
#include <QMap>
#include <QVariant>
#include <memory>

class Connection;

/**
 * @class Node
 * @brief Clase base para todos los nodos del sistema node-based
 * Similar a Foundry Nuke y Mari
 */
class Node {
public:
    enum NodeType {
        INPUT,      // Nodo de entrada (Read, Camera)
        OUTPUT,     // Nodo de salida (Write, Viewer)
        EFFECT,     // Nodos de efectos
        TRANSFORM,  // Transformaciones
        COLOR,      // Corrección de color
        KEYING,     // Keying
        MERGE,      // Fusión de capas
        CUSTOM      // Nodos personalizados
    };

    Node(const QString& name, NodeType type);
    virtual ~Node() = default;

    // Información del nodo
    QString getName() const { return m_name; }
    void setName(const QString& name) { m_name = name; }
    NodeType getType() const { return m_type; }
    QString getTypeString() const;

    // Conexiones
    void addInputConnection(std::shared_ptr<Connection> connection);
    void addOutputConnection(std::shared_ptr<Connection> connection);
    QVector<std::shared_ptr<Connection>> getInputConnections() const;
    QVector<std::shared_ptr<Connection>> getOutputConnections() const;

    // Propiedades/Parámetros
    void setParameter(const QString& name, const QVariant& value);
    QVariant getParameter(const QString& name) const;
    QMap<QString, QVariant> getAllParameters() const { return m_parameters; }

    // Procesamiento
    virtual void process() = 0;
    virtual QVariant getOutput() = 0;

    // Posición en el gráfico
    void setPosition(double x, double y) { m_posX = x; m_posY = y; }
    double getX() const { return m_posX; }
    double getY() const { return m_posY; }

protected:
    QString m_name;
    NodeType m_type;
    QVector<std::shared_ptr<Connection>> m_inputConnections;
    QVector<std::shared_ptr<Connection>> m_outputConnections;
    QMap<QString, QVariant> m_parameters;
    double m_posX = 0.0;
    double m_posY = 0.0;
};

#endif // NODE_H
