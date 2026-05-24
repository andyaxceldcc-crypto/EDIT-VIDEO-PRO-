#include "imagemanager.h"
#include <QFile>
#include <QImageReader>
#include <QImageWriter>
#include <QDebug>

ImageManager::ImageManager(QObject *parent)
    : QObject(parent)
{
}

ImageManager::~ImageManager()
{
}

bool ImageManager::loadImage(const QString &path)
{
    QFile file(path);
    if (!file.exists()) {
        emit errorOccurred("Archivo no encontrado: " + path);
        return false;
    }

    QImageReader reader(path);
    if (!reader.read(&currentImage)) {
        emit errorOccurred("No se pudo cargar la imagen: " + reader.errorString());
        return false;
    }

    currentPath = path;
    emit imageLoaded(currentImage);
    return true;
}

bool ImageManager::saveImage(const QString &path, const QImage &image)
{
    QImageWriter writer(path);
    if (!writer.write(image)) {
        emit errorOccurred("No se pudo guardar la imagen: " + writer.errorString());
        return false;
    }
    return true;
}

QImage ImageManager::resizeImage(const QImage &image, int width, int height)
{
    return image.scaled(width, height, Qt::KeepAspectRatio, Qt::SmoothTransformation);
}

QImage ImageManager::applyFilter(const QImage &image, const QString &filterName)
{
    QImage result = image;
    
    if (filterName == "grayscale") {
        result = image.convertToFormat(QImage::Format_Grayscale8);
    } else if (filterName == "sepia") {
        // Implementar filtro sepia
        result = image;
    }
    
    return result;
}

QList<QString> ImageManager::getSupportedFormats() const
{
    return QList<QString>() << "png" << "jpg" << "jpeg" << "bmp" << "gif" << "tiff";
}

bool ImageManager::isFormatSupported(const QString &format) const
{
    return getSupportedFormats().contains(format.toLower());
}