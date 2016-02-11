//
// Created by i059483 on 9/20/15.
//

#include "YMailbox.hpp"

ymq::YMailbox::YMailbox() {

    bool ok = cpipe_.read(NULL);
    assert (ok == false);
    active_ = false;
}

ymq::YMailbox::~YMailbox() {

    sync_.lock();
    sync_.unlock();
}

void ymq::YMailbox::send(const ymq::YCommand &cmd){

    sync_.lock();
    cpipe_.write(cmd, false);
    bool ok = cpipe_.flush();
    if (ok){
        signaler_.send();
    }

}

int ymq::YMailbox::recv(ymq::YCommand *cmd, int timeout) {

    if (active_){
        if (cpipe_.read (cmd))
            return 0;

        // no more commands to read
        active_ = false;
    }

    int rc = signaler_.wait(timeout);
    if (rc == -1){
        return -1;
    }

    //recv signal
    signaler_.recv();

    active_ = true;
    bool ok = cpipe_.read(cmd);
    assert (ok);
    return 0;

}

ymq::fd_t ymq::YMailbox::get_fd() {
    return signaler_.get_fd();
}
