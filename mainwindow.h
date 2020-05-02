#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QPushButton>
#include <QMediaPlayer>
#include <QMediaPlaylist>
#include "gamemenu.h"

class MainWindow : public QMainWindow
{
    Q_OBJECT
public:
    QMediaPlaylist *start_playlist_;
    QMediaPlayer *start_player_;

    QPushButton *main_window_play_button_;
    QPushButton *main_window_exit_button_;
    QPushButton *main_window_about_button_;

    QPixmap main_window_background_;

    QPalette main_window_palette_;
    QPalette main_play_button_palette_;
    QPalette main_exit_button_palette_;
    QPalette main_about_button_palette_;

    GameMenu *game_menu_;

    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
};

#endif // MAINWINDOW_H
