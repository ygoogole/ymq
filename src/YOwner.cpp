#include "YOwner.hpp"

using namespace ymq;

YOwner::YOwner(Context *parent, uint32_t tid)
    :Object(parent, tid)
    ,owner_(nullptr){

}

YOwner::YOwner(IoThread *io_thread)
    :Object((Object *)io_thread)
    ,owner_(nullptr){

}

YOwner::~YOwner() {

}

void YOwner::launch_child(YOwner *object) {

    object->set_owner(this);

    //send_plug(object);

    //send_own(this, object);
}

void YOwner::set_owner(YOwner *owner) {
    owner_ = owner;
}
