#ifndef MQ_IOOBJECT_HPP
#define MQ_IOOBJECT_HPP

#include <stddef.h>
#include "EpollerBase.hpp"
#include "Common.hpp"
#include "Epoller.hpp"

namespace ymq{

    class IoThread;

    class IoObject : public EpollerBase {

    public:
        IoObject(IoThread *thread = nullptr);
        ~IoObject();

    protected:

        typedef Epoller::EpollHandle handle_t;

        //  Methods to access underlying poller object.
        handle_t addFd(fd_t fd);
        void rmFd(handle_t handle);
        void setPollin(handle_t handle);
        void resetPollin(handle_t handle);
        void setPollout(handle_t handle);
        void resetPollout(handle_t handle);

        // PollEvent interface implementation.
        void inEvent() override;
        void outEvent() override;

        IoThread *io_thread_;

    private:

        Epoller *poller_;

        IoObject(const IoObject &) = delete;
        const IoObject & operator= (const IoObject &) = delete;
    };
}

#endif //YMQ_IOOBJECT_HPP
