#ifndef AppUIControl_H
#define AppUIControl_H

#include <QObject>
#include <QString>
#include <QSharedPointer>

#include "iappuicontrolreceiver.h"
#include "imediaplayercontrolreceiver.h"

class AppUIControl: public QObject
{
    Q_OBJECT
    Q_PROPERTY(bool isMediaPlaying READ getMediaPlayerState NOTIFY playerStateChanged)
    Q_PROPERTY(int  playingSongIndex READ getMediaPlayingSongIndex NOTIFY playerSongPlayingChanged)
    Q_PROPERTY(bool isMediaAppVisible READ getMediaAppVisibleProperty NOTIFY mediaAppVisiblePropertyChanged)

public:
    AppUIControl(QObject *parent = nullptr);

    // UI event
    Q_INVOKABLE void uiEventBackToHomeOnClicked();
    Q_INVOKABLE void uiEventMediaPlayStateChanged();
    Q_INVOKABLE void uiMusicSelectedChanged(int clickedIndex);

signals:
    // UI update signal
    void playerStateChanged(bool isPlaying);
    void mediaAppVisiblePropertyChanged();
    void playerSongPlayingChanged(int index, QString songName, QString singer, QString imagePath, int totalTime);
    void homeScreenAppVisibleChanged();

public slots:
    void handleMediaAppVisibleChanged(bool val);
    void handleHomeScreenAppVisibleChanged();

private:
    int  getMediaPlayingSongIndex() const;
    bool getMediaPlayerState() const;
    bool getMediaAppVisibleProperty() const;

private:
    bool    m_appVisible;

    IAppUIControlReceiver* m_UIControlReceiver;
    IMediaPlayerControlReceiver* m_playerReceiver;
};

#endif // AppUIControl_H

