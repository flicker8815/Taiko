#include "gamecontroller.h"

GameController::GameController(QWidget *parent)
    :QWidget(parent)
{
    game_window_ = new GameWindow(this);
    score_window_ = new ScoreWindow(this);

    game_video_player_ = new QMediaPlayer(this);
    game_song_player_ = new QMediaPlayer(this);

    object_pool_ = new ObjectPool(this);
    track_pool_ = new std::deque<Note *>;

    occur_note_time_container_ = new std::vector<int>;
    note_type_container_ = new std::vector<QString>;

    song_timer_ = new QTimer(this);
    note_runner_ = new QTimer(this);

    /* Connect Object */
    QObject::connect(game_window_->game_back_, &QPushButton::clicked, this, &GameController::StopGame);
    QObject::connect(song_timer_, &QTimer::timeout, this, &GameController::TakePoolNote);
    QObject::connect(song_timer_, &QTimer::timeout, this, &GameController::DogDance);
    QObject::connect(note_runner_, &QTimer::timeout, this, &GameController::MoveNote);
    QObject::connect(game_window_, &GameWindow::keyPressEvent, this, &GameController::CatchNote);
    QObject::connect(this,  &GameController::ShowFinal, this, &GameController::ShowScore);
    QObject::connect(song_timer_, &QTimer::timeout, this, &GameController::ComputeScore);
    QObject::connect(song_timer_, &QTimer::timeout, this, &GameController::AddTime);
}

GameController::~GameController()
{
    delete track_pool_;
};

void GameController::StopGame(void)
{
    game_video_player_->pause();
    game_song_player_->pause();
    game_window_->close();
    emit BacktoMenu();
};

void GameController::InitObjectPool(void)
{
    Note *temp_r_note;
    Note *temp_l_note;
    Note *temp_br_note;
    Note *temp_bl_note;
    for(int i = 0; i < object_pool_->kPoolMaxSize; i++) {
        temp_r_note = new Note(game_window_, "R");
        temp_l_note = new Note(game_window_, "L");
        temp_br_note = new Note(game_window_, "BR");
        temp_bl_note = new Note(game_window_, "BL");
        temp_r_note->hide();
        temp_l_note->hide();
        temp_br_note->hide();
        temp_bl_note->hide();
        this->object_pool_->EmplaceNote(temp_r_note);
        this->object_pool_->EmplaceNote(temp_l_note);
        this->object_pool_->EmplaceNote(temp_br_note);
        this->object_pool_->EmplaceNote(temp_bl_note);
    }
}

void GameController::InitNoteData(QString song_name)
{
    note_data_reader_ = new QFile(":/notesdata/" + song_name, this);
    if (!note_data_reader_->open(QIODevice::ReadOnly | QIODevice::Text)) qDebug() << "Note data can't be opened...";
    QString text_line;
    QStringList list;

    if(!note_data_reader_->atEnd()) {
        text_line = note_data_reader_->readLine();
        text_line = text_line.simplified();
        list = text_line.split(" ", QString::SkipEmptyParts);
        this->total_time_ = list[0].toInt();
        this->fps_ = list[1].toInt();
    }

    while(!note_data_reader_->atEnd()) {
        text_line = note_data_reader_->readLine();
        text_line = text_line.simplified();
        list = text_line.split(" ", QString::SkipEmptyParts);
        occur_note_time_container_ ->emplace_back(list[0].toInt());
        note_type_container_->emplace_back(list[1]);
    }

}

void GameController::AddTime(void)
{
    current_time_ += 100; /* 1ms = 100t */
    if(current_time_ == total_time_) emit ShowFinal();
}

void GameController::TakePoolNote(void)
{
    if(current_time_ >= 0 && current_time_ <= total_time_) {
        if(current_time_ == (*occur_note_time_container_)[current_index_]) {
            if((*note_type_container_)[current_index_] == "R") {
                track_pool_->emplace_back(object_pool_->PopNote("R"));

            }else if((*note_type_container_)[current_index_] == "L") {
                track_pool_->emplace_back(object_pool_->PopNote("L"));

            }else if((*note_type_container_)[current_index_] == "BR") {
                 track_pool_->emplace_back(object_pool_->PopNote("BR"));

            }else {
                 track_pool_->emplace_back(object_pool_->PopNote("BL"));

            }
            current_index_++;
            total_note_++;
        }
    }
}

void GameController::MoveNote(void)
{
    for(Note *x : *track_pool_) {
        x->show();
        x->note_pos_x_ -= note_v_;
        x->setGeometry(x->note_pos_x_, x->note_pos_y_,  x->width(), x->height());
        if(x->note_pos_x_ < 120) {
            combo_num_ = 0;
            game_window_->combo_label_->setText(QString::number(combo_num_));
            x->note_pos_x_ = 1450;
            x->hide();
            object_pool_->EmplaceNote(track_pool_->front());
            track_pool_->pop_front();
        }
    }
}

void GameController::CatchNote(QKeyEvent *event)
{
    key_ = event->key();
    if(!track_pool_->empty()) {
         Note *temp_note = track_pool_->front();

         if(key_ == Qt::Key_O) {
             if(temp_note->note_pos_x_ > 120 && temp_note->note_pos_x_ < 300) {
                 if(temp_note->note_type_ == "L" || temp_note->note_type_ == "BL") {
                     ++combo_num_;
                     ++correct_note_;
                     temp_note->note_pos_x_ = 1450;
                     temp_note->hide();
                     object_pool_->EmplaceNote(track_pool_->front());
                     track_pool_->pop_front();
                 }else if(temp_note->note_type_ == "L" || temp_note->note_type_ == "BL") combo_num_ = 0;
             }
        }else if(key_ == Qt::Key_P) {

             if(temp_note->note_pos_x_ > 120 && temp_note->note_pos_x_ < 300) {
                 if(temp_note->note_type_ == "R" || temp_note->note_type_ == "BR") {
                     ++combo_num_;
                     ++correct_note_;
                     temp_note->note_pos_x_ = 1450;
                     temp_note->hide();
                     object_pool_->EmplaceNote(track_pool_->front());
                     track_pool_->pop_front();
                 }else if(temp_note->note_type_ == "L" || temp_note->note_type_ == "BL") combo_num_ = 0;
             }
         }
    }
};

void GameController::DogDance(void)
{
    game_window_->taiko_dog_->at(current_dog_index_ % 7)->hide();
    game_window_->taiko_dog_->at(++current_dog_index_ % 7)->show();
}

void GameController::ShowScore(void)
{
    game_window_->close();
    score_window_->show();
    score_window_->total_label_->setText("Total score : " + QString::number(this->score_));
    score_window_->combo_label_->setText("Combo : " + QString::number(this->combo_num_));
    score_window_->accuracy_label_->setText("Accuracy : " + QString::number(this->correct_rate_, 'f', 2) + "%");
    if(this->correct_rate_ >= 95) score_window_->rank_pixmap_ = QPixmap(":/images/s");
    else if(this->correct_rate_ >= 90) score_window_->rank_pixmap_ = QPixmap(":/images/a");
    else if(this->correct_rate_ >= 80) score_window_->rank_pixmap_ = QPixmap(":/images/b");
    else if(this->correct_rate_ >= 70) score_window_->rank_pixmap_ = QPixmap(":/images/c");
    else score_window_->rank_pixmap_ = QPixmap(":/images/d");

    score_window_->rank_pixmap_ =  score_window_->rank_pixmap_.scaled(100, 100, Qt::IgnoreAspectRatio, Qt::SmoothTransformation);
    score_window_->rank_label_->setPixmap(score_window_->rank_pixmap_);
    score_window_->total_label_->show();
    score_window_->combo_label_->show();
    score_window_->accuracy_label_->show();
    score_window_->rank_label_->show();
}

void GameController::ComputeScore(void)
{
    score_ = correct_note_ * 300;
    correct_rate_ = (correct_note_ / (total_note_ * 1.0)) * 100;
    game_window_->score_label_->setText(QString("%1").arg(QString::number(score_).toInt(), 8, 10, QLatin1Char('0')));
    game_window_->correct_rate_label_->setText(QString::number(correct_rate_, 'f', 2) + "%");
    game_window_->combo_label_->setText(QString::number(combo_num_));
}

//drum_playlist_ = new QMediaPlaylist(this);
//drum_player_ =  new QMediaPlayer(this);
/* Initialize drum playlist */
//drum_playlist_ ->insertMedia(0, QUrl("qrc:/music/right.wav"));
//drum_playlist_ ->insertMedia(1, QUrl("qrc:/music/left.wav"));
//drum_playlist_ ->setPlaybackMode(QMediaPlaylist::CurrentItemOnce);
//drum_player_->setPlaylist(drum_playlist_);
//drum_player_->setVolume(100);
//game_song_player_->setVolume(30);
//drum_playlist_->setCurrentIndex(1);
//drum_player_->play();
//drum_playlist_->setCurrentIndex(0);
//drum_player_->play();
