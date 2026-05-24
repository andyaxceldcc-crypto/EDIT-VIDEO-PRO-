#include "titlesmanager.h"

TitlesManager::TitlesManager(QObject *parent)
    : QObject(parent)
{
    // Crear estilos predeterminados
    TitleStyle basic;
    basic.name = "Basic";
    basic.font = QFont("Arial", 24);
    basic.textColor = Qt::white;
    basic.backgroundColor = QColor(0, 0, 0, 150);
    basic.animationDuration = 1000;
    basic.animationType = "FadeIn";
    basic.hasOutline = false;
    basic.hasShadow = true;
    basic.shadowColor = QColor(0, 0, 0, 200);
    basic.shadowOffsetX = 2;
    basic.shadowOffsetY = 2;
    basic.shadowBlur = 4;
    titleStyles.append(basic);

    TitleStyle cinematic;
    cinematic.name = "Cinematic";
    cinematic.font = QFont("Impact", 36);
    cinematic.textColor = Qt::white;
    cinematic.backgroundColor = Qt::transparent;
    cinematic.animationDuration = 2000;
    cinematic.animationType = "SlideIn";
    cinematic.hasOutline = true;
    cinematic.outlineColor = Qt::black;
    cinematic.outlineWidth = 2;
    cinematic.hasShadow = true;
    cinematic.shadowColor = QColor(0, 0, 0, 180);
    cinematic.shadowOffsetX = 3;
    cinematic.shadowOffsetY = 3;
    cinematic.shadowBlur = 6;
    titleStyles.append(cinematic);

    TitleStyle subtitle;
    subtitle.name = "Subtitle";
    subtitle.font = QFont("Arial", 18);
    subtitle.textColor = Qt::white;
    subtitle.backgroundColor = QColor(0, 0, 0, 200);
    subtitle.animationDuration = 500;
    subtitle.animationType = "FadeIn";
    subtitle.hasOutline = false;
    subtitle.hasShadow = true;
    subtitle.shadowColor = QColor(0, 0, 0, 150);
    subtitle.shadowOffsetX = 1;
    subtitle.shadowOffsetY = 1;
    subtitle.shadowBlur = 3;
    titleStyles.append(subtitle);

    // Tipos de animación
    animationTypes << "FadeIn" << "FadeOut" << "SlideIn" << "SlideOut" << "PopIn" << "ZoomIn" << "Typewriter";
}

TitlesManager::~TitlesManager()
{
}

void TitlesManager::createTitleStyle(const TitleStyle &style)
{
    titleStyles.append(style);
    emit titleStyleCreated(style.name);
}

QList<QString> TitlesManager::getTitleStyleNames() const
{
    QList<QString> names;
    for (const auto &style : titleStyles) {
        names.append(style.name);
    }
    return names;
}

TitlesManager::TitleStyle TitlesManager::getTitleStyle(const QString &name) const
{
    for (const auto &style : titleStyles) {
        if (style.name == name) {
            return style;
        }
    }
    return TitleStyle();
}

void TitlesManager::removeTitleStyle(const QString &name)
{
    for (int i = 0; i < titleStyles.size(); ++i) {
        if (titleStyles[i].name == name) {
            titleStyles.removeAt(i);
            emit titleStyleRemoved(name);
            break;
        }
    }
}

QStringList TitlesManager::getAnimationTypes() const
{
    return animationTypes;
}