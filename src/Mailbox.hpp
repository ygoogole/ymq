#ifndef YMQ_MAILBOX_HPP
#define YMQ_MAILBOX_HPP

#include "Common.hpp"
#include "Signaler.hpp"
#include <memory>

namespace ymq{

    class Mailbox {

    public:
        Mailbox();
        ~Mailbox();
        fd_t getFd();

/*
        void send(const ymq::YCommand &cmd);
        int recv(ymq::YCommand *cmd, int timeout);
*/

    private:
/*
        //  The pipe to store actual commands.
        typedef YyPipe <YCommand, ymq::YConstPool::kCmdPipeGranularity> ypipe_t;
        ypipe_t cpipe_;

        YMutex sync_;

        bool active_;
*/
        Signaler signaler_;

        Mailbox(const Mailbox&) = delete;
        const Mailbox& operator=(const Mailbox&) = delete;
    };
}



#endif //YMQ_MAILBOX_HPP
