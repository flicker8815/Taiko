#include "mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    // Set main window background
    this->setFixedSize(1000,600);
    this->setWindowTitle("Taiko!");
    main_window_background_ = QPixmap(":/images/osu_background");
    main_window_background_ = main_window_background_.scaled(1000, 600, Qt::IgnoreAspectRatio, Qt::SmoothTransformation);
    main_window_palette_.setBrush(QPalette::Background, main_window_background_);
    setPalette(main_window_palette_);

    // Set main window button
    main_window_play_button_ = new QPushButton(this);
    main_window_exit_button_ = new QPushButton(this);
    main_window_about_button_ = new QPushButton(this);

    start_player_ = new QMediaPlayer(this);
    start_playlist_ = new QMediaPlaylist(this);
    start_playlist_->insertMedia(0, QUrl("qrc:/songs/start.mp3"));

    start_playlist_ ->setPlaybackMode(QMediaPlaylist::CurrentItemInLoop);
    start_player_->setPlaylist(start_playlist_);
    start_player_->play();

    main_play_button_palette_ = main_window_play_button_->palette();
    main_exit_button_palette_ = main_window_exit_button_->palette();
    main_about_button_palette_ = main_window_about_button_->palette();

    main_play_button_palette_.setColor(QPalette::Button, QColor(67, 110, 238, 125));
    main_exit_button_palette_.setColor(QPalette::Button, QColor(205, 201, 165, 125));
    main_about_button_palette_.setColor(QPalette::Button, QColor(205, 170, 125, 125));

    main_window_play_button_->setPalette(main_play_button_palette_);
    main_window_exit_button_->setPalette(main_exit_button_palette_);
    main_window_about_button_->setPalette(main_about_button_palette_);

    main_window_play_button_->setAutoFillBackground(true);
    main_window_exit_button_->setAutoFillBackground(true);
    main_window_about_button_->setAutoFillBackground(true);

    main_window_play_button_->setGeometry(720, 50, 225, 80);
    main_window_exit_button_->setGeometry(760, 250, 225, 80);
    main_window_about_button_->setGeometry(720, 450, 225, 80);

    main_window_play_button_->setText("PLAY");
    main_window_exit_button_->setText("EXIT");
    main_window_about_button_->setText("ABOUT");

    main_window_play_button_->setFont(QFont("Courier", 18, QFont::Bold));
    main_window_exit_button_->setFont(QFont("Courier", 18, QFont::Bold));
    main_window_about_button_->setFont(QFont("Courier", 18, QFont::Bold));

    main_window_play_button_->update();
    main_window_exit_button_->update();
    main_window_about_button_->update();

    // Game menu
    game_menu_ = new GameMenu(this);

    // Connect Object
    QObject::connect(this->main_window_play_button_, &QPushButton::clicked, this->game_menu_, &QDialog::show);
    QObject::connect(this->main_window_play_button_, &QPushButton::clicked, this, &QWidget::hide);
    QObject::connect(this->main_window_exit_button_, &QPushButton::clicked, this, &QWidget::close);
    QObject::connect(this->main_window_play_button_, &QPushButton::clicked, game_menu_, &GameMenu::InitGameMenu);
    QObject::connect(this->main_window_play_button_, &QPushButton::clicked, start_player_, &QMediaPlayer::stop);
}

MainWindow::~MainWindow()
{

}
