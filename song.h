#ifndef SONG_H
#define SONG_H

#include <taglib/taglib.h>
#include <taglib/fileref.h>

#include <QString>
#include <QUrl>

class Song
{
public:
    Song(const QString &filePath);

    QString title() const;
    QString singer() const;
    QUrl    image() const;
    int     duration() const;
    QString path() const;

private:
    void    extractMetaData(const QString &filePath);
    QString saveImageToFile(const TagLib::ByteVector &imageData);

private:
    QString m_title;
    QString m_singer;
    QUrl    m_image;
    int     m_duration;
    QString     m_path;
};

#endif // SONG_H
