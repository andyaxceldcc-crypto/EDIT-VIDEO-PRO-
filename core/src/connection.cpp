#include "connection.h"
#include "node.h"
#include <QString>

Connection::Connection(std::shared_ptr<Node> src, int srcPort, std::shared_ptr<Node> dst, int dstPort)
    : m_src(src), m_dst(dst), m_srcPort(srcPort), m_dstPort(dstPort)
{
}

std::shared_ptr<Node> Connection::srcNode() const {
    return m_src.lock();
}

std::shared_ptr<Node> Connection::dstNode() const {
    return m_dst.lock();
}

int Connection::srcPort() const { return m_srcPort; }
int Connection::dstPort() const { return m_dstPort; }

QString Connection::debugString() const {
    auto s = srcNode();
    auto d = dstNode();
    QString srcName = s ? s->getName() : "<null>";
    QString dstName = d ? d->getName() : "<null>";
    return QString("%1:%2 -> %3:%4").arg(srcName).arg(m_srcPort).arg(dstName).arg(m_dstPort);
}
