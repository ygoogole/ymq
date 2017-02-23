#ifndef RW_QUEUE_
#define RW_QUEUE_

#include <assert.h>

namespace ymq {

    template<typename T, unsigned N>
    class RwQueue {

        public:
            RwQueue()
                : idx_begin_()
                , idx_end_() {

                head_ = new chunk;
                assert(head_);
                tail_ = head_;

            }

            ~RwQueue() {

                do {
                    chunk *t = head_->next;
                    delete head_;
                    head_ = t;
                } while (head_);
            }

            void push(const T& t) {
                back() = t;
                if (++idx_end_ == N) {
                    // add a new chunk
                    tail_->next = new chunk;
                    assert(tail_->next);
                    tail_ = tail_->next;
                    idx_end_ = 0;
                }
            }

            void pop() {
                if (++idx_begin_ == N) {
                    //this chunk could be freed (or set to spared)
                    chunk *tmp = head_;
                    head_ = head_->next;
                    delete tmp;
                    idx_begin_ = 0;
                }
            }

            T& front() {
                return head_->data[idx_begin_];
            }

            T& back() {
                return tail_->data[idx_end_];
            }

        private:

            struct chunk {
                chunk()
                    : next(nullptr)
                {}
                T data[N];
                chunk *next;
            };

            unsigned idx_begin_;
            unsigned idx_end_;
            chunk *head_;
            chunk *tail_;

            RwQueue(const RwQueue &) = delete;
            const RwQueue & operator=(const RwQueue &) = delete;
    };
}

#endif
