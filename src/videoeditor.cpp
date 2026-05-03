#include "videoeditor.h"

VideoEditor::VideoEditor()
{
}

void VideoEditor::loadVideo(const QString &filePath)
{
    currentProject = filePath;
    
    VideoClip clip;
    clip.path = filePath;
    clip.duration = 0;
    clip.startFrame = 0;
    clip.endFrame = 0;
    
    clips.append(clip);
}

void VideoEditor::addClip(const QString &filePath, int startTime, int duration)
{
    VideoClip clip;
    clip.path = filePath;
    clip.duration = duration;
    clip.startFrame = startTime;
    clip.endFrame = startTime + duration;
    
    clips.append(clip);
}

void VideoEditor::removeClip(int index)
{
    if (index >= 0 && index < clips.size()) {
        clips.removeAt(index);
    }
}

void VideoEditor::addEffect(const QString &effectName, double intensity)
{
    Effect effect;
    effect.name = effectName;
    effect.type = "filter";
    effect.intensity = intensity;
    
    effects.append(effect);
}

void VideoEditor::addTransition(const QString &transitionType, int duration, int clipIndex)
{
    Transition transition;
    transition.type = transitionType;
    transition.duration = duration;
    transition.clipIndex = clipIndex;
    
    transitions.append(transition);
}

void VideoEditor::exportVideo(const QString &outputPath, const QString &format)
{
    // Aquí irían los comandos para FFmpeg
    // ffmpeg -i input.mp4 -vf "[efectos]" -t duration output.mp4
}

QList<VideoClip> VideoEditor::getClips() const
{
    return clips;
}

QList<Effect> VideoEditor::getEffects() const
{
    return effects;
}

QList<Transition> VideoEditor::getTransitions() const
{
    return transitions;
}
