//
// Created by i059483 on 9/7/15.
//

#include "YBaseSocket.hpp"
#include "YMailbox.hpp"
#include "YReply.hpp"
#include "YTcpListner.hpp"

ymq::YBaseSocket::YBaseSocket(ymq::YContext *ctx, uint32_t tid, int sid)
    : YOwner(ctx, tid){

    mailbox_ = new YMailbox();
}

ymq::YBaseSocket::~YBaseSocket() {


}

void ymq::YBaseSocket::in_event() {

}

void ymq::YBaseSocket::out_event() {

}

void ymq::YBaseSocket::process_plug() {

}

void ymq::YBaseSocket::process_bind() {

}

void ymq::YBaseSocket::timer_event(int id) {

}

void ymq::YBaseSocket::read_activated(ymq::YPipe *pipe) {

}

void ymq::YBaseSocket::write_activated(ymq::YPipe *pipe) {

}

void ymq::YBaseSocket::hiccuped(ymq::YPipe *pipe) {

}

void ymq::YBaseSocket::pipe_terminated(ymq::YPipe *pipe) {

}

ymq::YBaseSocket *ymq::YBaseSocket::create(int type, ymq::YContext *parent, uint32_t tid, int sid) {

    switch (type){

        case YConstPool::YMQ_REP:
            return new (std::nothrow) YReply(parent, tid, sid);


        default:
            return nullptr;
    }

}

ymq::YBaseMailbox *ymq::YBaseSocket::get_mailbox() {
    return mailbox_;
}

int ymq::YBaseSocket::bind(const char *addr) {

    YIOThread *io_thread = choose_io_thread();

    // tcp
    YTcpListner *tcp_listner = new (std::nothrow) YTcpListner(io_thread, this);
    assert(tcp_listner != NULL);

    int rc = tcp_listner->set_address(addr);
    assert(rc == 0);

    add_endpoint(addr, (YOwner* ) tcp_listner, NULL);

}

void ymq::YBaseSocket::set_fd(ymq::fd_t fd) {

    fd_ = fd;
}

void ymq::YBaseSocket::add_endpoint(const char *addr, ymq::YOwner *endpoint, ymq::YPipe *pipe) {

    launch_child(endpoint);
    endpoints_.insert(endpoints_t::value_type (std::string (addr), endpoint_pipe_t (endpoint, pipe)));
}

int ymq::YBaseSocket::send(ymq::YMsg *msg, int flags_) {
    return 0;
}

int ymq::YBaseSocket::recv(ymq::YMsg *msg, int flags_) {

    int rc = xrecv(msg);
    return 0;
}
