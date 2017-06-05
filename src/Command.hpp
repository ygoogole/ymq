#ifndef YMQ_COMMAND_HPP
#define YMQ_COMMAND_HPP

namespace ymq{

    class Object;

    struct Command {

        Object  *destination;

        enum type_t{

            plug,
            bind,
            own,
            stop,
            attach,

        }type;

        union args_t{

            struct {
            } plug;

            struct {
            } bind;

            struct {
            } own;

            struct {
            } stop;

            struct {
            } attach;

        } args;

    };

}



#endif //YMQ_COMMAND_HPP
