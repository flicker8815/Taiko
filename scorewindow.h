#ifndef SCOREWINDOW_H
#define SCOREWINDOW_H

#include <QDialog>
#include <QLabel>
#include <QPushButton>
class ScoreWindow : public QDialog
{
public:
    QPixmap rank_pixmap_;
    QLabel *total_label_;
    QLabel *combo_label_;
    QLabel *rank_label_;
    QLabel *accuracy_label_;
    QPushButton *back_menu_;
    QPalette back_menu_palette_;
    ScoreWindow(QWidget *parent = nullptr);
    ~ScoreWindow();
};

#endif // SCOREWINDOW_H
