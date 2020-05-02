#ifndef SONGLIST_H
#define SONGLIST_H
#include <QComboBox>
#include <QtGui>
#include <QFile>
#include <QString>
#include <QTextStream>
#include <QHash>
#include <QMediaPlaylist>
class SongList : public QComboBox
{
public:
    int count_ = 0;
    QHash<QString, int> *song_hash_;

    QMediaPlaylist *menu_song_playlist_;
    QMediaPlaylist *game_video_playlist_;
    QFile *song_reader_;
    QString temp_song_name_;

    SongList(QWidget *parent = nullptr);
    ~SongList();
};

#endif // SONGLIST_H
