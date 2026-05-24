#ifndef COLORGRADINGMANAGER_H
#define COLORGRADINGMANAGER_H

#include <QObject>
#include <QImage>
#include <QColor>

class ColorGradingManager : public QObject
{
    Q_OBJECT

public:
    explicit ColorGradingManager(QObject *parent = nullptr);
    ~ColorGradingManager();

    struct ColorPreset {
        QString name;
        float brightness;
        float contrast;
        float saturation;
        float temperature;
        float tint;
        float exposure;
        float highlights;
        float shadows;
        float gamma;
    };

    void addPreset(const ColorPreset &preset);
    QImage applyPreset(const QImage &image, const QString &presetName);
    QList<QString> getPresetNames() const;
    void removePreset(const QString &name);

    // Ajustes individuales
    QImage adjustBrightness(const QImage &image, float value);
    QImage adjustContrast(const QImage &image, float value);
    QImage adjustSaturation(const QImage &image, float value);
    QImage adjustTemperature(const QImage &image, float value);
    QImage adjustExposure(const QImage &image, float value);

signals:
    void presetApplied(const QString &presetName);
    void adjustmentApplied();

private:
    QList<ColorPreset> presets;
    QColor applyColorTransform(const QColor &color, float brightness, float contrast, float saturation);
};

#endif // COLORGRADINGMANAGER_H