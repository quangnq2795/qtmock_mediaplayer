#include "imediaplayercontrolreceiver.h"
#include "player.h"

IMediaPlayerControlReceiver::IMediaPlayerControlReceiver()
{
    m_mediaAdapter = new IMediaPlayerControlAdaptor(this);

    auto connection =  new QDBusConnection(QDBusConnection::sessionBus());
    if (!connection->registerService("com.services.mediaplayer")) {
        qFatal("Could not register service!");
    }

    if (!connection->registerObject("/com/services/mediaplayer/mediacontrol", this)) {
        qFatal("Could not register object!");
    }

    qDebug()<<__FILE__<<__FUNCTION__<<__LINE__<<"Register Done";
}

bool IMediaPlayerControlReceiver::play()
{
    Player::getInstance().play();
    return true;
}

bool IMediaPlayerControlReceiver::pause()
{
    Player::getInstance().pause();
    return true;
}

bool IMediaPlayerControlReceiver::next()
{
    Player::getInstance().next();
    return true;
}

bool IMediaPlayerControlReceiver::previous()
{
    Player::getInstance().previous();
    return true;
}

bool IMediaPlayerControlReceiver::isPlaying()
{
    return Player::getInstance().isPlaying();
}

bool IMediaPlayerControlReceiver::getTimePlaying(int& currentTime)
{
    currentTime = 0;
    return true;
}

bool IMediaPlayerControlReceiver::getSongPlaying(int& SongId, QString& songName, QString& singer, QString& imagePath,int& totalTime)
{
    return Player::getInstance().getSongPlaying(SongId, songName, singer, imagePath, totalTime);
}
