#ifndef GAMECONTROLLER_H
#define GAMECONTROLLER_H
#include <QtGui>
#include <QTimer>
#include <QFile>
#include <QMediaPlayer>
#include <QWidget>
#include <QString>
#include <QLabel>
#include <vector>
#include <deque>
#include "objectpool.h"
#include "gamewindow.h"
#include "note.h"
#include "scorewindow.h"

class GameController : public QWidget
{
    Q_OBJECT
public:
    int total_time_ = 0;
    int fps_ = 0; // fps_ = 33
    int note_v_ = 10;
    int current_time_ = 0;
    int key_ = 0;
    int combo_num_ = 0;
    int total_note_ = 0;
    int correct_note_ = 0;
    int score_ = 0;
    double correct_rate_ = 0.0;

    size_t current_index_ = 0;
    size_t current_dog_index_ = 0;

    GameWindow *game_window_;
    ScoreWindow *score_window_;

    QMediaPlayer *game_video_player_;
    QMediaPlayer *game_song_player_;

    ObjectPool *object_pool_;

    std::deque<Note *> *track_pool_;
    std::vector<int> *occur_note_time_container_;
    std::vector<QString> *note_type_container_;

    QFile *note_data_reader_;
    QTimer *song_timer_;
    QTimer *note_runner_;

    void StopGame(void);
    void InitObjectPool(void);
    void InitNoteData(QString);
    void TakePoolNote(void);
    void MoveNote(void);
    void DogDance(void);
    void CatchNote(QKeyEvent *);
    void ShowScore(void);
    void ComputeScore(void);
    void AddTime(void);
    GameController(QWidget *parent = nullptr);
    ~GameController();
signals:
    void BacktoMenu(void);
    void ShowFinal(void);
};

#endif // GAMECONTROLLER_H

//#include <QMediaPlaylist>
//QMediaPlaylist *drum_playlist_;
//QMediaPlayer *drum_player_;
//  bool pause_game_flag_ = false;
//  Show error bug :
