#ifndef GAMEMENU_H
#define GAMEMENU_H
#include <QDialog>
#include <QMediaPlayer>
#include <QString>
#include <QPushButton>
#include "songlist.h"
#include "gamecontroller.h"

class GameMenu :public QDialog
{
    Q_OBJECT
public:
    QPushButton *menu_play_button_;
    QPushButton *menu_setting_button_;
    QPushButton *menu_back_button_;

    QMediaPlayer *menu_song_player_;

    QPixmap menu_window_background_;
    QPalette menu_window_palette_;
    QPalette menu_play_button_palette_;
    QPalette menu_setting_button_palette_;
    QPalette menu_back_button_palette_;

    GameController *game_controller_;
    QString temp_string_;

    SongList *song_list_;

    GameMenu(QWidget *parent = nullptr);
    ~GameMenu();
    void InitGameMenu(void);       //  When main_window_play_button_ clicked
    void ChangeMenuMedia(QString); //  When songlist is changed
    void PlayGame(void);           //  When menu_play_button_ clicked
    void BacktoMenu(void);           //  When game stop
signals:
    void InitNoteData(QString);
};

#endif // GAMEMENU_H
