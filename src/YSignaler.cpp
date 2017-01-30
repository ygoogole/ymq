#include "YSignaler.hpp"
#include "YIPCtrl.hpp"
#include <sys/eventfd.h>
#include <sys/poll.h>
#include <sys/errno.h>

ymq::YSignaler::YSignaler() {

    int ret = make_fdpair(&r_, &w_);
    if(ret == 0){
        ymq::unblock_fd(r_);
        ymq::unblock_fd(w_);
    }

    pid_ = getpid();// get id of process which creates current context
}

ymq::YSignaler::~YSignaler() {

    // close fd
    close(r_);
}

void ymq::YSignaler::send() {

    if ( pid_ != getpid() ){
        return ;
    }

    const uint64_t kInc = 1;

    //send signal by writing to fd
    //write(2) adds to kernel maintained  counter
    ssize_t sz = write(w_, &kInc, sizeof kInc);
}

int ymq::YSignaler::wait(int timeout) {

    struct pollfd pfd;
    pfd.fd = r_;
    pfd.events = POLLIN;

    //block until timeout seconds elapse...
    int rc = poll(&pfd, 1, timeout);
    if(rc < 0){
        return -1;
    }else if(rc == 0) {
            errno = EAGAIN;
            return -1;
    } else if(pid_ != getpid()){
        errno = EINTR;
        return -1;
    }

    return 0;
}

void ymq::YSignaler::recv() {

    uint64_t dummy;
    ssize_t sz = read(r_, &dummy, sizeof dummy);

    if(dummy > 1){
        //catch next signals by mistake, send it back again
        const uint64_t kInc = dummy - 1;
        write(w_, &kInc, sizeof kInc);
    }
}

ymq::fd_t ymq::YSignaler::get_fd() {
    return r_;
}

void ymq::YSignaler::forked() {

}

int ymq::YSignaler::make_fdpair(ymq::fd_t *r, ymq::fd_t *w) {

    ymq::fd_t fd = eventfd(0, 0);

    if( fd == -1){
        return -1;
    } else{
        *r = *w = fd;
        return 0;
    }
}
