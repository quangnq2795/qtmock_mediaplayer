#ifndef IMEDIAPLAYERCONTROLRECEIVER_H
#define IMEDIAPLAYERCONTROLRECEIVER_H

#include <QObject>
#include <imediaplayercontrol.h>
#include <imediaplayercontroladaptor.h>

class IMediaPlayerControlReceiver : public IMediaPlayerControl
{
    Q_OBJECT
public:
    IMediaPlayerControlReceiver();

    bool play() override;
    bool pause() override;
    bool next() override;
    bool previous() override;
    bool isPlaying() override;
    
    bool getTimePlaying(int& currentTime) override;
    bool getSongPlaying(int& SongId, QString& songName, QString& singer, QString& imagePath,int& totalTime) override;

private:
    IMediaPlayerControlAdaptor* m_mediaAdapter;
}  ;

#endif // IMEDIAPLAYERCONTROLRECEIVER_H
