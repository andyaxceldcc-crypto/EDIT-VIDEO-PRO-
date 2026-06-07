#include "writenode.h"
#include <QDebug>

void WriteNode::process() {
    // Tomar la primera entrada y simular escritura
    if (m_inputConnections.isEmpty()) {
        m_lastWritten = QVariant("<no-input>");
        return;
    }
    auto conn = m_inputConnections.first();
    if (!conn) { m_lastWritten = QVariant("<invalid-conn>"); return; }
    auto src = conn->srcNode();
    if (!src) { m_lastWritten = QVariant("<invalid-src>"); return; }
    QVariant data = src->getOutput();
    QString outPath = getParameter("outpath").toString();
    // Simular escritura
    qDebug() << "[WriteNode] Escribiendo" << data.toString() << "a" << outPath;
    m_lastWritten = data;
}

QVariant WriteNode::getOutput() {
    return m_lastWritten;
}
