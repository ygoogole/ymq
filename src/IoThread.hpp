#ifndef YMQ_IOTHREAD_HPP
#define YMQ_IOTHREAD_HPP

#include "YObject.hpp"
#include "Mailbox.hpp"
#include "Epoller.hpp"
#include "EpollerBase.hpp"

namespace ymq{

    class Context;
    class IoThread : public EpollerBase {

    public:

        IoThread(Context *ctx, uint32_t idx);

        virtual ~IoThread();

        Epoller* getPoller();

        const Mailbox & getMailbox();
        void start();
        void stop();
        void inEvent() override;
        void outEvent();
/*
        void timer_event( int id );
        void process_plug();
        void process_bind();
        void process_stop();
*/
    private:

        Mailbox mailbox_;
        Epoller::EpollHandle mailbox_handle_;
        Epoller *epoller_;
        Context *ctx_;

        IoThread(const IoThread &) = delete;
        const IoThread& operator= (const IoThread&) = delete;
    };
}

#endif //YMQ_IOTHREAD_HPP
