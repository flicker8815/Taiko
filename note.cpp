#include "note.h"

Note::Note(QDialog *parent, QString note_type)
    :QLabel(parent)
{
    /* Initialize note position */
    this->note_type_ = note_type;
    note_pos_x_ = 1450;

    /* Set note's image */
    if(note_type == "R") node_image_ = QPixmap(":/notes/R");
    else if(note_type == "L") node_image_ = QPixmap(":/notes/L");
    else if(note_type == "BR")  node_image_ = QPixmap(":/notes/BR");
    else node_image_ = QPixmap(":/notes/BL");

    if(note_type == "R" || note_type == "L") {
        node_image_ = node_image_.scaled(100, 100, Qt::IgnoreAspectRatio, Qt::SmoothTransformation);
        note_pos_y_ = 255;
        this->setFixedSize(100, 100);
    }else {
        node_image_ = node_image_.scaled(150, 150, Qt::IgnoreAspectRatio, Qt::SmoothTransformation);
        note_pos_y_ = 230;
        this->setFixedSize(150, 150);
    }
    this->setPixmap(node_image_);
}

Note::~Note()
{

}
