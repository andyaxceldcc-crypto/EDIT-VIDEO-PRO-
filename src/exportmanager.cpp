#include "exportmanager.h"
#include <QProcess>
#include <QDebug>

ExportManager::ExportManager()
{
    initializePresets();
}

void ExportManager::initializePresets()
{
    ExportPreset hd;
    hd.name = "HD (720p)";
    hd.format = "mp4";
    hd.bitrate = 5000;
    hd.resolution = 720;
    hd.fps = 30;
    presets.append(hd);
    
    ExportPreset fullhd;
    fullhd.name = "Full HD (1080p)";
    fullhd.format = "mp4";
    fullhd.bitrate = 8000;
    fullhd.resolution = 1080;
    fullhd.fps = 30;
    presets.append(fullhd);
    
    ExportPreset ultra4k;
    ultra4k.name = "4K (2160p)";
    ultra4k.format = "mp4";
    ultra4k.bitrate = 15000;
    ultra4k.resolution = 2160;
    ultra4k.fps = 60;
    presets.append(ultra4k);
    
    ExportPreset web;
    web.name = "Web (optimizado)";
    web.format = "mp4";
    web.bitrate = 2000;
    web.resolution = 480;
    web.fps = 24;
    presets.append(web);
}

QList<ExportPreset> ExportManager::getPresets() const
{
    return presets;
}

bool ExportManager::exportVideo(const QString &inputPath, const QString &outputPath, 
                               const ExportPreset &preset)
{
    // Comando FFmpeg para exportar
    QString command = QString(
        "ffmpeg -i \"%1\" -vf scale=%2:-1 -r %3 -b:v %4k -c:a aac \"%5\""
    ).arg(inputPath)
     .arg(preset.resolution)
     .arg(preset.fps)
     .arg(preset.bitrate)
     .arg(outputPath);
    
    qDebug() << "Ejecutando comando:" << command;
    
    QProcess process;
    process.start(command);
    
    if (!process.waitForFinished(-1)) {
        qDebug() << "Error en la exportación:" << process.errorString();
        return false;
    }
    
    qDebug() << "Exportación completada";
    return true;
}
