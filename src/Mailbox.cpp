#include "Mailbox.hpp"

using namespace ymq;

Mailbox::Mailbox()
    : pipe_()
    , signaler_()
    , active_(false)
{
    pipe_.read(nullptr);
}

Mailbox::~Mailbox() {
}

fd_t Mailbox::getFd() {
    return signaler_.getFd();
}

void Mailbox::send(Command &cmd) {

    // TODO: may need a sync here
    pipe_.write(cmd);
    bool ret = pipe_.flush();
    if (!ret) {
        signaler_.send();
    }
}

int Mailbox::recv(Command *cmd, int timeout) {

    if (active_) {
        if (pipe_.read(cmd))
            return 0;

        active_ = false;
    }

    int rc = signaler_.wait(timeout);
    if (rc == -1) {
        assert(errno == EAGAIN || errno == EINTR);
        return -1;
    }

    signaler_.recv();

    active_ = true;

    const bool ok = pipe_.read(cmd);
    assert(ok);

    return 0;
}
