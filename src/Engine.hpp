#ifndef ENGINE_HPP
#define ENGINE_HPP

#include <string>
#include "IoObject.hpp"

namespace ymq {

    class IoThread;
    class SocketBase;
    class Session;

    class Engine : public IoObject {

    public:
        Engine(IoThread *thread, SocketBase *socket, std::string addr);
        ~Engine() {}
        void setSession(Session *s) {
            session_ = s;
        }

        void plug(fd_t fd);

    protected:
        // PollEvent interface implementation.
        void inEvent() override;
        void outEvent() override;

    private:
        SocketBase *socket_;
        std::string addr_;
        Session *session_;
    };
}

#endif
