#include "SocketBase.hpp"
#include "Context.hpp"

using namespace ymq;

namespace ymq {

SocketBase::SocketBase(Context *ctx, unsigned type)
    : ctx_(ctx) {
}

int SocketBase::bind(std::string addr) {
/*
    std::shared_ptr<ymq::TcpListener> tcp_listener;
    tcp_listener.reset(new (std::nothrow) TcpListener(ctx_->getIoThread(), this));
*/
    auto tcp_listener = std::make_shared<TcpListener>(ctx_->getIoThread(), this);
    /*
    auto pair = std::make_pair<std::string, std::shared_ptr<TcpListener> >(addr, tcp_listener);

    endpoints_.insert(pair);
*/
    int res = tcp_listener->startListening(addr);

    endpoints_[addr] = tcp_listener;

    return res;
}

int SocketBase::accept() {

    return 0;
}

void SocketBase::inEvent() {
}

void SocketBase::outEvent() {
}

} // ns: ymq
