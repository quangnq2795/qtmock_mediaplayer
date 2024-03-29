// player.cpp
#include "player.h"
#include "songlist.h"
#include <QDir>
#include <QDebug>
#include <QFileInfo>

Player::Player(): m_workingDir()
{
    m_mediaPlayer = new QMediaPlayer();
    m_mediaPlaylist = new QMediaPlaylist();
    m_mediaPlayer->setPlaylist(m_mediaPlaylist);
    m_mediaPlayer->setVolume(90);

    m_activeIndex = -1;
    m_playingState = false;
}

Player::~Player()
{
    delete m_mediaPlayer;
    delete m_mediaPlaylist;
}

Player& Player::getInstance()
{
    static Player m_player;

    return m_player;
}

void Player::setWorkingDir(const QString &workingDir)
{
    m_workingDir = workingDir;

    loadSongList();
}

void Player::loadSongList()
{
    QStringList filters;
    filters << "*.mp3";

    QDir musicFolder(m_workingDir);
    musicFolder.setNameFilters(filters);

    QFileInfoList fileInfoList = musicFolder.entryInfoList();
    for (const QFileInfo& fileInfo : fileInfoList) {
        if (fileInfo.isFile()) {
            QString filePath = fileInfo.absoluteFilePath();

            Song song(filePath);

            SongList::instance().addSong(song);
            m_mediaPlaylist->addMedia(QUrl::fromLocalFile(filePath));
        }
    }
}

void Player::play()
{
    // if(m_activeIndex >= 0 && m_playingState == false) {
    //     setPlayingState(true);
    // }

    if(m_playingState == false) {
        if(m_activeIndex < 0) {
            setPlayingSong(0);
        }
        setPlayingState(true); 
    }
}

void Player::play(int songIndex)
{
    if(songIndex < 0) {
        setPlayingState(false); 
        return;       
    }

    setPlayingSong(songIndex);
    setPlayingState(true); 
}

void Player::pause()
{
    if(m_activeIndex >= 0 && m_playingState == true) {
        setPlayingState(false);
    }
}

void Player::next()
{
    if(m_activeIndex < 0) {
        return;
    }

    if(m_activeIndex == m_mediaPlaylist->mediaCount() - 1) {
        setPlayingSong(0);
    } else {
        setPlayingSong(m_activeIndex + 1);
    }

    setPlayingState(true);
}

void Player::previous()
{
    if(m_activeIndex < 0) {
        return;
    }
    
    if(m_activeIndex == 0) {
        setPlayingSong(m_mediaPlaylist->mediaCount() - 1);
    } else {
        setPlayingSong(m_activeIndex -1 );
    }

    setPlayingState(true);
}


bool Player::isPlaying() {
    return m_playingState;
}

int  Player::currentSongIndex() {
    return m_activeIndex;
}


bool Player::getSongPlaying(int& id, QString& songName, QString& singer, QString& imagePath, int& totalTime)
{
    if(m_activeIndex < 0) {

    }

    Song* playingSong = SongList::instance().getSong(m_activeIndex);
    if(playingSong) {
        id = m_activeIndex;
        songName = playingSong->title();
        singer = playingSong->singer();
        imagePath = playingSong->path();
        totalTime = playingSong->duration();

        return true;
    }

    return false;
}

void Player::setPlayingSong(int songIndex)
{
    if(songIndex < 0) {
        return;
    }

    if(songIndex != m_activeIndex) {
        Song* playingSong = SongList::instance().getSong(songIndex);
        if(playingSong) {    
            m_activeIndex = songIndex;
            m_mediaPlaylist->setCurrentIndex(m_activeIndex);
            emit playerSongPlayingChanged(songIndex, playingSong->title(),playingSong->singer(),playingSong->path(), 100);
        }
    }
}

void Player::setPlayingState(bool playing)
{
    if(m_activeIndex < 0) {
        return;
    }

    if(playing) {
        m_mediaPlayer->play();
    } else {
        m_mediaPlayer->pause();
    }

    if(playing != m_playingState) {
        m_playingState = playing;
        emit playerStateChanged(m_playingState);
    }
}
