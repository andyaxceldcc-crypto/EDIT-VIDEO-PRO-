#include "audiomanager.h"

AudioManager::AudioManager(QObject *parent)
    : QObject(parent)
    , sampleRate(44100)
    , channels(2)
    , duration(0.0f)
{
}

AudioManager::~AudioManager()
{
}

bool AudioManager::loadAudioFile(const QString &path)
{
    QFile file(path);
    if (!file.exists()) {
        emit errorOccurred("Archivo de audio no encontrado: " + path);
        return false;
    }
    
    emit audioLoaded();
    return true;
}

bool AudioManager::saveAudioFile(const QString &path, const QByteArray &data)
{
    QFile file(path);
    if (!file.open(QIODevice::WriteOnly)) {
        emit errorOccurred("No se pudo abrir el archivo para escribir: " + path);
        return false;
    }
    
    qint64 written = file.write(data);
    file.close();
    
    return written == data.size();
}

QByteArray AudioManager::applyEffect(const QByteArray &audioData, AudioEffect effect)
{
    QByteArray result = audioData;
    
    // Implementar efectos de audio
    switch (effect) {
        case FadeIn:
            // Implementar fade in
            break;
        case FadeOut:
            // Implementar fade out
            break;
        case Normalize:
            // Implementar normalización
            break;
        case Reverb:
            // Implementar reverb
            break;
        case Echo:
            // Implementar eco
            break;
        case Equalizer:
            // Implementar ecualizador
            break;
        case Compressor:
            // Implementar compresor
            break;
        case NoiseReduction:
            // Implementar reducción de ruido
            break;
    }
    
    return result;
}

void AudioManager::addTrack(const AudioTrack &track)
{
    audioTracks.append(track);
    emit trackAdded(audioTracks.size() - 1);
}

QList<AudioManager::AudioTrack> AudioManager::getTracks() const
{
    return audioTracks;
}

void AudioManager::removeTrack(int index)
{
    if (index >= 0 && index < audioTracks.size()) {
        audioTracks.removeAt(index);
        emit trackRemoved(index);
    }
}

void AudioManager::setTrackVolume(int index, float volume)
{
    if (index >= 0 && index < audioTracks.size()) {
        audioTracks[index].volume = qBound(0.0f, volume, 1.0f);
    }
}

void AudioManager::setTrackPan(int index, float pan)
{
    if (index >= 0 && index < audioTracks.size()) {
        audioTracks[index].pan = qBound(-1.0f, pan, 1.0f);
    }
}

void AudioManager::muteTrack(int index, bool muted)
{
    if (index >= 0 && index < audioTracks.size()) {
        audioTracks[index].muted = muted;
    }
}

void AudioManager::soloTrack(int index, bool solo)
{
    if (index >= 0 && index < audioTracks.size()) {
        audioTracks[index].solo = solo;
    }
}

float AudioManager::getDuration() const
{
    return duration;
}

int AudioManager::getSampleRate() const
{
    return sampleRate;
}

int AudioManager::getChannelCount() const
{
    return channels;
}