#include "Mailbox.hpp"

ymq::Mailbox::Mailbox()
    : signaler_()
{
}

ymq::Mailbox::~Mailbox() {
}

ymq::fd_t ymq::Mailbox::getFd() {
    return signaler_.getFd();
}
