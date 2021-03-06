#ifndef YMQ_YOWNER_HPP
#define YMQ_YOWNER_HPP

#include "Object.hpp"
//#include "Context.hpp"

namespace ymq {

    class IoThread;
    class Context;

    class YOwner : public Object {

    public:

        YOwner(Context *parent, uint32_t tid);
        YOwner(IoThread *io_thread);

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
