// player.h
#ifndef PLAYER_H
#define PLAYER_H

#include <QObject>
#include <QMediaPlayer>
#include <QMediaPlaylist>

class Player: public QObject
{
    Q_OBJECT

public:
    static Player& getInstance();

    void setWorkingDir(const QString& workingDir);

    void play();
    void play(int songIndex);
    void pause();
    void next();
    void previous();
    bool isPlaying();
    int  currentSongIndex();

    bool getSongPlaying(int& songId,QString& songName, QString& singer, QString& imagePath, int& playingTime);
    bool getTimePlaying(int& playingTime);

signals:
    void playerStateChanged(bool playing);
    void playerTimePlayingChanged(int currentTime);
    void playerSongPlayingChanged(int SongId, QString songName, QString singer, QString imagePath,int totalTime);

private:
    Player(); // Private constructor to prevent instantiation
    ~Player();  // Private destructor to prevent deletion
    Player(const Player&) = delete; // Disable copy constructor
    Player& operator=(const Player&) = delete;

    void loadSongList();
    void setPlayingSong(int songIndex);
    void setPlayingState(bool playing);

private:
    QMediaPlayer* m_mediaPlayer;
    QMediaPlaylist* m_mediaPlaylist;

    QString m_workingDir;

    bool m_playingState;
    int m_activeIndex;
};

#endif // PLAYER_H
