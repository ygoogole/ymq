#include <sys/eventfd.h>
#include <sys/poll.h>
#include "Signaler.hpp"
#include "FdCtrl.hpp"

using namespace ymq;

Signaler::Signaler() {
    int ret = makeEventPair(&r_, &w_);
    if (ret == 0) {
        unblockFd(r_);
        unblockFd(w_);
    }
}

Signaler::~Signaler() {
    close(r_);
}

fd_t Signaler::getFd() const {
    return r_;
}

void Signaler::send() {

    const uint64_t inc = 1;
    ssize_t sz = write(w_, &inc, sizeof inc);
    assert(sz == sizeof inc);
}

void Signaler::recv() {

    uint64_t dummy = 0;
    ssize_t sz = read(r_, &dummy, sizeof dummy);
    assert(sz == sizeof dummy);

    if (dummy > 1) {
        const uint64_t inc = dummy - 1;
        ssize_t sz2 = write(w_, &inc, sizeof inc);
        assert(sz2 == sizeof inc);
    }

    assert(dummy == 1);
}

int Signaler::wait(int timeout) {

    struct pollfd pfd;
    pfd.fd = r_;
    pfd.events = POLLIN;

    int rc = poll(&pfd, 1, timeout);
    if (rc < 0) {
        assert(errno == EINTR);
        return -1;
    }

    assert(rc == 1);
    return 0;
}

int Signaler::makeEventPair(fd_t *r, fd_t *w) {

    int flags = 0;

    // avoid abnormal behavior when exec() called
    // old socks are closed and won't block tcp ports
    // and to avoid leaks.
    flags |= EFD_CLOEXEC;

    fd_t fd = eventfd(0, flags);
    if (fd == -1) {
        *r = *w = -1;
        return -1;
    } else {
        *r = *w = fd;
        return 0;
    }

}
