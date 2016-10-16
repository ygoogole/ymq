//
// Created by i059483 on 10/17/15.
//

#include <sys/socket.h>
#include <netinet/in.h>
#include "TcpListener.hpp"
#include "tcp.hpp"

ymq::TcpListener::TcpListener(ymq::IoThread *thread, ymq::YBaseSocket *socket)
    :YOwner(thread)
    ,socket_(socket)
    ,fd_(-1){

    port_ = "8888";
}

ymq::TcpListener::~TcpListener() {

    fd_ = -1;
}

void ymq::TcpListener::in_event() {

    fd_t fd = accept();

    if (fd == -1)
        return;

    tune_tcp_socket (fd);
    tune_tcp_keepalives (fd, options_.tcp_keepalive_, options_.tcp_keepalive_cnt_, options_.tcp_keepalive_idle_, options_.tcp_keepalive_intvl_);
    tune_tcp_retransmit_timeout (fd, options_.tcp_retransmit_timeout_);

    socket_->set_fd(fd);

    //create engine

    //create session
}

ymq::fd_t ymq::TcpListener::accept() {
    return 0;
}

void ymq::TcpListener::process_plug() {

    handle_ = add_fd(fd_);
    set_pollin(handle_);
}

int ymq::TcpListener::set_address(const char *addr) {

    sockaddr_in saddr;
    saddr.sin_family = AF_INET;
    fd_t s = socket(saddr.sin_family, SOCK_STREAM, IPPROTO_TCP);

    if (s == -1)
        return -1;

    saddr.sin_addr.s_addr = INADDR_ANY;
    saddr.sin_port = htons(atoi(port_));


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

    return 0;
}
