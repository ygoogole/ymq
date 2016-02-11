//
// Created by i059483 on 9/20/15.
//

#ifndef YMQ_YCONSTPOOL_HPP
#define YMQ_YCONSTPOOL_HPP


namespace ymq{

    struct YConstPool{
        static const int kMaxThreadNumber = 1023;
        static const int kMaxIoEvent = 256;
        static const int kRetired_fd = -1;
        static const int kCmdPipeGranularity = 16;

        typedef enum sock_type{

            YMQ_REP = 0,
            YMQ_REQ = 1,

        }SocketType;

        //typedef enum SocketType_t SocketType;
    };

}

#endif //YMQ_YCONSTPOOL_HPP


