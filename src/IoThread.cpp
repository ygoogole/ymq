#include <sys/errno.h>
#include "IoThread.hpp"

using namespace ymq;

namespace ymq {

IoThread::IoThread( Context *ctx, uint32_t tid)
    : EpollerBase()
    , Object(ctx, tid)
    , ctx_(ctx)
{
    epoller_ = new (std::nothrow) Epoller();

    mailbox_handle_ = epoller_->addFd(mailbox_.getFd(), this);
    epoller_->setPollin(mailbox_handle_);
    // mailbox handle need deallocated?
}

IoThread::~IoThread() {
    delete epoller_;
    epoller_ = nullptr;
}

void IoThread::inEvent() {

    Command cmd;
    int rc = mailbox_.recv(&cmd, 0);

    while (rc == 0 || errno == EINTR){

        if (rc == 0){
            cmd.destination->process_command(cmd);
        }

        rc = mailbox_.recv(&cmd, 0);
    }
}

Epoller *IoThread::getPoller() {
    return epoller_;
}

Mailbox& IoThread::getMailbox() {
    return mailbox_;
}

void IoThread::outEvent() {
    // never called
}

void IoThread::start() {

    epoller_->start();
}

void IoThread::stop() {
    epoller_->stop();
}


} // ymq

/*
void IoThread::process_stop() {

    epoller_->rm_fd (mailbox_handle_);
    epoller_->stop ();
}
void IoThread::timer_event(int id) {
}

void IoThread::process_plug() {
}

void IoThread::process_bind() {
}
*/

