#include "scorewindow.h"

ScoreWindow::ScoreWindow(QWidget *parent)
    :QDialog(parent)
{
    this->setFixedSize(750, 350);
    total_label_ = new QLabel(this);
    combo_label_ = new QLabel(this);
    rank_label_ = new QLabel(this);
    accuracy_label_ = new QLabel(this);
    back_menu_ = new QPushButton(this);

    /* Set Button */
    back_menu_palette_ = back_menu_->palette();
    back_menu_palette_ .setColor(QPalette::Button, QColor(173, 239, 228, 125));
    back_menu_->setPalette(back_menu_palette_);
    back_menu_->setAutoFillBackground(true);
    back_menu_->setGeometry(300, 250, 100, 50);
    back_menu_->setText("BACK");
    back_menu_->setFont(QFont("Courier", 18, QFont::Bold));
    back_menu_->update();

    /* Set Label */
    total_label_->setGeometry(50, 20, 300, 80);
    combo_label_->setGeometry(50, 150, 200, 80);
    rank_label_->setGeometry(450, 20, 100, 100);
    accuracy_label_->setGeometry(450, 150, 300, 80);

    total_label_->setFont(QFont("Timers", 30, QFont::Bold));
    combo_label_->setFont(QFont("Timers", 30, QFont::Bold));
    accuracy_label_->setFont(QFont("Timers", 30, QFont::Bold));
}

ScoreWindow::~ScoreWindow()
{

}
