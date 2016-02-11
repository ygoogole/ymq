//
// Created by i059483 on 9/20/15.
//

#ifndef YMQ_YMAILBOX_HPP
#define YMQ_YMAILBOX_HPP

#include "YBaseMailbox.hpp"
#include "YCommon.hpp"
#include "YSignaler.hpp"
#include "YyPipe.hpp"
#include "YConstPool.hpp"
#include "YMutex.hpp"

namespace ymq{

    class YMailbox : public  YBaseMailbox{

    public:
        YMailbox();
        ~YMailbox();

        ymq::fd_t get_fd();


        void send(const ymq::YCommand &cmd) override ;
        int recv(ymq::YCommand *cmd, int timeout) override ;


    private:

        //  The pipe to store actual commands.
        typedef YyPipe <YCommand, ymq::YConstPool::kCmdPipeGranularity> ypipe_t;
        ypipe_t cpipe_;

        YSignaler signaler_;
        YMutex sync_;

        bool active_;

        YMailbox(const YMailbox&);
        const YMailbox& operator=(const YMailbox&);
    };
}



#endif //YMQ_YMAILBOX_HPP
