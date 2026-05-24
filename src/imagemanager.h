#ifndef IMAGEMANAGER_H
#define IMAGEMANAGER_H

#include <QObject>
#include <QImage>
#include <QString>
#include <QList>

class ImageManager : public QObject
{
    Q_OBJECT

public:
    explicit ImageManager(QObject *parent = nullptr);
    ~ImageManager();

    bool loadImage(const QString &path);
    bool saveImage(const QString &path, const QImage &image);
    QImage resizeImage(const QImage &image, int width, int height);
    QImage applyFilter(const QImage &image, const QString &filterName);
    
    QList<QString> getSupportedFormats() const;
    bool isFormatSupported(const QString &format) const;

signals:
    void imageLoaded(const QImage &image);
    void loadingProgress(int percent);
    void errorOccurred(const QString &errorMessage);

private:
    QImage currentImage;
    QString currentPath;
};

#endif // IMAGEMANAGER_H