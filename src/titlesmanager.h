#ifndef TITLESMANAGER_H
#define TITLESMANAGER_H

#include <QObject>
#include <QString>
#include <QFont>
#include <QColor>
#include <QList>

class TitlesManager : public QObject
{
    Q_OBJECT

public:
    explicit TitlesManager(QObject *parent = nullptr);
    ~TitlesManager();

    struct TitleStyle {
        QString name;
        QFont font;
        QColor textColor;
        QColor backgroundColor;
        int animationDuration;
        QString animationType;
        bool hasOutline;
        QColor outlineColor;
        int outlineWidth;
        bool hasShadow;
        QColor shadowColor;
        int shadowOffsetX;
        int shadowOffsetY;
        int shadowBlur;
    };

    void createTitleStyle(const TitleStyle &style);
    QList<QString> getTitleStyleNames() const;
    TitleStyle getTitleStyle(const QString &name) const;
    void removeTitleStyle(const QString &name);

    // Tipos de animación
    enum AnimationType {
        FadeIn,
        FadeOut,
        SlideIn,
        SlideOut,
        PopIn,
        ZoomIn,
        Typewriter
    };

    QStringList getAnimationTypes() const;

signals:
    void titleStyleCreated(const QString &styleName);
    void titleStyleRemoved(const QString &styleName);

private:
    QList<TitleStyle> titleStyles;
    QStringList animationTypes;
};

#endif // TITLESMANAGER_H