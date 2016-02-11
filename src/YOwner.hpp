//
// Created by i059483 on 10/8/15.
//

#ifndef YMQ_YOWNER_HPP
#define YMQ_YOWNER_HPP

#include "YObject.hpp"
//#include "YContext.hpp"

namespace ymq {

    class YIOThread;
    class YContext;

    class YOwner : public YObject {

    public:

        YOwner(YContext *parent, uint32_t tid);
        YOwner(YIOThread *io_thread);

        virtual ~YOwner();

        void launch_child(YOwner *object);


    private:

        YOwner *owner_;

    private:
        YOwner(const YOwner &);
        const YOwner & operator = (const YOwner &);

        void set_owner(YOwner *owner);
    };

}


#endif //YMQ_YOWNER_HPP
