#ifndef SESSION_HPP
#define SESSION_HPP

#include <string>
#include "IoObject.hpp"
#include "Msg.h"
#include "RwPipe.hpp"
#include "YConstPool.hpp"

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
        void flush(Msg msg);

    private:
        SocketBase *socket_;
        std::string addr_;
        Engine *engine_;
        RwPipe<Msg, YConstPool::kCmdPipeGranularity> *pipe_;
    };
}

#endif
