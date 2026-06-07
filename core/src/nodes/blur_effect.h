#ifndef BLUR_EFFECT_H
#define BLUR_EFFECT_H

#include "../node.h"

class BlurEffect : public Node {
public:
    BlurEffect(const QString& name = "Blur") : Node(name, Node::EFFECT) {}
    ~BlurEffect() override = default;

    void process() override;
    QVariant getOutput() override;

private:
    QVariant m_output;
};

#endif // BLUR_EFFECT_H
