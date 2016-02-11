//
// Created by i059483 on 9/21/15.
//

#include <assert.h>
#include <unistd.h>
#include "YEPoller.hpp"

ymq::YEPoller::YEPoller(const ymq::YContext &ctx)
    : ctx_(ctx), stopping_(false){

    epoll_fd_ = epoll_create(1);
    assert(epoll_fd_ != -1);
}

ymq::YEPoller::~YEPoller() {

    close(epoll_fd_);
}

ymq::YEPoller::handle_t ymq::YEPoller::add_fd(ymq::fd_t fd, ymq::YPollEvent *event) {

    epoll_entry_t* pe = new (std::nothrow) epoll_entry_t;
    assert(pe != nullptr);

    pe->fd = fd;
    pe->events = event;
    pe->ev.events = 0;
    pe->ev.data.ptr = pe;

    int rc = epoll_ctl(epoll_fd_, EPOLL_CTL_ADD, pe->fd, &pe->ev );
    assert(rc != -1);

    //adjust_load(1);

    return pe;
}

void ymq::YEPoller::rm_fd(ymq::YEPoller::handle_t handle) {

    epoll_entry_t *pe = (epoll_entry_t*)handle;
    int rc = epoll_ctl(epoll_fd_, EPOLL_CTL_DEL, pe->fd, &pe->ev);
    assert( rc != -1);
}

void ymq::YEPoller::set_pollin(ymq::YEPoller::handle_t handle) {

    epoll_entry_t *pe = (epoll_entry_t*)handle;
    pe->ev.events |= EPOLLIN;

    int rc = epoll_ctl(epoll_fd_, EPOLL_CTL_MOD, pe->fd, &pe->ev);
    assert( rc != -1);
}

void ymq::YEPoller::reset_pollin(ymq::YEPoller::handle_t handle) {
    epoll_entry_t *pe = (epoll_entry_t*) handle;
    pe->ev.events &= ~((short) EPOLLIN);
    int rc = epoll_ctl (epoll_fd_, EPOLL_CTL_MOD, pe->fd, &pe->ev);
    assert (rc != -1);
}

void ymq::YEPoller::set_pollout(ymq::YEPoller::handle_t handle) {

    epoll_entry_t *pe = (epoll_entry_t*)handle;
    pe->ev.events |= EPOLLOUT;

    int rc = epoll_ctl(epoll_fd_, EPOLL_CTL_MOD, pe->fd, &pe->ev);
    assert( rc != -1);
}

void ymq::YEPoller::reset_pollout(ymq::YEPoller::handle_t handle) {

    epoll_entry_t *pe = (epoll_entry_t*) handle;
    pe->ev.events &= ~((short) EPOLLOUT);

    int rc = epoll_ctl (epoll_fd_, EPOLL_CTL_MOD, pe->fd, &pe->ev);
    assert (rc != -1);
}

void ymq::YEPoller::start() {

    //start a new thread for epolling , this is managed by context
    ctx_.start_thread(thread_, worker_routine, this);

}

void ymq::YEPoller::stop() {

    stopping_ = true;
}

void ymq::YEPoller::worker_routine(void *args) {

    ((YEPoller* )args)->loop();
}

void ymq::YEPoller::loop() {

    epoll_event ev_buf[ymq::YConstPool::kMaxIoEvent];

    while (!stopping_){
        // timeout = 1000ms
        int n = epoll_wait(epoll_fd_, &ev_buf[0], ymq::YConstPool::kMaxIoEvent, 1000 );
        if (n == -1){
            continue;
        }

        for (int i = 0; i < n; i++) {

            epoll_entry_t *pe = (epoll_entry_t *) ev_buf[i].data.ptr;

            if (pe->fd == ymq::YConstPool::kRetired_fd)
                continue;

            if (ev_buf [i].events & (EPOLLERR | EPOLLHUP))
                pe->events->in_event();
            if (pe->fd == ymq::YConstPool::kRetired_fd)
                continue;
            if (ev_buf [i].events & EPOLLOUT)
                pe->events->out_event();
            if (pe->fd == ymq::YConstPool::kRetired_fd)
                continue;
            if (ev_buf [i].events & EPOLLIN)
                pe->events->in_event();

        }

    }




}
