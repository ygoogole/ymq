//
// Created by i059483 on 10/8/15.
//

#include "YOwner.hpp"

ymq::YOwner::YOwner(ymq::Context *parent, uint32_t tid)
    :YObject(parent, tid)
    ,owner_(nullptr){

}

ymq::YOwner::YOwner(ymq::IoThread *io_thread)
    :YObject((YObject *)io_thread)
    ,owner_(nullptr){

}

ymq::YOwner::~YOwner() {

}

void ymq::YOwner::launch_child(ymq::YOwner *object) {

    object->set_owner(this);

    //send_plug(object);

    //send_own(this, object);
}

void ymq::YOwner::set_owner(ymq::YOwner *owner) {
    owner_ = owner;
}
