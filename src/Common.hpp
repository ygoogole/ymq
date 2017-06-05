#ifndef YMQ_COMMON_HPP
#define YMQ_COMMON_HPP

#include <assert.h>
#include <errno.h>

namespace ymq{

    class Common {
    };

    typedef int fd_t;
    const static unsigned kMaxIoEvent = 256;
    const static unsigned kMaxThreadNumber = 1023;
    const static unsigned kMsgLength = 1024;
}



#endif //YMQ_COMMON_HPP
