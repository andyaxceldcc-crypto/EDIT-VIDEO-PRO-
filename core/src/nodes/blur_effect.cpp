#include "blur_effect.h"

void BlurEffect::process() {
    // Leer primer input
    if (m_inputConnections.isEmpty()) {
        m_output = QVariant("<no-input>");
        return;
    }
    auto conn = m_inputConnections.first();
    if (!conn) { m_output = QVariant("<invalid-conn>"); return; }
    auto src = conn->srcNode();
    if (!src) { m_output = QVariant("<invalid-src>"); return; }
    QVariant in = src->getOutput();
    // Simular blur: envolver el contenido
    QString radius = getParameter("radius").toString();
    if (radius.isEmpty()) radius = "3";
    m_output = QVariant(QString("blur(r=%1):%2").arg(radius).arg(in.toString()));
}

QVariant BlurEffect::getOutput() {
    return m_output;
}
