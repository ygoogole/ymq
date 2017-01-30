#include <fcntl.h>
#include "FdCtrl.hpp"

int ymq::unblockFd(fd_t fd) {

    int flags = fcntl(fd, F_GETFL, 0);
    if( flags == -1)
        flags = 0;

    return fcntl(fd, F_SETFL, flags | O_NONBLOCK);

}
