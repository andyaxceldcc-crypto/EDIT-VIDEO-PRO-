#ifndef TRANSFORM_NODE_H
#define TRANSFORM_NODE_H

#include "node_base.h"
#include <QString>

/**
 * @class TransformNode
 * @brief 2D transformation node for scale, rotate, translate
 */
class TransformNode : public NodeBase
{
public:
    TransformNode(const QString& name = "Transform");
    virtual ~TransformNode();

    // Translation
    void setTranslate(float tx, float ty);
    float getTranslateX() const { return getProperty("translate_x").toFloat(); }
    float getTranslateY() const { return getProperty("translate_y").toFloat(); }

    // Rotation
    void setRotate(float degrees);
    float getRotate() const { return getProperty("rotate").toFloat(); }

    // Scale
    void setScale(float scaleX, float scaleY);
    float getScaleX() const { return getProperty("scale_x").toFloat(); }
    float getScaleY() const { return getProperty("scale_y").toFloat(); }

    // Pivot point
    void setPivot(float x, float y);

protected:
    bool processImage(cv::Mat& output, int frame) override;

private:
    cv::Mat2f getTransformMatrix();
};

#endif // TRANSFORM_NODE_H
