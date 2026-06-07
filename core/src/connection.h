#ifndef CONNECTION_H
#define CONNECTION_H

#include <memory>
#include <QString>

class Node;

class Connection {
public:
    Connection(std::shared_ptr<Node> src, int srcPort, std::shared_ptr<Node> dst, int dstPort);

    std::shared_ptr<Node> srcNode() const;
    std::shared_ptr<Node> dstNode() const;
    int srcPort() const;
    int dstPort() const;

    QString debugString() const;

private:
    std::weak_ptr<Node> m_src;
    std::weak_ptr<Node> m_dst;
    int m_srcPort;
    int m_dstPort;
};

#endif // CONNECTION_H
