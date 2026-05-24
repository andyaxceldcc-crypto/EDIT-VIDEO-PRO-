#ifndef AUDIOMANAGER_H
#define AUDIOMANAGER_H

#include <QObject>
#include <QString>
#include <QAudioFormat>
#include <QList>

class AudioManager : public QObject
{
    Q_OBJECT

public:
    explicit AudioManager(QObject *parent = nullptr);
    ~AudioManager();

    enum AudioEffect {
        Reverb,
        Echo,
        FadeIn,
        FadeOut,
        Normalize,
        Equalizer,
        Compressor,
        NoiseReduction
    };

    struct AudioTrack {
        QString filePath;
        float volume;
        float pan;
        bool muted;
        bool solo;
        QList<AudioEffect> effects;
    };

    bool loadAudioFile(const QString &path);
    bool saveAudioFile(const QString &path, const QByteArray &data);
    QByteArray applyEffect(const QByteArray &audioData, AudioEffect effect);

    void addTrack(const AudioTrack &track);
    QList<AudioTrack> getTracks() const;
    void removeTrack(int index);
    void setTrackVolume(int index, float volume);
    void setTrackPan(int index, float pan);
    void muteTrack(int index, bool muted);
    void soloTrack(int index, bool solo);

    float getDuration() const;
    int getSampleRate() const;
    int getChannelCount() const;

signals:
    void audioLoaded();
    void trackAdded(int index);
    void trackRemoved(int index);
    void errorOccurred(const QString &errorMessage);

private:
    QList<AudioTrack> audioTracks;
    int sampleRate;
    int channels;
    float duration;
};

#endif // AUDIOMANAGER_H