#include "songlist.h"

SongList::SongList(QObject *parent) : QAbstractListModel(parent)
{
    // Initialization, if needed
}

SongList& SongList::instance()
{
    static SongList instance; // Static instance ensures a single instance is created
    return instance;
}

int SongList::rowCount(const QModelIndex &parent) const
{
    if (parent.isValid())
        return 0;

    return m_songs.size();
}

QVariant SongList::data(const QModelIndex &index, int role) const
{
    if (!index.isValid() || index.row() >= m_songs.size())
        return QVariant();

    const Song &song = m_songs[index.row()];

    switch (role) {
    case TitleRole:
        return song.title();
    case ImageRole:
        return song.image();
    case DurationRole:
        return song.duration();
    default:
        return QVariant();
    }
}

QHash<int, QByteArray> SongList::roleNames() const
{
    QHash<int, QByteArray> roles;
    roles[TitleRole] = "title";
    roles[ImageRole] = "image";
    roles[DurationRole] = "duration";
    return roles;
}

void SongList::addSong(const Song &song)
{
    beginInsertRows(QModelIndex(), m_songs.size(), m_songs.size());
    m_songs.append(song);
    endInsertRows();
}

Song* SongList::getSong(int index){
    if(index <0 || index >= m_songs.size()) {
        return nullptr;
    }

    return &m_songs[index];
}
