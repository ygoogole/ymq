#ifndef SESSION_HPP
#define SESSION_HPP

#include <string>
#include "IoObject.hpp"

namespace ymq {

    class IoThread;
    class SocketBase;
    class Engine;

    class Session : public IoObject {

    public:
        Session(IoThread *thread, SocketBase *socket, std::string addr);
        ~Session();
        void setEngine(Engine *e) {
            engine_ = e;
        }

    private:
        SocketBase *socket_;
        std::string addr_;
        Engine *engine_;
    };
}

#endif
