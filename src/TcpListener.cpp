#ifndef LOG_DISABLE
#include <iostream>
#endif

#include <sys/socket.h>
#include <netinet/in.h>
#include <string.h>
#include "TcpListener.hpp"
#include "tcp.hpp"
#include "Session.hpp"
#include "Engine.hpp"

using namespace ymq;

namespace ymq {

TcpListener::TcpListener(IoThread *thread, SocketBase *socket)
    : IoObject(thread)
    , Object(thread->get_context(), thread->get_tid())
    , socket_(socket)
    , fd_(-1) {

    port_ = "8888";
}

TcpListener::~TcpListener() {

    fd_ = -1;
}

void TcpListener::inEvent() {
#ifndef LOG_DISABLE
    std::cout << "tcp listener in event " << std::endl;
#endif

    fd_t fd = accept();

    if (fd == -1)
        return;

    tune_tcp_socket (fd);
    tune_tcp_keepalives (fd, -1, -1, -1, -1); 
    //tune_tcp_keepalives (fd, options_.tcp_keepalive_, options_.tcp_keepalive_cnt_, options_.tcp_keepalive_idle_, options_.tcp_keepalive_intvl_);
    //tune_tcp_retransmit_timeout (fd, options_.tcp_retransmit_timeout_);

    //create engine
    Engine *engine = new (std::nothrow) Engine(io_thread_, socket_, 
            addr_);
    assert(engine);

    //create session
    Session *sess = new (std::nothrow) Session(io_thread_, socket_, 
            addr_);
    assert(sess);

    //set ref
    engine->setSession(sess);
    sess->setEngine(engine);

    // setup queue between session and engine

    //poll engine on accepted socket
    engine->plug(fd);
}

fd_t TcpListener::accept() {

#ifndef LOG_DISABLE
    std::cout << "tcp listener accepted " << std::endl;
#endif

    struct sockaddr_storage ss;
    socklen_t len = sizeof(ss);
    memset(&ss, 0, len);

    fd_t sock = ::accept4 (fd_, (struct sockaddr *) &ss, &len, SOCK_CLOEXEC);

    return sock;
}

/*
void TcpListener::process_plug() {

    handle_ = add_fd(fd_);
    set_pollin(handle_);
}
*/
int TcpListener::startListening(const std::string &addr) {

    size_t pos = addr.find(':');
    if (pos == std::string::npos) {
        return -1; 
    }

    ip_ = addr.substr(0, pos);
    port_ = addr.substr(pos+1);
    addr_ = addr;

    sockaddr_in saddr;
    saddr.sin_family = AF_INET;
    fd_t s = socket(saddr.sin_family, SOCK_STREAM, IPPROTO_TCP);

    if (s == -1)
        return -1;

    saddr.sin_addr.s_addr = INADDR_ANY;
    saddr.sin_port = htons(atoi(port_.c_str()));

    //reuse address
    int flag = 1;
    int rc = setsockopt(s, SOL_SOCKET, SO_REUSEADDR, &flag, sizeof (int));

    if (rc == -1)
        return -1;

    rc = bind(s, (struct sockaddr *)&saddr, sizeof (saddr));
    if (rc == -1)
        return -1;

    if (listen(s, 64) == -1) {
        close(s);
        return -1;
    }

    fd_ = s;

    handle_ = addFd(fd_);
    setPollin(handle_);

    return 0;
}

} // ns: ymq
