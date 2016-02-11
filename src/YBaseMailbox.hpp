//
// Created by i059483 on 9/20/15.
//

#ifndef YMQ_YBASEMAILBOX_HPP
#define YMQ_YBASEMAILBOX_HPP

#include "YCommand.hpp"

namespace ymq{

    class YBaseMailbox {

    public:
        virtual ~YBaseMailbox(){}

        virtual void send(const ymq::YCommand &cmd) = 0;

        virtual int recv(ymq::YCommand *cmd, int timeout) = 0;

    };
}



#endif //YMQ_YBASEMAILBOX_HPP
