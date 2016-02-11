//
// Created by i059483 on 9/21/15.
//

#ifndef YMQ_YBASEPOLLER_HPP
#define YMQ_YBASEPOLLER_HPP

namespace ymq{

    class YBasePoller {

    public:
        YBasePoller();
        virtual ~YBasePoller();

    private:
        YBasePoller(const YBasePoller &);
        const YBasePoller &operator=(const YBasePoller &);
    };
}



#endif //YMQ_YBASEPOLLER_HPP
