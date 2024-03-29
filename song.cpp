#include "song.h"

#include <taglib/mpegfile.h>
#include <taglib/id3v2tag.h>
#include <taglib/id3v2frame.h>
#include <taglib/attachedpictureframe.h>

#include <QImage>
#include <QDir>
#include <QDebug>

Song::Song(const QString &filePath)
{
    extractMetaData(filePath);
}

QString Song::title() const
{
    return m_title;
}

QString Song::singer() const
{
    return m_singer;
}

QUrl Song::image() const
{
    return m_image;
}

int Song::duration() const {
    return m_duration;
}

QString Song::path() const {
    return m_path;
}


void Song::extractMetaData(const QString &filePath) {
    TagLib::MPEG::File file(filePath.toStdString().c_str());

    if (!file.isValid()) {
        return;
    }

    TagLib::ID3v2::Tag *tag = file.ID3v2Tag();
    if (!tag) {
        return;
    }

    // Extract title and singer
    m_title = QString::fromWCharArray(tag->title().toCWString());
    m_singer = QString::fromWCharArray(tag->artist().toCWString());


    TagLib::AudioProperties* properties = file.audioProperties();
    if(properties){
        m_duration = properties->length();
        qDebug() << m_duration;
    }else{
        m_duration = 0;
    }
    // Extract album art (image)
    TagLib::ID3v2::FrameList frameList = tag->frameList("APIC");
    if (!frameList.isEmpty()) {
        TagLib::ID3v2::AttachedPictureFrame *pictureFrame = dynamic_cast<TagLib::ID3v2::AttachedPictureFrame *>(frameList.front());
        if (pictureFrame) {
            const TagLib::ByteVector &imageData = pictureFrame->picture();
            QString imagePath = saveImageToFile(imageData);
            m_path  = imagePath;
            m_image = QUrl::fromLocalFile(imagePath);
        }
    }

    if(m_path == ""){
        m_path = QString("/home/Qt/mediaplayer/Image/Hoang_Hau.png");
        m_image = QUrl::fromLocalFile(m_path);
    }
}

QString Song::saveImageToFile(const TagLib::ByteVector &imageData)
{
    QImage image;
    image.loadFromData(reinterpret_cast<const uchar *>(imageData.data()), static_cast<int>(imageData.size()));

    if (!image.isNull()) {
        QString imageFileName = QString("%1/%2_%3.jpg").arg(QDir::tempPath()).arg(m_title).arg(m_singer);
        image.save(imageFileName);
        return imageFileName;
    }

    return QString("");
}
