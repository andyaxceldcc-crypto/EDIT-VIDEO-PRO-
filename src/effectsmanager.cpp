#include "effectsmanager.h"

EffectsManager::EffectsManager()
{
    initializeEffects();
}

void EffectsManager::initializeEffects()
{
    // Efectos de color
    EffectPreset brightness;
    brightness.name = "Brillo";
    brightness.category = "Color";
    brightness.description = "Ajusta el brillo del video";
    brightness.parameters["intensity"] = 1.0;
    effects.append(brightness);
    
    EffectPreset contrast;
    contrast.name = "Contraste";
    contrast.category = "Color";
    contrast.description = "Ajusta el contraste del video";
    contrast.parameters["intensity"] = 1.0;
    effects.append(contrast);
    
    EffectPreset saturation;
    saturation.name = "Saturación";
    saturation.category = "Color";
    saturation.description = "Ajusta la saturación de colores";
    saturation.parameters["intensity"] = 1.0;
    effects.append(saturation);
    
    // Efectos de desenfoque
    EffectPreset blur;
    blur.name = "Desenfoque";
    blur.category = "Blur";
    blur.description = "Aplica desenfoque gaussiano";
    blur.parameters["radius"] = 5;
    effects.append(blur);
    
    EffectPreset motionBlur;
    motionBlur.name = "Desenfoque de Movimiento";
    motionBlur.category = "Blur";
    motionBlur.description = "Aplica desenfoque de movimiento";
    motionBlur.parameters["amount"] = 1.0;
    effects.append(motionBlur);
    
    // Efectos de transición
    EffectPreset fade;
    fade.name = "Fade";
    fade.category = "Transiciones";
    fade.description = "Desvanecimiento suave";
    fade.parameters["duration"] = 0.5;
    effects.append(fade);
    
    // Efectos especiales
    EffectPreset sepia;
    sepia.name = "Sepia";
    sepia.category = "Artístico";
    sepia.description = "Efecto vintage sepia";
    sepia.parameters["intensity"] = 1.0;
    effects.append(sepia);
    
    EffectPreset grayscale;
    grayscale.name = "Escala de Grises";
    grayscale.category = "Artístico";
    grayscale.description = "Convierte a blanco y negro";
    grayscale.parameters["intensity"] = 1.0;
    effects.append(grayscale);
}

QList<EffectPreset> EffectsManager::getEffects() const
{
    return effects;
}

QList<QString> EffectsManager::getEffectCategories() const
{
    QList<QString> categories;
    for (const auto &effect : effects) {
        if (!categories.contains(effect.category)) {
            categories.append(effect.category);
        }
    }
    return categories;
}

QList<EffectPreset> EffectsManager::getEffectsByCategory(const QString &category) const
{
    QList<EffectPreset> result;
    for (const auto &effect : effects) {
        if (effect.category == category) {
            result.append(effect);
        }
    }
    return result;
}

EffectPreset EffectsManager::getEffectByName(const QString &name) const
{
    for (const auto &effect : effects) {
        if (effect.name == name) {
            return effect;
        }
    }
    return EffectPreset();
}
