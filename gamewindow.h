#ifndef GAMEWINDOW_H
#define GAMEWINDOW_H
#include <QKeyEvent>
#include <QApplication>
#include <QtMultimediaWidgets>
#include <QPushButton>
#include <QVideoWidget>
#include <QWidget>
#include <QDialog>
#include <QVBoxLayout>
#include <QLabel>
#include <vector>

class GameWindow : public QDialog
{
    Q_OBJECT
public:
    std::vector<QLabel *> *taiko_dog_;
    QLabel *track_picture_;
    QLabel *upper_background_;
    QLabel *score_label_;
    QLabel *correct_rate_label_;
    QLabel *combo_label_;

    QPushButton *game_back_;
    QPalette game_back_palette_;

    QPixmap track_pixmap_;
    QPixmap upper_pixmap_;

    QVideoWidget *game_video_player_wi_;
    QVBoxLayout *game_window_layout_;
    QWidget *key_sensor_;

    GameWindow(QWidget *parent = nullptr);
    ~GameWindow();
signals:
     void keyPressEvent(QKeyEvent *);
};

#endif // GAMEWINDOW_H

//QPushButton *game_continue_;
//QPalette game_continue_palette_;
