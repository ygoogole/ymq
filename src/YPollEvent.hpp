//
// Created by i059483 on 9/20/15.
//

#ifndef YMQ_YPOLLEVENT_HPP
#define YMQ_YPOLLEVENT_HPP

namespace ymq{

    class YPollEvent {

    public:
        virtual ~YPollEvent () {}

        virtual void in_event () = 0;

        virtual void out_event () = 0;

        virtual void timer_event ( int id ) = 0;
    };
}



#endif //YMQ_YPOLLEVENT_HPP
