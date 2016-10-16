//
// Created by i059483 on 9/7/15.
//

#ifndef YMQ_YBASESOCKET_HPP
#define YMQ_YBASESOCKET_HPP

//#include "YObject.hpp"
#include "YOwner.hpp"
#include "YPollEvent.hpp"
#include "YArray.hpp"
#include "YPipe.hpp"
#include "YBaseMailbox.hpp"
#include "YCommon.hpp"
#include <string>
#include <map>
//#include "YMailbox.hpp"

namespace ymq{

    class YBaseMailbox;
    class YMsg;

    class YBaseSocket : public YOwner, public YPollEvent, public YArrayItem<>, public i_pipe_events{

    public:

        YBaseSocket(ymq::Context *ctx, uint32_t tid, int sid);
        virtual ~YBaseSocket();

        virtual void in_event() override ;
        virtual void out_event() override ;
        virtual void timer_event(int id) override ;

        virtual void read_activated (ymq::YPipe *pipe);
        virtual void write_activated (ymq::YPipe *pipe);
        virtual void hiccuped (ymq::YPipe *pipe);
        virtual void pipe_terminated (ymq::YPipe *pipe);

        //  Create a socket of a specified type.
        static YBaseSocket *create (int type, ymq::Context *parent,
                                    uint32_t tid, int sid);
        YBaseMailbox *get_mailbox();
        int bind(const char *addr);

        void set_fd(fd_t fd);

        int send (ymq::YMsg *msg, int flags_);
        int recv (ymq::YMsg *msg, int flags_);
        virtual int xrecv (ymq::YMsg *msg);

    protected:
        void process_plug();
        void process_bind();


    private:
        YBaseMailbox *mailbox_;
        fd_t fd_;

        //  Creates new endpoint ID and adds the endpoint to the map.
        void add_endpoint (const char *addr, YOwner *endpoint, YPipe *pipe);

        //  Map of open endpoints.
        typedef std::pair <YOwner *, YPipe*> endpoint_pipe_t;
        typedef std::multimap <std::string, endpoint_pipe_t> endpoints_t;
        endpoints_t endpoints_;

        YBaseSocket(const YBaseSocket& );
        const YBaseSocket& operator= (const YBaseSocket &);


    };
}



#endif //YMQ_YBASESOCKET_HPP
