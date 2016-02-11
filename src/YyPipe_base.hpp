//
// Created by i059483 on 9/6/15.
//

#ifndef YMQ_YYPIPE_BASE_HPP
#define YMQ_YYPIPE_BASE_HPP

namespace ymq{

    template<typename T> class YyPipe_base{

        public:
            virtual ~YyPipe_base () {}
            virtual void write (const T &value_, bool incomplete_) = 0;
            virtual bool unwrite (T *value_) = 0;
            virtual bool flush () = 0;
            virtual bool check_read () = 0;
            virtual bool read (T *value_) = 0;
            virtual bool probe (bool (*fn)(const T &)) = 0;
    };
}


#endif //YMQ_YYPIPE_BASE_HPP
