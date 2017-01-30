#ifndef SIGNALER_HPP
#define SIGNALER_HPP

#include <unistd.h>
#include "Common.hpp"

namespace ymq {

    class Signaler {

    public:
        Signaler();
        ~Signaler();

        fd_t getFd() const;
        void send();
        void recv();
        int wait(int timeout);

    private:
        fd_t r_;
        fd_t w_;
        int makeEventPair(fd_t *r, fd_t *w);

        Signaler(const Signaler &) = delete;
        const Signaler& operator= (const Signaler &) = delete;
    };
}

#endif
