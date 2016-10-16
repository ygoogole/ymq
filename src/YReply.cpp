//
// Created by i059483 on 10/26/15.
//

#include "YReply.hpp"

ymq::YReply::YReply(ymq::Context *parent, uint32_t tid, int sid)
    :YRouter(parent, tid, sid){

}

int ymq::YReply::xsend(ymq::YMsg *msg) {

    return YRouter::xsend(msg);
}

int ymq::YReply::xrecv(ymq::YMsg *msg) {
    return YRouter::xrecv(msg);
}
