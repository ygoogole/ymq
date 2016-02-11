//
// Created by i059483 on 10/4/15.
//

#ifndef YMQ_YSIGNALER_HPP
#define YMQ_YSIGNALER_HPP

#include <unistd.h>
#include "YCommon.hpp"

namespace ymq{

    class YSignaler {

    public:
        YSignaler();
        ~YSignaler();

        void send();
        int wait(int timeout);
        void recv();

        ymq::fd_t get_fd();

        void forked ();

    private:

        static int make_fdpair(ymq::fd_t *r, ymq::fd_t *w);
        ymq::fd_t w_;
        ymq::fd_t r_;

        pid_t pid_;

    private:
        YSignaler(const YSignaler &);
        const YSignaler& operator= (const YSignaler &);
    };
}



#endif //YMQ_YSIGNALER_HPP
