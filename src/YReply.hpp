//
// Created by i059483 on 10/26/15.
//

#ifndef YMQ_YREPLY_HPP
#define YMQ_YREPLY_HPP

#include "YRouter.hpp"

namespace ymq{

    class YReply : public YRouter{

    public:
        YReply(ymq::Context *parent, uint32_t tid, int sid);

        virtual int xsend (ymq::YMsg *msg);
        virtual int xrecv (ymq::YMsg *msg);
    };

}


#endif //YMQ_YREPLY_HPP
