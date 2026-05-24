#include "colorgradingmanager.h"
#include <QPainter>

ColorGradingManager::ColorGradingManager(QObject *parent)
    : QObject(parent)
{
    // Presets predeterminados
    ColorPreset cinematic;
    cinematic.name = "Cinematic";
    cinematic.brightness = 0.05f;
    cinematic.contrast = 1.2f;
    cinematic.saturation = 0.9f;
    cinematic.temperature = -10.0f;
    presets.append(cinematic);

    ColorPreset vintage;
    vintage.name = "Vintage";
    vintage.brightness = 0.1f;
    vintage.contrast = 0.8f;
    vintage.saturation = 0.7f;
    vintage.sepia = 0.3f;
    presets.append(vintage);

    ColorPreset vivid;
    vivid.name = "Vivid";
    vivid.brightness = 0.0f;
    vivid.contrast = 1.4f;
    vivid.saturation = 1.5f;
    presets.append(vivid);
}

ColorGradingManager::~ColorGradingManager()
{
}

void ColorGradingManager::addPreset(const ColorPreset &preset)
{
    presets.append(preset);
}

QImage ColorGradingManager::applyPreset(const QImage &image, const QString &presetName)
{
    for (const auto &preset : presets) {
        if (preset.name == presetName) {
            QImage result = image;
            result = adjustBrightness(result, preset.brightness);
            result = adjustContrast(result, preset.contrast);
            result = adjustSaturation(result, preset.saturation);
            result = adjustTemperature(result, preset.temperature);
            result = adjustExposure(result, preset.exposure);
            emit presetApplied(presetName);
            return result;
        }
    }
    return image;
}

QList<QString> ColorGradingManager::getPresetNames() const
{
    QList<QString> names;
    for (const auto &preset : presets) {
        names.append(preset.name);
    }
    return names;
}

void ColorGradingManager::removePreset(const QString &name)
{
    for (int i = 0; i < presets.size(); ++i) {
        if (presets[i].name == name) {
            presets.removeAt(i);
            break;
        }
    }
}

QImage ColorGradingManager::adjustBrightness(const QImage &image, float value)
{
    QImage result = image;
    for (int y = 0; y < result.height(); ++y) {
        for (int x = 0; x < result.width(); ++x) {
            QColor color(result.pixel(x, y));
            color.setRedF(qMin(1.0, qMax(0.0, color.redF() + value)));
            color.setGreenF(qMin(1.0, qMax(0.0, color.greenF() + value)));
            color.setBlueF(qMin(1.0, qMax(0.0, color.blueF() + value)));
            result.setPixel(x, y, color.rgba());
        }
    }
    return result;
}

QImage ColorGradingManager::adjustContrast(const QImage &image, float value)
{
    QImage result = image;
    float factor = (259.0f * (value + 255.0f)) / (255.0f * (259.0f - value));
    
    for (int y = 0; y < result.height(); ++y) {
        for (int x = 0; x < result.width(); ++x) {
            QColor color(result.pixel(x, y));
            color.setRed(qBound(0, int(factor * (color.red() - 128) + 128), 255));
            color.setGreen(qBound(0, int(factor * (color.green() - 128) + 128), 255));
            color.setBlue(qBound(0, int(factor * (color.blue() - 128) + 128), 255));
            result.setPixel(x, y, color.rgba());
        }
    }
    return result;
}

QImage ColorGradingManager::adjustSaturation(const QImage &image, float value)
{
    QImage result = image;
    for (int y = 0; y < result.height(); ++y) {
        for (int x = 0; x < result.width(); ++x) {
            QColor color(result.pixel(x, y));
            int gray = qGray(color.red(), color.green(), color.blue());
            color.setRed(qBound(0, int(gray + value * (color.red() - gray)), 255));
            color.setGreen(qBound(0, int(gray + value * (color.green() - gray)), 255));
            color.setBlue(qBound(0, int(gray + value * (color.blue() - gray)), 255));
            result.setPixel(x, y, color.rgba());
        }
    }
    return result;
}

QImage ColorGradingManager::adjustTemperature(const QImage &image, float value)
{
    QImage result = image;
    float warmFactor = value / 100.0f;
    
    for (int y = 0; y < result.height(); ++y) {
        for (int x = 0; x < result.width(); ++x) {
            QColor color(result.pixel(x, y));
            color.setRed(qBound(0, int(color.red() * (1 + warmFactor * 0.2)), 255));
            color.setBlue(qBound(0, int(color.blue() * (1 - warmFactor * 0.2)), 255));
            result.setPixel(x, y, color.rgba());
        }
    }
    return result;
}

QImage ColorGradingManager::adjustExposure(const QImage &image, float value)
{
    float factor = qPow(2.0f, value);
    QImage result = image;
    
    for (int y = 0; y < result.height(); ++y) {
        for (int x = 0; x < result.width(); ++x) {
            QColor color(result.pixel(x, y));
            color.setRed(qBound(0, int(color.red() * factor), 255));
            color.setGreen(qBound(0, int(color.green() * factor), 255));
            color.setBlue(qBound(0, int(color.blue() * factor), 255));
            result.setPixel(x, y, color.rgba());
        }
    }
    return result;
}

QColor ColorGradingManager::applyColorTransform(const QColor &color, float brightness, float contrast, float saturation)
{
    Q_UNUSED(color);
    Q_UNUSED(brightness);
    Q_UNUSED(contrast);
    Q_UNUSED(saturation);
    return color;
}