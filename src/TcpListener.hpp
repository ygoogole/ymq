#ifndef YMQ_TCPLISTNER_HPP
#define YMQ_TCPLISTNER_HPP

#include <string>
#include "IoObject.hpp"
#include "IoThread.hpp"

namespace ymq{

    class SocketBase;
    class IoThread;

    class TcpListener : public IoObject {

    public:
        TcpListener(IoThread *thread, SocketBase *socket );
        ~TcpListener();

        int startListening(const std::string &addr);

    private:

        SocketBase *socket_;
        fd_t fd_;
        handle_t handle_;

        std::string ip_;
        std::string port_;
        std::string addr_;

        void inEvent() override;
        fd_t accept();


        TcpListener(const TcpListener &) = delete;
        const TcpListener & operator= (const TcpListener &) = delete;
    };
}




#endif //YMQ_TCPLISTNER_HPP
