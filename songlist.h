// songlistmodel.h
#ifndef SONGLIST_H
#define SONGLIST_H

#include <QObject>
#include <QAbstractListModel>
#include <QList>
#include "song.h"

class SongList : public QAbstractListModel
{
    Q_OBJECT
public:
    enum Role {
        TitleRole = Qt::UserRole + 1,
        ImageRole,
        DurationRole
    };

    static SongList& instance();

    int rowCount(const QModelIndex &parent = QModelIndex()) const override;
    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;

    QHash<int, QByteArray> roleNames() const override;

public:
    void addSong(const Song &song);
    Song* getSong(int index);

private:
    SongList(QObject *parent = nullptr); // Private constructor to prevent external instantiation

    QList<Song> m_songs;
};

#endif
