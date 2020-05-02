#include "objectpool.h"

ObjectPool::ObjectPool(QWidget *parent)
    :QWidget(parent)
{
    r_note_pool_ = new std::queue<Note *>;
    l_note_pool_ = new std::queue<Note *>;
    br_note_pool_ = new std::queue<Note *>;
    bl_note_pool_ = new std::queue<Note *>;
}

ObjectPool::~ObjectPool()
{
   delete r_note_pool_;
   delete l_note_pool_;
   delete br_note_pool_;
   delete bl_note_pool_;
}

Note *ObjectPool::PopNote(QString note_type)
{
    Note *temp_note;
    if(note_type == "R") {
        temp_note = r_note_pool_->front();
        r_note_pool_->pop();
    }
    else if(note_type == "L") {
        temp_note = l_note_pool_->front();
        l_note_pool_->pop();
    }
    else if(note_type == "BR") {
        temp_note = br_note_pool_->front();
        br_note_pool_->pop();
    }
    else {
        temp_note = bl_note_pool_->front();
        bl_note_pool_->pop();
    }
    return temp_note;
}

void ObjectPool::EmplaceNote(Note *temp_note)
{
    if(temp_note->note_type_ == "R")  r_note_pool_->emplace(temp_note);
    else if(temp_note->note_type_ == "L")  l_note_pool_->emplace(temp_note);
    else if(temp_note->note_type_ == "BR")  br_note_pool_->emplace(temp_note);
    else this->bl_note_pool_->emplace(temp_note);
}
