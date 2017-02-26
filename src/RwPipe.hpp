/*
 * This is read-write pipe based on high performant
 * lock free queue.
 * */

#ifndef RW_PIPE_
#define RW_PIPE_

#include <atomic>
#include <assert.h>
#include "RwQueue.hpp"

namespace ymq {

    template <typename T, int N>
    class RwPipe {
        public:

            RwPipe() {
                r_ = &queue_.front();
                c_ = w_ = r_;
            }

            ~RwPipe(){
            }

            void write(const T &t) {
                queue_.back() = t;
                queue_.push();
            }

            bool read(T *val) {
                // item already prefetched, read directly
                if (r_ != &queue_.front()) {
                    *val = queue_.front();
                    queue_.pop();
                    return true;
                }

                bool res = c_.compare_exchange_strong(r_, &queue_.front());
                if (res) {
                    // c_ is queue_front() now
                    return false;
                } else {
                    // r_ is set to c_ now
                    if (r_ == &queue_.front()) {
                        return false;
                    }
                }

                // there is at least one value prefetched
                *val = queue_.front();
                queue_.pop();

                return true;

            }

            bool flush() {
                if (w_ == &queue_.back()) {
                    return false;
                }

                bool res = c_.compare_exchange_strong(w_, &queue_.back());
                if (res) {
                    // c_ is &queue_.back() now
                    w_ = &queue_.back();
                } else {
                    // w_ is set to c_ now
                }

                return res;
            }

        private:
            T *r_;
            T *w_;
            std::atomic<T*> c_;
            RwQueue<T, N> queue_;

        RwPipe(const RwPipe &) = delete;
        const RwPipe & operator=(const RwPipe&) = delete;
    };

}

#endif
