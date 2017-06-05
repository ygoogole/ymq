#include "Object.hpp"
#include "Context.hpp"
#include "Command.hpp"
#include "YConstPool.hpp"

using namespace ymq;

Object::Object(Context *ctx, uint32_t tid)
    :ctx_(ctx),
    tid_(tid){

}

Object::Object(Object *parent)
    : ctx_(parent->ctx_)
    , tid_(parent->tid_){

}

Object::~Object() {

}

uint32_t Object::get_tid() {
    return tid_;
}

void Object::set_tid(uint32_t tid) {
    tid_ = tid;
}

Context *Object::get_context() {
    return ctx_;
}

void Object::process_command(Command &cmd) {

    switch (cmd.type){

        case Command::plug :

            process_plug();
            break;

        case Command::bind :

            process_bind();
            break;

        case Command::attach:
            process_attach();
            break;
    }
}

void Object::process_attach() {
}

void Object::process_plug() {
}

void Object::process_bind() {
}

void Object::send_stop() {

    Command cmd;
    cmd.destination = this;
    cmd.type = Command::stop;
    send_command (cmd);
}

void Object::send_command(Command &cmd) {
    ctx_->send_command (cmd.destination->get_tid (), cmd);
}

IoThread *Object::choose_io_thread() {
    return ctx_->choose_io_thread();
}

void Object::send_plug(YOwner *destination, bool inc_seqnum_) {


//    if (inc_seqnum_)
//        destination->inc_seqnum ();
/*
    Command cmd;
    cmd.destination = destination;
    cmd.type = Command::plug;
    send_command (cmd);*/
}
