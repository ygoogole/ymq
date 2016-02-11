//
// Created by i059483 on 10/4/15.
//

#ifndef YMQ_YTHREAD_HPP
#define YMQ_YTHREAD_HPP

#include <bits/pthreadtypes.h>

namespace ymq{

    typedef void (thread_fn) (void*);

    class YThread {

    public:
        inline YThread(){}

        void start(thread_fn *tfn, void *arg);
        void stop();

        thread_fn *tfn_;
        void *arg_;
        pthread_t td_;

    private:
        YThread(const YThread&);
        const YThread& operator= (const YThread&);
    };

}


#endif //YMQ_YTHREAD_HPP
