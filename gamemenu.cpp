#include "gamemenu.h"

GameMenu::GameMenu(QWidget *parent)
    :QDialog(parent)
{
    menu_song_player_ = new QMediaPlayer(this);
    song_list_ = new SongList(this);

    menu_play_button_ = new QPushButton(this);
    menu_setting_button_ = new QPushButton(this);
    menu_back_button_ = new QPushButton(this);

    menu_play_button_palette_ = menu_play_button_->palette();
    menu_setting_button_palette_ = menu_setting_button_->palette();
    menu_back_button_palette_ = menu_back_button_->palette();

    game_controller_ = new GameController(this);

    // Set menu window background
    this->setFixedSize(1000,600);
    this->setWindowTitle("Menu");

    menu_play_button_palette_.setColor(QPalette::Button, QColor(145, 253, 235, 125));
    menu_setting_button_palette_.setColor(QPalette::Button, QColor(145, 253, 235, 125));
    menu_back_button_palette_.setColor(QPalette::Button, QColor(145, 253, 235, 125));

    menu_play_button_->setPalette(menu_play_button_palette_);
    menu_setting_button_->setPalette(menu_setting_button_palette_);
    menu_back_button_ ->setPalette(menu_back_button_palette_);

    menu_play_button_->setAutoFillBackground(true);
    menu_setting_button_->setAutoFillBackground(true);
    menu_back_button_ ->setAutoFillBackground(true);

    menu_play_button_->setGeometry(425, 225, 150, 100);
    menu_setting_button_->setGeometry(50, 400, 100, 60);
    menu_back_button_->setGeometry(50, 500, 100, 60);

    menu_play_button_->setText("PLAY");
    menu_setting_button_->setText("SETTING");
    menu_back_button_->setText("BACK");

    menu_play_button_->setFont(QFont("Courier", 18, QFont::Bold));
    menu_setting_button_->setFont(QFont("Courier", 18, QFont::Bold));
    menu_back_button_->setFont(QFont("Courier", 18, QFont::Bold));

    menu_play_button_->update();
    menu_setting_button_->update();
    menu_back_button_->update();

    // Initialize
    song_list_->menu_song_playlist_->setPlaybackMode(QMediaPlaylist::CurrentItemInLoop);
    song_list_->game_video_playlist_->setPlaybackMode(QMediaPlaylist::CurrentItemOnce);
    game_controller_->InitObjectPool();

    // Connect Object
    QObject::connect(this->song_list_, &QComboBox::currentTextChanged, this, &GameMenu::ChangeMenuMedia);
    QObject::connect(this->menu_back_button_, &QPushButton::clicked, this, &GameMenu::close);
    QObject::connect(this->menu_back_button_, &QPushButton::clicked, parent, &QWidget::show);
    QObject::connect(this->menu_play_button_, &QPushButton::clicked, this, &GameMenu::PlayGame);
    QObject::connect(this->game_controller_, &GameController::BacktoMenu, this, &GameMenu::BacktoMenu);
    QObject::connect(this, &GameMenu::InitNoteData, this->game_controller_, &GameController::InitNoteData);
    QObject::connect(game_controller_->score_window_->back_menu_, &QPushButton::clicked, this, &GameMenu::BacktoMenu);
}

GameMenu::~GameMenu()
{

}

void GameMenu::InitGameMenu(void)
{
    menu_window_background_ = QPixmap(":/images/IntroSong");
    this->temp_string_ = "IntroSong";
    menu_window_background_ = menu_window_background_.scaled(1000, 600, Qt::IgnoreAspectRatio, Qt::SmoothTransformation);
    menu_window_palette_.setBrush(QPalette::Background, menu_window_background_);
    this->setPalette(menu_window_palette_);

    menu_song_player_->setPlaylist(song_list_->menu_song_playlist_);
    game_controller_->game_song_player_->setPlaylist(song_list_->menu_song_playlist_);

    game_controller_->game_video_player_->setPlaylist(song_list_->game_video_playlist_);
    game_controller_->game_video_player_->setVideoOutput(game_controller_->game_window_->game_video_player_wi_);

    menu_song_player_->play();
}

void GameMenu::ChangeMenuMedia(QString temp_string)
{
    this->temp_string_ = temp_string;
    menu_window_background_ = QPixmap(":/images/" + temp_string);
    menu_window_background_ = menu_window_background_.scaled(1000, 600, Qt::IgnoreAspectRatio, Qt::SmoothTransformation);
    menu_window_palette_.setBrush(QPalette::Background, menu_window_background_);
    this->setPalette(menu_window_palette_);
    song_list_->menu_song_playlist_->setCurrentIndex((*song_list_->song_hash_)[this->temp_string_]);
}

void GameMenu::PlayGame(void)
{
    /* Stop menu actions */
    emit InitNoteData(this->temp_string_);
    menu_song_player_->pause();

    game_controller_->game_window_->show();
    game_controller_->game_window_->taiko_dog_->at(0)->show();
    game_controller_->game_window_->score_label_->setText(QString("%1").arg(QString::number(0).toInt(), 8, 10, QLatin1Char('0')));
    game_controller_->game_window_->correct_rate_label_->setText(QString::number(0, 'f', 2) + "%");
    game_controller_->game_window_->combo_label_->setText(QString::number(0));
    song_list_->menu_song_playlist_->setPlaybackMode(QMediaPlaylist::CurrentItemOnce);
    game_controller_->game_video_player_->play();
    game_controller_->game_song_player_->play();
    song_list_->game_video_playlist_->setCurrentIndex((*song_list_->song_hash_)[this->temp_string_]);
    song_list_->menu_song_playlist_->setCurrentIndex((*song_list_->song_hash_)[this->temp_string_]);
    game_controller_->song_timer_->start(100);  /* 1ms = 100t */
    game_controller_->note_runner_->start(game_controller_->fps_);
}

// Initialize track pool and note
void GameMenu::BacktoMenu(void)
{
    song_list_->menu_song_playlist_->setPlaybackMode(QMediaPlaylist::CurrentItemInLoop);
    song_list_->menu_song_playlist_->setCurrentIndex((*song_list_->song_hash_)[this->temp_string_]);
    menu_song_player_->play();
    game_controller_->score_window_->close();
    game_controller_->song_timer_->stop();
    game_controller_->note_runner_->stop();
    game_controller_->current_time_ = 0;
    game_controller_->current_index_ = 0;
    game_controller_->current_dog_index_ = 0;
    game_controller_->occur_note_time_container_->clear();
    game_controller_->note_type_container_->clear();
    game_controller_->combo_num_ = 0;
    game_controller_->score_ = 0;
    game_controller_->correct_rate_ = 0.0;
    game_controller_->total_note_ = 0;
    game_controller_-> correct_note_ = 0;
    if(!game_controller_->track_pool_->empty()) {
        for(Note *x : *(game_controller_->track_pool_)) {
            x->note_pos_x_ = 1450;
            x->hide();
            game_controller_->object_pool_->EmplaceNote(game_controller_->track_pool_->front());
            game_controller_->track_pool_->pop_front();
        }
    }
    for(size_t i = 0; i < 7; i++)  {
        game_controller_->game_window_->taiko_dog_->at(i)->hide();
    }
}

//qDebug() << temp_string_<< (*song_list_->song_hash_)[this->temp_string_];
//qDebug() << temp_string << (*song_list_->song_hash_)[temp_string];
//game_controller_->drum_player_->play();
