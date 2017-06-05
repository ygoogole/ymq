#include "Engine.hpp"
#include "tcp.hpp"
#include "Msg.h"
#include <iostream>
#include "Session.hpp"

namespace ymq {

Engine::Engine(IoThread *thread, SocketBase *socket, std::string addr)
    : IoObject(thread)
    , socket_(socket)
    , addr_(addr)
    , session_(nullptr) {

}

void Engine::plug(fd_t fd) {

    handle_t handle = addFd(fd);
    setPollin(handle);
    setPollout(handle);
}

void Engine::inEvent() {
#ifndef DISABLE_LOG
    std::cout << "engine inEvent" << std::endl;
#endif

    char data[kMsgLength];

    int rc = tcp_read(fd_, data, kMsgLength);
    if (rc > 0) {
        Msg msg;
        msg.Init();
        msg.setData(data, rc);
        session_->flush(msg);
    }

}

void Engine::outEvent() {
#ifndef DISABLE_LOG
//    std::cout << "engine outEvent" << std::endl;
#endif
}

} // ns: ymq
