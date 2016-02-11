//
// Created by i059483 on 10/12/15.
//

#ifndef YMQ_YATOMICCOUNTER_HPP
#define YMQ_YATOMICCOUNTER_HPP

#include <stdint.h>

namespace ymq{

    class YAtomicCounter {

    public:
        inline YAtomicCounter(uint32_t value = 0)
            :value_(value){}

        inline ~YAtomicCounter(){}

        inline void set(uint32_t value){
            value_ = value;
        }

        inline uint32_t get(){
            return value_;
        }

        inline uint32_t add(uint32_t inc){

            uint32_t old;

            __asm__ volatile (
            "lock; xadd %0, %1 \n\t"
            : "=r" (old), "=m" (value_)
            : "0" (inc), "m" (value_)
            : "cc", "memory");

            return old;
        }

        //  Atomic subtraction. Returns false if the counter drops to zero.
        inline bool sub(uint32_t dec){

            uint32_t old  = -dec;
            volatile uint32_t *val = &value_;
            __asm__ volatile ("lock; xaddl %0,%1"
            : "=r" (old), "=m" (*val)
            : "0" (old), "m" (*val)
            : "cc", "memory");
            return old != dec;
        }

    private:

        volatile uint32_t value_;

        YAtomicCounter(const YAtomicCounter &);
        const YAtomicCounter & operator= (const YAtomicCounter &);
    };


}


#endif //YMQ_YATOMICCOUNTER_HPP
