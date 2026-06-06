#ifndef WRITE_NODE_H
#define WRITE_NODE_H

#include "nodes/node_base.h"
#include <QString>

/**
 * @class WriteNode
 * @brief Output rendering node - saves image sequences and video files
 */
class WriteNode : public NodeBase
{
public:
    WriteNode(const QString& name = "Write");
    virtual ~WriteNode();

    // Output configuration
    void setFilePath(const QString& path);
    QString getFilePath() const { return getProperty("filepath").toString(); }

    void setFormat(const QString& format);
    QString getFormat() const { return getProperty("format").toString(); }

    // Encoding settings
    void setCodec(const QString& codec);
    void setBitrate(int bitrate);
    void setFrameRate(float fps);

    // Frame range
    void setFrameRange(int first, int last);

    // Options
    void setOverwrite(bool overwrite);
    bool getOverwrite() const { return getProperty("overwrite").toBool(); }

protected:
    bool processImage(cv::Mat& output, int frame) override;

private:
    bool writeEXRSequence(const cv::Mat& image, int frame);
    bool writeMovieFile(const cv::Mat& image, int frame);
};

#endif // WRITE_NODE_H
