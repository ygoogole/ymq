//
// Created by i059483 on 10/26/15.
//

#ifndef YMQ_YROUTER_HPP
#define YMQ_YROUTER_HPP

#include "YBaseSocket.hpp"

namespace ymq{

    class YMsg;

    class YRouter : public YBaseSocket{

    public:
        YRouter(ymq::Context *parent, uint32_t tid, int sid);

        virtual int xsend (ymq::YMsg *msg);
        virtual int xrecv (ymq::YMsg *msg);

    private:
        YRouter(const YRouter& );
        const YRouter& operator= (const YRouter& );
    };
}



#endif //YMQ_YROUTER_HPP
