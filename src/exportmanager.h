#ifndef EXPORTMANAGER_H
#define EXPORTMANAGER_H

#include <QString>
#include <QList>

struct ExportPreset
{
    QString name;
    QString format;
    int bitrate;
    int resolution;
    int fps;
};

class ExportManager
{
public:
    ExportManager();
    
    QList<ExportPreset> getPresets() const;
    bool exportVideo(const QString &inputPath, const QString &outputPath, 
                    const ExportPreset &preset);
    
private:
    QList<ExportPreset> presets;
    
    void initializePresets();
};

#endif // EXPORTMANAGER_H
