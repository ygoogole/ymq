#ifndef YMQ_MAILBOX_HPP
#define YMQ_MAILBOX_HPP

#include "Common.hpp"
#include "Signaler.hpp"
#include "Command.hpp"
#include "RwPipe.hpp"
#include "YConstPool.hpp"
#include <memory>

namespace ymq{

    class Mailbox {

    public:
        Mailbox();
        ~Mailbox();
        fd_t getFd();

        void send(ymq::Command &cmd);
        int recv(ymq::Command *cmd, int timeout);

    private:
/*
        //  The pipe to store actual commands.
        typedef YyPipe <YCommand, ymq::YConstPool::kCmdPipeGranularity> ypipe_t;
        ypipe_t cpipe_;

        YMutex sync_;

*/

        RwPipe<Command, YConstPool::kCmdPipeGranularity> pipe_;
        Signaler signaler_;
        bool active_;

        Mailbox(const Mailbox&) = delete;
        const Mailbox& operator=(const Mailbox&) = delete;
    };
}



#endif //YMQ_MAILBOX_HPP
