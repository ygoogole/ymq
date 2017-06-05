#ifndef YMQ_YPIPE_HPP
#define YMQ_YPIPE_HPP

#include "Object.hpp"
#include "YArray.hpp"

namespace ymq{

    //  Note that pipe can be stored in three different arrays.
    //  The array of inbound pipes (1), the array of outbound pipes (2) and
    //  the generic array of pipes to deallocate (3).
    class YPipe : public Object, public YArrayItem<1>, public YArrayItem<2>, public YArrayItem<3>{

    private:

        //  Type of the underlying lock-free pipe.
        //typedef YyPipe_base <YMsg> upipe_t;

        YPipe(const YPipe &);
        const YPipe & operator= (const YPipe &);
    };

    struct i_pipe_events
    {
        virtual ~i_pipe_events () {}

        virtual void read_activated (ymq::YPipe *pipe) = 0;
        virtual void write_activated (ymq::YPipe *pipe) = 0;
        virtual void hiccuped (ymq::YPipe *pipe) = 0;
        virtual void pipe_terminated (ymq::YPipe *pipe) = 0;
    };


}



#endif //YMQ_YPIPE_HPP
