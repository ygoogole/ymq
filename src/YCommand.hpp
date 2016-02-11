//
// Created by i059483 on 9/20/15.
//

#ifndef YMQ_YCOMMAND_HPP
#define YMQ_YCOMMAND_HPP

namespace ymq{

    class YObject;

    struct YCommand {

        ymq::YObject  *destination;

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



#endif //YMQ_YCOMMAND_HPP
