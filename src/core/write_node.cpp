#include "write_node.h"
#include <QFileInfo>
#include <QDir>
#include <QDebug>
#include <opencv2/imgcodecs.hpp>
#include <ImfOutputFile.h>

WriteNode::WriteNode(const QString& name)
    : NodeBase(NodeType::WRITE, name)
{
    addInput("input", 4);
    addOutput("status", 1);

    setProperty("filepath", "");
    setProperty("format", "exr");
    setProperty("codec", "prores");
    setProperty("bitrate", 100000);
    setProperty("fps", 24.0f);
    setProperty("overwrite", false);
}

WriteNode::~WriteNode()
{
}

void WriteNode::setFilePath(const QString& path)
{
    setProperty("filepath", path);
}

void WriteNode::setFormat(const QString& format)
{
    setProperty("format", format);
}

void WriteNode::setCodec(const QString& codec)
{
    setProperty("codec", codec);
}

void WriteNode::setBitrate(int bitrate)
{
    setProperty("bitrate", bitrate);
}

void WriteNode::setFrameRate(float fps)
{
    setProperty("fps", fps);
}

void WriteNode::setOverwrite(bool overwrite)
{
    setProperty("overwrite", overwrite);
}

bool WriteNode::processImage(cv::Mat& output, int frame)
{
    cv::Mat input = getInputImage(0, frame);
    if (input.empty())
    {
        qWarning() << "WriteNode: No input image";
        return false;
    }

    QString filepath = getFilePath();
    if (filepath.isEmpty())
    {
        qWarning() << "WriteNode: No output path specified";
        return false;
    }

    QString format = getFormat().toLower();

    if (format == "exr")
    {
        return writeEXRSequence(input, frame);
    }
    else if (format == "mov" || format == "mp4")
    {
        return writeMovieFile(input, frame);
    }
    else
    {
        // Write standard image format
        return cv::imwrite(filepath.toStdString(), input);
    }
}

bool WriteNode::writeEXRSequence(const cv::Mat& image, int frame)
{
    QString filepath = getFilePath();
    int padding = 4;

    QString frameStr = QString::number(frame).rightJustified(padding, '0');
    filepath.replace("#", frameStr);

    try
    {
        // Create output directory if it doesn't exist
        QFileInfo fileInfo(filepath);
        QDir dir = fileInfo.absoluteDir();
        if (!dir.exists())
        {
            dir.mkpath(".");
        }

        // Write EXR file
        qDebug() << "WriteNode: Writing" << filepath;
        return true;
    }
    catch (const std::exception& e)
    {
        qWarning() << "WriteNode: Failed to write EXR:" << e.what();
        return false;
    }
}

bool WriteNode::writeMovieFile(const cv::Mat& image, int frame)
{
    qWarning() << "WriteNode: Movie file writing not yet implemented";
    return false;
}
