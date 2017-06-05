#ifndef YMQ_OBJECT_HPP
#define YMQ_OBJECT_HPP

#include <stdint-gcc.h>
#include "Command.hpp"
//#include "YOwner.hpp"
//#include "Context.hpp"

namespace ymq{

    class Context;
    class Command;
    class IoThread;
    class YOwner;

    class Object {

    public:

        Object(ymq::Context *ctx, uint32_t tid);
        Object(Object *parent);

        virtual ~Object();

        uint32_t get_tid();
        void set_tid(uint32_t tid);
        IoThread* choose_io_thread();

        Context* get_context();
        void process_command(ymq::Command &cmd);

    protected:

        virtual void process_plug();
        virtual void process_bind();
        virtual void process_attach();

        void send_command(Command &cmd);
        void send_stop();
        void send_plug (ymq::YOwner *destination, bool inc_seqnum_ = true);

    private:

        ymq::Context *ctx_;
        uint32_t tid_;


        Object( const Object &) = delete;
        const Object& operator=( const Object &) = delete;

    };
}



#endif //YMQ_OBJECT_HPP
