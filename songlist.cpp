#include "songlist.h"

SongList::SongList(QWidget *parent)
    :QComboBox(parent)
{
    menu_song_playlist_ = new QMediaPlaylist(this);
    game_video_playlist_ = new QMediaPlaylist(this);
    song_hash_ = new QHash<QString, int>;

    this->setStyleSheet("color: darkCyan;");
    this->setGeometry(675, 25, 300, 50);

    /* Read file and Initialize songlist */
    song_reader_ = new QFile(":/songlist/song_list",this);
    if (!song_reader_->open(QIODevice::ReadOnly | QIODevice::Text)) qDebug() << "Song list can't be opened...";

    while(!song_reader_->atEnd()) {
        temp_song_name_ = song_reader_->readLine();
        temp_song_name_= temp_song_name_.simplified();

        menu_song_playlist_->insertMedia(count_, QUrl("qrc:/songs/" +  temp_song_name_ +  ".mp3"));
        game_video_playlist_->insertMedia(count_, QUrl("qrc:/videos/" +  temp_song_name_ +  ".mp4"));
        qDebug() << "qrc:/videos/" +  temp_song_name_ +  ".mp4" << count_;
        (*song_hash_)[temp_song_name_] = count_;  // Map song(Key) to index(Value)
        this->insertItem(count_++, temp_song_name_);
    }
}

SongList::~SongList()
{
    delete song_hash_;
}
