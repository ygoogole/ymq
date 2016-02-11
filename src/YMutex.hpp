//
// Created by i059483 on 10/5/15.
//

#ifndef YMQ_YMUTEX_HPP
#define YMQ_YMUTEX_HPP

#include <pthread.h>
#include <assert.h>
#include <sys/errno.h>

namespace ymq{

    class YMutex {

    public:

        inline YMutex(){

            int rc = pthread_mutexattr_init(&attr_);
            assert( rc == 0 );
            rc = pthread_mutexattr_settype(&attr_, PTHREAD_MUTEX_RECURSIVE);
            assert( rc == 0 );
            rc = pthread_mutex_init (&mutex_, &attr_);
            assert( rc == 0 );
        }

        inline ~YMutex ()
        {
            int rc = pthread_mutex_destroy (&mutex_);
            assert( rc == 0 );

            rc = pthread_mutexattr_destroy (&attr_);
            assert( rc == 0 );
        }

        inline void lock ()
        {
            int rc = pthread_mutex_lock (&mutex_);
            assert( rc == 0 );
        }

        inline bool try_lock ()
        {
            int rc = pthread_mutex_trylock (&mutex_);
            if (rc == EBUSY)
                return false;

            assert( rc == 0 );
            return true;
        }

        inline void unlock ()
        {
            int rc = pthread_mutex_unlock (&mutex_);
            assert( rc == 0 );
        }

        inline pthread_mutex_t* get_mutex()
        {
            return &mutex_;
        }
    private:

        pthread_mutex_t mutex_;
        pthread_mutexattr_t attr_;

        YMutex(const YMutex&);
        const YMutex & operator = (const YMutex& );
    };
}



#endif //YMQ_YMUTEX_HPP
