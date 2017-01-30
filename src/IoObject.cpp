#include "IoObject.hpp"
#include "IoThread.hpp"

using namespace ymq;

IoObject::IoObject(IoThread *thread)
    : poller_(nullptr) {

    if (thread) {
        poller_ = thread->getPoller();
        io_thread_ = thread;
    }
}

IoObject::~IoObject() {

}

IoObject::handle_t IoObject::addFd(fd_t fd) {
    return poller_->addFd(fd, this);
}

void IoObject::rmFd(IoObject::handle_t handle) {
    return poller_->rmFd(handle);
}

void IoObject::setPollin(IoObject::handle_t handle) {
    poller_->setPollin(handle);
}

void IoObject::resetPollin(IoObject::handle_t handle) {
    poller_->resetPollin(handle);
}

void IoObject::setPollout(IoObject::handle_t handle) {
    poller_->setPollout(handle);
}

void IoObject::resetPollout(IoObject::handle_t handle) {
    poller_->resetPollout(handle);
}

void IoObject::inEvent() {
    assert(false);
}

void IoObject::outEvent() {
    assert(false);
}
