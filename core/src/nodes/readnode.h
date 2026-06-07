#ifndef READNODE_H
#define READNODE_H

#include "../node.h"

class ReadNode : public Node {
public:
    ReadNode(const QString& name = "Read") : Node(name, Node::INPUT) {}
    ~ReadNode() override = default;

    void process() override;
    QVariant getOutput() override;

private:
    QVariant m_output;
};

#endif // READNODE_H
