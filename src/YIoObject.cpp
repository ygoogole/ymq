//
// Created by i059483 on 10/17/15.
//

#include "YIoObject.hpp"
#include "IoThread.hpp"

ymq::YIoObject::YIoObject(ymq::IoThread *thread)
    :poller_(NULL){

    if (thread)
        plug(thread);
}

ymq::YIoObject::~YIoObject() {

}

void ymq::YIoObject::plug(ymq::IoThread *io_thread) {

    //poller_ = io_thread->getPoller();
}

void ymq::YIoObject::unplug() {

    poller_ = NULL;
}

ymq::YIoObject::handle_t ymq::YIoObject::add_fd(ymq::fd_t fd) {
    return poller_->add_fd(fd, this);
}

void ymq::YIoObject::rm_fd(ymq::YIoObject::handle_t handle) {
    return poller_->rm_fd(handle);
}

void ymq::YIoObject::set_pollin(ymq::YIoObject::handle_t handle) {
    poller_->set_pollin(handle);
}

void ymq::YIoObject::reset_pollin(ymq::YIoObject::handle_t handle) {
    poller_->reset_pollin(handle);
}

void ymq::YIoObject::set_pollout(ymq::YIoObject::handle_t handle) {
    poller_->set_pollout(handle);
}

void ymq::YIoObject::reset_pollout(ymq::YIoObject::handle_t handle) {
    poller_->reset_pollout(handle);
}

void ymq::YIoObject::add_timer(int timout, int id) {
    //poller_->add_timer
}

void ymq::YIoObject::cancel_timer(int id_) {
    //poller_->cancel_timer
}

void ymq::YIoObject::in_event() {

}

void ymq::YIoObject::out_event() {

}

void ymq::YIoObject::timer_event(int id) {

}
