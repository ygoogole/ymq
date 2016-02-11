//
// Created by i059483 on 9/20/15.
//

#include <sys/errno.h>
#include "YIOThread.hpp"
#include "YCommand.hpp"

ymq::YIOThread::YIOThread( ymq::YContext *ctx, uint32_t tid )
    :YObject(ctx, tid){

    epoller_ = new (std::nothrow) ymq::YEPoller(*ctx);

    mailbox_handle_ = epoller_->add_fd(mailbox_.get_fd(), this);
    epoller_->set_pollin(mailbox_handle_);

}

ymq::YIOThread::~YIOThread() {

    delete epoller_;
    epoller_ = nullptr;
}

void ymq::YIOThread::in_event(){

    YCommand cmd;
    int rc = mailbox_.recv(&cmd, 0);

    while (rc == 0 || errno == EINTR){

        if (rc == 0){
            cmd.destination->process_command(cmd);
        }

        rc = mailbox_.recv(&cmd, 0);
    }

}

void ymq::YIOThread::out_event() {
    // never called
}

void ymq::YIOThread::timer_event(int id) {
}

void ymq::YIOThread::process_plug() {
    YObject::process_plug();
}

void ymq::YIOThread::process_bind() {
    YObject::process_bind();
}

void ymq::YIOThread::start() {

    epoller_->start();
}

void ymq::YIOThread::stop() {

}

ymq::YMailbox *ymq::YIOThread::get_mailbox() {
    return &mailbox_;
}

void ymq::YIOThread::process_stop() {

    epoller_->rm_fd (mailbox_handle_);
    epoller_->stop ();
}

ymq::YEPoller *ymq::YIOThread::get_poller() {
    return epoller_;
}
