#include "Session.hpp"

namespace ymq {

Session::Session(IoThread *thread, SocketBase *socket, std::string addr)
    : IoObject(thread)
    , socket_(socket)
    , addr_(addr)
    , engine_(nullptr) {

}

Session::~Session() {

    //terminate engine
    //engine_->terminate();
}

} // ns: ymq
