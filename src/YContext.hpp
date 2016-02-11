//
// Created by i059483 on 9/7/15.
//

#ifndef YMQ_YCONTEXT_HPP
#define YMQ_YCONTEXT_HPP

#include "YConstPool.hpp"
#include "YMailbox.hpp"
#include "YThread.hpp"
#include "YAtomicCounter.hpp"
#include "YArray.hpp"
#include "YBaseSocket.hpp"
#include <vector>
#include <stdint.h>

namespace ymq{

    class YBaseSocket;
    class YIOThread;

    class YContext {

    public:

        YContext(int thread_num, int max_thread = ymq::YConstPool::kMaxThreadNumber);
        ~YContext();

        YBaseSocket* create_socket( ymq::YConstPool::SocketType type);
        void start_thread(YThread &thread, thread_fn *tfn, void* arg) const;
        void set_max_thread ( int max_thread );
        int get_max_thread ();

        void send_command (uint32_t tid, const YCommand &cmd);

        int thread_count_;
        int max_thread_;
        int slot_count_;

        YBaseMailbox **slots_;

        //YContext ( int number_thread, int max_thread = ymq::YConstPool::kMaxThreadNumber );

        YIOThread *choose_io_thread();

    private:

        static YAtomicCounter max_sock_counter_;

        std::vector<YIOThread*> io_threads_;
        std::vector<uint32_t> empty_slots_;
        YArray<YBaseSocket> sockets_;

        YMutex slot_sync_;
        //YMailbox mailbox_slots[ymq::YConstPool::kMaxThreadNumber];

        YContext (const YContext &);
        const YContext& operator= (const YContext&);
    };
}



#endif //YMQ_YCONTEXT_HPP
