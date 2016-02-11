//
// Created by i059483 on 10/17/15.
//

#ifndef YMQ_YIOOBJECT_HPP
#define YMQ_YIOOBJECT_HPP

//#include "YIOThread.hpp"

#include <stddef.h>
#include "YPollEvent.hpp"
#include "YCommon.hpp"
#include "YEPoller.hpp"

namespace ymq{

    class YIOThread;

    class YIoObject : public YPollEvent {

    public:
        YIoObject(ymq::YIOThread *thread = NULL);
        ~YIoObject();

        void plug (ymq::YIOThread *io_thread);
        void unplug ();

    protected:

        typedef YEPoller::handle_t handle_t;

        //  Methods to access underlying poller object.
        handle_t add_fd (fd_t fd);
        void rm_fd (handle_t handle);
        void set_pollin (handle_t handle);
        void reset_pollin (handle_t handle);
        void set_pollout (handle_t handle);
        void reset_pollout (handle_t handle);
        void add_timer (int timout, int id);
        void cancel_timer (int id_);

        // YPollEvent interface implementation.
        void in_event ();
        void out_event ();
        void timer_event (int id);

    private:

        YEPoller *poller_;

        YIoObject(const YIoObject &);
        const YIoObject & operator= (const YIoObject &);
    };
}



#endif //YMQ_YIOOBJECT_HPP
