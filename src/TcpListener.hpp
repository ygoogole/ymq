//
// Created by i059483 on 10/17/15.
//

#ifndef YMQ_YTCPLISTNER_HPP
#define YMQ_YTCPLISTNER_HPP

#include "YOwner.hpp"
#include "YIoObject.hpp"
//#include "IoThread.hpp"
#include "YOption.hpp"

namespace ymq{

    class YBaseSocket;
    class IoThread;

    class TcpListener : public YOwner, public YIoObject{

    public:
        TcpListener(ymq::IoThread *thread, ymq::YBaseSocket *socket );
        ~TcpListener();

        int set_address(const char *addr);

    private:

        YBaseSocket *socket_;
        fd_t fd_;
        handle_t handle_;
        ymq::YOption options_;

        const char *ip_;
        const char *port_;

        void process_plug();
        void in_event();
        fd_t accept();


        TcpListener(const TcpListener &);
        const TcpListener & operator= (const TcpListener &);
    };
}




#endif //YMQ_YTCPLISTNER_HPP
