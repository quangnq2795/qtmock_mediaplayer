#ifndef IMEDIAPLAYERCONTROL_H
#define IMEDIAPLAYERCONTROL_H

#include <QObject>

class IMediaPlayerControl: public QObject
{
    Q_OBJECT

public:
    explicit IMediaPlayerControl(QObject *parent = nullptr) {};

public Q_SLOTS:
    virtual bool play() = 0;
    virtual bool pause() = 0;
    virtual bool next() = 0;
    virtual bool previous() = 0;
    virtual bool isPlaying() = 0;

    virtual bool getTimePlaying(int& playing)  = 0;
    virtual bool getSongPlaying(int& SongId, QString& songName, QString& singer, QString& imagePath,int& totalTime)  = 0;

signals:
    void playerStateChanged(bool playing);
    void playerTimePlayingChanged(int currentTime);
    void playerSongPlayingChanged(int SongId, QString songName, QString singer, QString imagePath,int totalTime);
};

#endif // IMEDIAPLAYERCONTROL_H
