//
// Created by i059483 on 10/26/15.
//

#include "YRouter.hpp"

ymq::YRouter::YRouter(ymq::Context *parent, uint32_t tid, int sid)
    :YBaseSocket(parent, tid, sid){

}

int ymq::YRouter::xsend(ymq::YMsg *msg) {
    return 0;
}

int ymq::YRouter::xrecv(ymq::YMsg *msg) {
    return 0;
}
