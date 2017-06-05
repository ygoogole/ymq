#ifndef YMQ_CONTEXT_HPP
#define YMQ_CONTEXT_HPP

#include "SocketBase.hpp"
#include "Command.hpp"
#include <vector>
#include <stdint.h>
#include <memory>

namespace ymq{

    class YBaseSocket;
    class IoThread;
    class SocketBase;

    class Context {

    public:

        Context(int thread_num, int max_thread = kMaxThreadNumber);
        ~Context();

        SocketBase* create_socket(unsigned type);
        void set_max_thread ( int max_thread );
        int get_max_thread ();

        void send_command (uint32_t tid, Command &cmd);
        IoThread* getIoThread();

        int thread_count_;
        int max_thread_;
        int slot_count_;

        Mailbox **slots_;

        //Context ( int number_thread, int max_thread = ymq::YConstPool::kMaxThreadNumber );

        IoThread *choose_io_thread();
        std::shared_ptr<SocketBase> socket_;

    private:

        std::vector<std::shared_ptr<IoThread>> io_threads_;
        std::vector<uint32_t> empty_slots_;

        //YMailbox mailbox_slots[ymq::YConstPool::kMaxThreadNumber];

        Context (const Context &) = delete;
        const Context& operator= (const Context&) = delete;
    };
}

#endif //YMQ_CONTEXT_HPP
