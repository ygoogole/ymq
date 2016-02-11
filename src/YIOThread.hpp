//
// Created by i059483 on 9/20/15.
//

#ifndef YMQ_YIOTHREAD_HPP
#define YMQ_YIOTHREAD_HPP

#include "YObject.hpp"
//#include "YPollEvent.hpp"
#include "YMailbox.hpp"
#include "YEPoller.hpp"

namespace ymq{

    class YIOThread : public YObject, public YPollEvent {

    public:

        YIOThread( ymq::YContext *ctx, uint32_t tid );

        void in_event();
        void out_event();
        void timer_event( int id );

        ~YIOThread();

        void start();
        void stop();
        YMailbox* get_mailbox();
        ymq::YEPoller* get_poller();

    protected:

        void process_plug();
        void process_bind();
        void process_stop();

    private:

        ymq::YMailbox mailbox_;
        ymq::YEPoller::handle_t mailbox_handle_;
        ymq::YEPoller *epoller_;

        YIOThread(const YIOThread &);
        const YIOThread& operator= (const YIOThread&);
    };
}



#endif //YMQ_YIOTHREAD_HPP
