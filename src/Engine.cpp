#include "Engine.hpp"
#include <iostream>

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

}

void Engine::outEvent() {
#ifndef DISABLE_LOG
//    std::cout << "engine outEvent" << std::endl;
#endif
}

} // ns: ymq
