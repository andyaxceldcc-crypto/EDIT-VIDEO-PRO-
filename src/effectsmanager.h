#ifndef EFFECTSMANAGER_H
#define EFFECTSMANAGER_H

#include <QString>
#include <QList>
#include <QMap>

struct EffectPreset
{
    QString name;
    QString category;
    QString description;
    QMap<QString, QVariant> parameters;
};

class EffectsManager
{
public:
    EffectsManager();
    
    QList<EffectPreset> getEffects() const;
    QList<QString> getEffectCategories() const;
    QList<EffectPreset> getEffectsByCategory(const QString &category) const;
    EffectPreset getEffectByName(const QString &name) const;
    
private:
    QList<EffectPreset> effects;
    
    void initializeEffects();
};

#endif // EFFECTSMANAGER_H
