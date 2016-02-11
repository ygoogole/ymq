//
// Created by i059483 on 10/4/15.
//

#include <pthread.h>
#include <assert.h>
#include "YThread.hpp"
#include <signal.h>


extern "C" {

    static void *thread_routine (void *arg){

        //  Following code will guarantee more predictable latencies as it'll
        //  disallow any signal handling in the I/O thread.
        sigset_t signal_set;
        int rc = sigfillset (&signal_set);
        assert (rc == 0);
        rc = pthread_sigmask (SIG_BLOCK, &signal_set, NULL);
        assert (rc == 0);

        ymq::YThread *self = (ymq::YThread*) arg;
        self->tfn_ (self->arg_);
        return NULL;
    }
}

void ymq::YThread::start(ymq::thread_fn *tfn, void *arg) {

    tfn_ = tfn;
    arg_ = arg;

    int rc = pthread_create(&td_, NULL, thread_routine, this);
    assert( rc == 0);
}

void ymq::YThread::stop() {

    int rc = pthread_join(td_, NULL);
    assert(rc == 0);
}
