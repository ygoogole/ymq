//
// Created by i059483 on 9/7/15.
//

#include <stddef.h>
#include <new>
#include <assert.h>
#include "Context.hpp"
#include "IoThread.hpp"
#include "YBaseSocket.hpp"

ymq::Context::Context( int thread_count, int max_thread )
    :thread_count_(thread_count),
    max_thread_(max_thread){


}

ymq::Context::~Context() {

}

void ymq::Context::set_max_thread (int max_thread) {
    max_thread_ = max_thread;
}

int ymq::Context::get_max_thread () {
    return max_thread_;
}

ymq::YBaseSocket *ymq::Context::create_socket(ymq::YConstPool::SocketType type) {

    // create socket, io thread and start polling

    // tid 0, 1 reserved, io_thread starts from 2

    slot_sync_.lock();

    slot_count_ = thread_count_ + max_thread_ + 2;
    slots_ = (YBaseMailbox **) malloc (sizeof (YBaseMailbox *) * slot_count_);
    assert (slots_ != NULL);

    for (int i = 2; i < thread_count_ + 2; i++){

        IoThread* io_thread = new (std::nothrow) IoThread(this, i);
        assert(io_thread != nullptr);

        io_threads_.push_back(io_thread);
        slots_[i] = io_thread->get_mailbox();
        io_thread->start();

    }

    for (int i = slot_count_ -1; i >= thread_count_ + 2; i--){
        empty_slots_.push_back(i);
        slots_[i] = NULL;
    }

    uint32_t slot = empty_slots_.back();
    empty_slots_.pop_back();

    // get unique id for socket
    int sid = (int)max_sock_counter_.add(1) + 1;

    YBaseSocket *socket = YBaseSocket::create(type, this, slot, sid);
    assert(socket != NULL);

    sockets_.push_back(socket);
    slots_[slot] = socket->get_mailbox();

    slot_sync_.unlock();

    return socket;
}

void ymq::Context::start_thread(ymq::YThread &thread, ymq::thread_fn *tfn, void *arg) const{

    thread.start(tfn, arg);
    //set thread parameter like priority, scheduling policy
}

void ymq::Context::send_command(uint32_t tid, const ymq::YCommand &cmd) {

    slots_[tid]->send (cmd);
}

ymq::YAtomicCounter ymq::Context::max_sock_counter_;

ymq::IoThread *ymq::Context::choose_io_thread() {
    return io_threads_[0];
}
