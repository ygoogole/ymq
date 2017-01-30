#ifndef EPOLLER_HPP
#define EPOLLER_HPP

#include <sys/epoll.h>
#include "Common.hpp"
#include "EpollerBase.hpp"

namespace ymq {

    class Epoller {
    public:
        typedef void* EpollHandle;

        Epoller();
        void start();
        void stop();

        EpollHandle addFd(fd_t fd, EpollerBase *evt);
        void rmFd(EpollHandle handle);
        void setPollin(EpollHandle handle);
        void resetPollin(EpollHandle handle);
        void setPollout(EpollHandle handle);
        void resetPollout(EpollHandle handle);
        void loop();

    private:
        bool stop_;
        fd_t epoll_fd_;

        struct PollEntry {
            fd_t fd_;
            epoll_event ev_;
            EpollerBase *events_;
        };
    };
}

#endif
