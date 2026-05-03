#ifndef VIDEOEDITOR_H
#define VIDEOEDITOR_H

#include <QString>
#include <QList>
#include <QImage>

struct VideoClip
{
    QString path;
    int duration;
    int startFrame;
    int endFrame;
};

struct Effect
{
    QString name;
    QString type;
    double intensity;
};

struct Transition
{
    QString type;
    int duration;
    int clipIndex;
};

class VideoEditor
{
public:
    VideoEditor();
    
    void loadVideo(const QString &filePath);
    void addClip(const QString &filePath, int startTime, int duration);
    void removeClip(int index);
    void addEffect(const QString &effectName, double intensity = 1.0);
    void addTransition(const QString &transitionType, int duration = 500, int clipIndex = -1);
    void exportVideo(const QString &outputPath, const QString &format = "mp4");
    
    QList<VideoClip> getClips() const;
    QList<Effect> getEffects() const;
    QList<Transition> getTransitions() const;

private:
    QList<VideoClip> clips;
    QList<Effect> effects;
    QList<Transition> transitions;
    
    QString currentProject;
};

#endif // VIDEOEDITOR_H
