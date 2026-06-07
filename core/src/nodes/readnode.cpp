#include "readnode.h"

void ReadNode::process() {
    // Placeholder: en un proyecto real aquí se leería con FFmpeg/avcodec
    QString path = getParameter("path").toString();
    if (path.isEmpty()) {
        m_output = QVariant("<no-file>");
    } else {
        m_output = QVariant(QString("frame_from:%1").arg(path));
    }
}

QVariant ReadNode::getOutput() {
    return m_output;
}
