#include "gamewindow.h"

GameWindow::GameWindow(QWidget *parent)
    :QDialog(parent)
{
    this->setFixedSize(1400,800);
    this->setWindowTitle("Game");

    game_window_layout_ = new QVBoxLayout(this);
    game_video_player_wi_ = new QVideoWidget();

    track_picture_ = new QLabel();
    upper_background_ = new QLabel();

    game_back_ = new QPushButton(this);
    key_sensor_ = new QWidget(this);
    taiko_dog_ = new std::vector<QLabel *>;

    /* Set Button */
    game_back_palette_ = game_back_->palette();
    game_back_palette_.setColor(QPalette::Button, QColor(173, 239, 228, 125));
    game_back_->setPalette(game_back_palette_);
    game_back_->setAutoFillBackground(true);
    game_back_->setGeometry(1225, 650, 150, 100);
    game_back_->setText("BACK");
    game_back_->setFont(QFont("Courier", 18, QFont::Bold));
    game_back_->update();

    /* Set Layout */
    track_pixmap_ = QPixmap(":/images/track");
    upper_pixmap_ = QPixmap(":/images/taikoslider");
    track_pixmap_ =  track_pixmap_.scaled(1400, 200, Qt::IgnoreAspectRatio, Qt::SmoothTransformation);
    upper_pixmap_ =  upper_pixmap_.scaled(1400, 200, Qt::IgnoreAspectRatio, Qt::SmoothTransformation);

    track_picture_->setPixmap(track_pixmap_);
    upper_background_->setPixmap(upper_pixmap_);

    game_video_player_wi_->setFixedSize(1200, 400);

    game_window_layout_->setMargin(0);
    game_window_layout_->addWidget(upper_background_);
    game_window_layout_->addWidget(track_picture_);
    game_window_layout_->addWidget(game_video_player_wi_);

    this->setLayout(game_window_layout_);

    /* Initialize */
    taiko_dog_->resize(7);
    for(size_t i = 0; i < 7; i++) {
        QPixmap temp_dog_picture = QPixmap(":/images/dog" +  QString::number(i));
        temp_dog_picture = temp_dog_picture.scaled(300, 225, Qt::IgnoreAspectRatio, Qt::SmoothTransformation);
        taiko_dog_->at(i) = new QLabel(this);
        taiko_dog_->at(i)->setPixmap(temp_dog_picture);
        taiko_dog_->at(i)->setGeometry(20, 25, 300, 225);
        taiko_dog_->at(i)->hide();
    }

    score_label_ = new QLabel("00000000", this);
    correct_rate_label_ = new QLabel("00.00%", this);
    combo_label_ = new QLabel("0", this);
    score_label_->setFont(QFont("Timers", 60, QFont::Bold));
    correct_rate_label_->setFont(QFont("Timers", 40, QFont::Bold));
    combo_label_->setFont(QFont("Timers", 40, QFont::Bold));
    combo_label_->setStyleSheet("color:black;");

    score_label_->setGeometry(1075, 10, 350, 50);
    correct_rate_label_->setGeometry(1240, 80, 150, 50);
    combo_label_->setGeometry(70, 275, 80, 50);

    /* Set Keypress event */
    key_sensor_->setFocusPolicy(Qt::StrongFocus);
}

GameWindow::~GameWindow()
{

}

/*
game_continue_ = new QPushButton(this);
game_continue_palette_ = game_continue_->palette();
game_continue_palette_ .setColor(QPalette::Button, QColor(173, 239, 228, 125));
game_continue_->setPalette(game_continue_palette_);
game_continue_->setAutoFillBackground(true);
game_continue_->setGeometry(1225, 500, 150, 100);
game_continue_->setText("PLAY");
game_continue_->setFont(QFont("Courier", 18, QFont::Bold));
game_continue_->update();
*/
