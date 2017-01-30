//
// Created by i059483 on 9/7/15.
//

#include "YObject.hpp"
#include "Context.hpp"
#include "YCommand.hpp"
#include "YConstPool.hpp"

ymq::YObject::YObject(ymq::Context *ctx, uint32_t tid)
    :ctx_(ctx),
    tid_(tid){

}

ymq::YObject::YObject(ymq::YObject *parent)
    :ctx_(parent->ctx_)
    ,tid_(parent->tid_){

}

ymq::YObject::~YObject() {

}

uint32_t ymq::YObject::get_tid() {
    return tid_;
}

void ymq::YObject::set_tid(uint32_t tid) {
    tid_ = tid;
}

ymq::Context *ymq::YObject::get_context() {
    return ctx_;
}

void ymq::YObject::process_command(ymq::YCommand &cmd) {

    switch (cmd.type){

        case ymq::YCommand::plug :

            process_plug();
            break;

        case ymq::YCommand::bind :

            process_bind();
            break;
    }
}

void ymq::YObject::process_plug() {

}

void ymq::YObject::process_bind() {

}

void ymq::YObject::send_stop() {

    YCommand cmd;
    cmd.destination = this;
    cmd.type = YCommand::stop;
    send_command (cmd);
}

void ymq::YObject::send_command(ymq::YCommand &cmd) {

    //ctx_->send_command (cmd.destination->get_tid (), cmd);
}

ymq::IoThread *ymq::YObject::choose_io_thread() {
    return ctx_->choose_io_thread();
}

void ymq::YObject::send_plug(ymq::YOwner *destination, bool inc_seqnum_) {


//    if (inc_seqnum_)
//        destination->inc_seqnum ();
/*
    YCommand cmd;
    cmd.destination = destination;
    cmd.type = YCommand::plug;
    send_command (cmd);*/
}
