//
// Created by i059483 on 9/21/15.
//

#ifndef YMQ_YEPOLLER_HPP
#define YMQ_YEPOLLER_HPP

#include "YBasePoller.hpp"
#include "Context.hpp"
#include <sys/epoll.h>
#include "YPollEvent.hpp"
#include "YThread.hpp"

namespace ymq{

    class YEPoller : public YBasePoller {

    public:

        typedef void* handle_t;

        YEPoller(const ymq::Context& ctx);
        ~YEPoller();

        handle_t add_fd(fd_t fd, ymq::YPollEvent* event);
        void rm_fd(handle_t handle);
        void set_pollin(handle_t handle);
        void reset_pollin(handle_t handle);
        void set_pollout(handle_t handle);
        void reset_pollout(handle_t handle);

        void start();
        void stop();

        YThread thread_;

    private:

        static void worker_routine( void* args );
        void loop();

        const Context& ctx_;
        fd_t epoll_fd_;

        struct epoll_entry_t{

            fd_t fd;
            epoll_event ev;
            ymq::YPollEvent *events;
        };

        bool stopping_;

        YEPoller(const YEPoller &);
        const YEPoller & operator=(const YEPoller &);
    };
}



#endif //YMQ_YEPOLLER_HPP
