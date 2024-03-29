#include "appuicontrol.h"
#include "appmanageruicontrol.h"
#include "player.h"

#include <QDebug>

AppUIControl::AppUIControl(QObject *parent)
{
    m_UIControlReceiver = new IAppUIControlReceiver(*this);
    m_playerReceiver = new IMediaPlayerControlReceiver();

    // ui control signal from appmanager
    connect(m_UIControlReceiver, &IAppUIControlReceiver::appVisibleChanged, this, &AppUIControl::handleMediaAppVisibleChanged);

    // internal signal for handler ui event
    connect(this, &AppUIControl::homeScreenAppVisibleChanged, this, &AppUIControl::handleHomeScreenAppVisibleChanged);

    // player signal to mediapp ui
    connect(&Player::getInstance(), &Player::playerStateChanged, this, &AppUIControl::playerStateChanged);
    connect(&Player::getInstance(), &Player::playerSongPlayingChanged, this, &AppUIControl::playerSongPlayingChanged);

    // player signal to dbus
    connect(&Player::getInstance(), &Player::playerStateChanged, m_playerReceiver, &IMediaPlayerControlReceiver::playerStateChanged);
    connect(&Player::getInstance(), &Player::playerSongPlayingChanged, m_playerReceiver, &IMediaPlayerControlReceiver::playerSongPlayingChanged);
    connect(&Player::getInstance(), &Player::playerTimePlayingChanged, m_playerReceiver, &IMediaPlayerControlReceiver::playerTimePlayingChanged);

    // init mediapp visible value
    m_appVisible = AppManagerUIControl::getInstance().getAppVisible("mediaplayer");
}

void AppUIControl::uiEventBackToHomeOnClicked() {
    emit homeScreenAppVisibleChanged();
}

void AppUIControl::uiEventMediaPlayStateChanged() {

    bool isPlaying = Player::getInstance().isPlaying();

    if(isPlaying) {
        Player::getInstance().pause();
    } else {
        Player::getInstance().play();
    }
}

void AppUIControl::uiMusicSelectedChanged(int clickedIndex) { 
    Player::getInstance().play(clickedIndex);
}

bool AppUIControl::getMediaPlayerState() const
{
    return Player::getInstance().isPlaying();
}

bool AppUIControl::getMediaAppVisibleProperty() const
{
    return m_appVisible;
}

void AppUIControl::handleMediaAppVisibleChanged(bool val)
{
    if(m_appVisible != val) {
        m_appVisible = val;
        emit mediaAppVisiblePropertyChanged();
    }
}

void AppUIControl::handleHomeScreenAppVisibleChanged()
{
    AppManagerUIControl::getInstance().requestShow("homescreen");
}

int AppUIControl::getMediaPlayingSongIndex() const
{
    return Player::getInstance().currentSongIndex();
}
