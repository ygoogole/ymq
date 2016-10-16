//
// Created by i059483 on 9/20/15.
//

#include <sys/errno.h>
#include "IoThread.hpp"
#include "YCommand.hpp"

ymq::IoThread::IoThread( ymq::Context *ctx, uint32_t tid )
    :YObject(ctx, tid){

    epoller_ = new (std::nothrow) ymq::YEPoller(*ctx);

    mailbox_handle_ = epoller_->add_fd(mailbox_.get_fd(), this);
    epoller_->set_pollin(mailbox_handle_);

}

ymq::IoThread::~IoThread() {

    delete epoller_;
    epoller_ = nullptr;
}

void ymq::IoThread::in_event(){

    YCommand cmd;
    int rc = mailbox_.recv(&cmd, 0);

    while (rc == 0 || errno == EINTR){

        if (rc == 0){
            cmd.destination->process_command(cmd);
        }

        rc = mailbox_.recv(&cmd, 0);
    }

}

void ymq::IoThread::out_event() {
    // never called
}

void ymq::IoThread::timer_event(int id) {
}

void ymq::IoThread::process_plug() {
    YObject::process_plug();
}

void ymq::IoThread::process_bind() {
    YObject::process_bind();
}

void ymq::IoThread::start() {

    epoller_->start();
}

void ymq::IoThread::stop() {

}

ymq::YMailbox *ymq::IoThread::get_mailbox() {
    return &mailbox_;
}

void ymq::IoThread::process_stop() {

    epoller_->rm_fd (mailbox_handle_);
    epoller_->stop ();
}

ymq::YEPoller *ymq::IoThread::get_poller() {
    return epoller_;
}
