//
// Created by i059483 on 9/7/15.
//

#ifndef YMQ_YOBJECT_HPP
#define YMQ_YOBJECT_HPP

#include <stdint-gcc.h>
#include "YCommand.hpp"
//#include "YOwner.hpp"
//#include "Context.hpp"

namespace ymq{

    class Context;
    class YCommand;
    class IoThread;
    class YOwner;

    class YObject {

    public:

        YObject(ymq::Context *ctx, uint32_t tid);
        YObject(YObject *parent);

        virtual ~YObject();

        uint32_t get_tid();
        void set_tid(uint32_t tid);
        IoThread* choose_io_thread();

        Context* get_context();
        void process_command(ymq::YCommand &cmd);
        //void send_command();

    protected:

        virtual void process_plug();
        virtual void process_bind();

        void send_command(YCommand &cmd);
        void send_stop();
        void send_plug (ymq::YOwner *destination, bool inc_seqnum_ = true);

    private:

        ymq::Context *ctx_;
        uint32_t tid_;


        YObject( const YObject &);
        const YObject& operator=( const YObject &);

    };
}



#endif //YMQ_YOBJECT_HPP
