//
// Created by i059483 on 10/4/15.
//

#include <fcntl.h>
#include "YIPCtrl.hpp"

int ::ymq::unblock_fd(ymq::fd_t fd) {

    int flags = fcntl(fd, F_GETFL, 0);
    if( flags == -1)
        flags = 0;

    return fcntl(fd, F_SETFL, flags | O_NONBLOCK);

}
