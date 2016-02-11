//
// Created by i059483 on 10/17/15.
//

#ifndef YMQ_YTCPLISTNER_HPP
#define YMQ_YTCPLISTNER_HPP

#include "YOwner.hpp"
#include "YIoObject.hpp"
//#include "YIOThread.hpp"
#include "YOption.hpp"

namespace ymq{

    class YBaseSocket;
    class YIOThread;

    class YTcpListner : public YOwner, public YIoObject{

    public:
        YTcpListner(ymq::YIOThread *thread, ymq::YBaseSocket *socket );
        ~YTcpListner();

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


        YTcpListner(const YTcpListner &);
        const YTcpListner & operator= (const YTcpListner &);
    };
}




#endif //YMQ_YTCPLISTNER_HPP
