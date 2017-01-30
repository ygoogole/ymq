#include "Epoller.hpp"
#include <thread>
#include <iostream>
#include <string.h>

namespace ymq {

Epoller::Epoller()
    : stop_(false) {

    epoll_fd_ = epoll_create1(EPOLL_CLOEXEC);
    assert(epoll_fd_ != -1 && "Epoller() epoll fd error");
}

void Epoller::start() {

    auto thread = std::thread([=] {loop();});
    //auto thread = std::thread(&Epoller::loop, this);
    thread.detach();
}

void Epoller::stop() {
    stop_ = true;
}

Epoller::EpollHandle Epoller::addFd(fd_t fd, EpollerBase *evt) {

    PollEntry *pe = new (std::nothrow) PollEntry;
    if (!pe) {
        return nullptr;
    }

    memset(pe, 0, sizeof(PollEntry));
    pe->fd_ = fd;
    pe->ev_.events = 0;
    pe->ev_.data.ptr = pe;
    pe->events_ = evt;

    int rc = epoll_ctl(epoll_fd_, EPOLL_CTL_ADD, fd, &pe->ev_);
    assert(rc != -1);

    return pe;
}

void Epoller::rmFd(EpollHandle handle) {
    PollEntry *pe = static_cast<PollEntry *>(handle);
    int rc = epoll_ctl(epoll_fd_, EPOLL_CTL_DEL, pe->fd_, &pe->ev_);
    assert(rc != -1);
}

void Epoller::setPollin(EpollHandle handle) {
    PollEntry *pe = static_cast<PollEntry *>(handle);
    pe->ev_.events |= static_cast<short>(EPOLLIN);
    int rc = epoll_ctl(epoll_fd_, EPOLL_CTL_MOD, pe->fd_, &pe->ev_);
    assert(rc != -1);
}

void Epoller::resetPollin(EpollHandle handle) {
    PollEntry *pe = static_cast<PollEntry *>(handle);
    pe->ev_.events &= ~(static_cast<short>(EPOLLIN));
    int rc = epoll_ctl(epoll_fd_, EPOLL_CTL_MOD, pe->fd_, &pe->ev_);
    assert(rc != -1);
}

void Epoller::setPollout(EpollHandle handle) {
    PollEntry *pe = static_cast<PollEntry *>(handle);
    pe->ev_.events |= static_cast<short>(EPOLLOUT);
    int rc = epoll_ctl(epoll_fd_, EPOLL_CTL_MOD, pe->fd_, &pe->ev_);
    assert(rc != -1);
}

void Epoller::resetPollout(EpollHandle handle) {
    PollEntry *pe = static_cast<PollEntry *>(handle);
    pe->ev_.events &= ~(static_cast<short>(EPOLLOUT));
    int rc = epoll_ctl(epoll_fd_, EPOLL_CTL_MOD, pe->fd_, &pe->ev_);
    assert(rc != -1);
}

void Epoller::loop() {

    epoll_event ev_buf[kMaxIoEvent];

    while (!stop_) {
        std::cout << "in new thread Epoller::loop()" << std::endl;

        // -1 to block forever, if no event
        int n = epoll_wait(epoll_fd_, &ev_buf[0], kMaxIoEvent, -1);
        if (n == -1) {
            assert(errno == EINTR);
            //ignore signal handler's interruption
            continue;
        }

        for (int i = 0; i < n; i++) {
           PollEntry *pe = reinterpret_cast<PollEntry *>(ev_buf[i].data.ptr); 
           if (pe->fd_ == -1) {
               continue; 
           }
           if (ev_buf[i].events & EPOLLIN) {
               pe->events_->inEvent();
           }
           if (ev_buf[i].events & EPOLLOUT) {
               pe->events_->outEvent();
           }
        }
    }

    std::cout << "exit thread Epoller::loop()" << std::endl;
}

} //ymq
