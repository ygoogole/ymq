//
// Created by i059483 on 10/26/15.
//

#ifndef YMQ_YOPTION_HPP
#define YMQ_YOPTION_HPP

namespace ymq{

    struct YOption {

        //YOption();

        //  TCP keep-alive settings.
        //  Defaults to -1 = do not change socket options
        int tcp_keepalive_;
        int tcp_keepalive_cnt_;
        int tcp_keepalive_idle_;
        int tcp_keepalive_intvl_;

        //  Maximum interval in milliseconds beyond which TCP will timeout
        //  retransmitted packets.
        //  Default 0 (unused)
        int tcp_retransmit_timeout_;
    };

}



#endif //YMQ_YOPTION_HPP
