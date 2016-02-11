//
// Created by i059483 on 8/29/15.
//

#ifndef YMQ_YATOMICPTR_HPP
#define YMQ_YATOMICPTR_HPP

namespace ymq {


    template<typename T> class YAtomicPtr {

    public:

        YAtomicPtr(){

            ptr_ = NULL;
        }

        ~YAtomicPtr(){
        }

        inline void set(T* ptr){

            ptr_ = ptr;
        }

        T* xchg(T* value){
            T *old;
            __asm__ volatile (
            "lock; xchg %0, %2"
            : "=r" (old), "=m" (ptr_)
            : "m" (ptr_), "0" (value));
            return old;
        }

        //  Perform atomic 'compare and swap' operation on the pointer.
        //  The pointer is compared to 'cmp' argument and if they are
        //  equal, its value is set to 'val'. Old value of the pointer
        //  is returned.
        T* cas(T* cmp, T* val){
            T *old;
            __asm__ volatile (
            "lock; cmpxchg %2, %3"
            : "=a" (old), "=m" (ptr_)
            : "r" (val), "m" (ptr_), "0" (cmp)
            : "cc");
            return old;
        }

    private:
        YAtomicPtr(const YAtomicPtr &);

        const YAtomicPtr &operator=(const YAtomicPtr &);

        volatile T* ptr_;
    };

}
#endif //YMQ_YATOMICPTR_HPP
