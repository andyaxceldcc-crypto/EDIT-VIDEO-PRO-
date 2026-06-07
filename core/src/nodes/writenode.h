#ifndef WRITENODE_H
#define WRITENODE_H

#include "../node.h"

class WriteNode : public Node {
public:
    WriteNode(const QString& name = "Write") : Node(name, Node::OUTPUT) {}
    ~WriteNode() override = default;

    void process() override;
    QVariant getOutput() override;

private:
    QVariant m_lastWritten;
};

#endif // WRITENODE_H
