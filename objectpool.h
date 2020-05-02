#ifndef OBJECTPOOL_H
#define OBJECTPOOL_H
#include <QString>
#include <queue>
#include <QWidget>
#include <note.h>
class ObjectPool : public QWidget
{
public:
    const int kPoolMaxSize = 20;
    std::queue<Note *> *r_note_pool_;
    std::queue<Note *> *l_note_pool_;
    std::queue<Note *> *br_note_pool_;
    std::queue<Note *> *bl_note_pool_;

    ObjectPool(QWidget *parent = nullptr);
    ~ObjectPool();

    /* Take note method */
    Note* PopNote(QString);
    void EmplaceNote(Note*);
};

#endif // OBJECTPOOL_H
