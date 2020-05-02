#ifndef NOTE_H
#define NOTE_H
#include <QLabel>
#include <QDialog>
#include <QString>
class Note : public QLabel
{
public:
    int note_pos_x_;
    int note_pos_y_;
    QString note_type_;
    QPixmap node_image_;
    Note(QDialog *parent = nullptr, QString note_type = "R");
    ~Note();
};

#endif // NOTE_H
