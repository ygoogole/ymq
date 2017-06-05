#include <cstdlib>
#include <cstring>
#include "Msg.h"
#include "Common.hpp"

using namespace ymq;

bool Msg::Init()
{

    data_ = malloc(kMsgLength);
    if (!data_) {
        return false;
    }

    return true;
}

void Msg::Close() {

    if (data_) {
        delete data_;
        data_ = nullptr;
    }
}

void Msg::setData(void *src, unsigned len) {

    if (data_) {
        void *dst = memcpy(data_, src, len);
        assert(dst != nullptr);
    }
}

Msg::Msg(const Msg &msg) {
    data_ = msg.data_;
    len_  = msg.len_;
}

/*
Msg &Msg::operator=(const Msg &msg) {
    data_ = msg.data_;
    len_  = msg.len_;

    return *this;
}
*/
