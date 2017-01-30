#ifndef YMQ_TCP_HPP
#define YMQ_TCP_HPP

#include <stddef.h>
#include "Common.hpp"

namespace ymq{

    //  Tunes the supplied TCP socket for the best latency.
    void tune_tcp_socket (fd_t s);

    //  Sets the socket send buffer size.
    void set_tcp_send_buffer (fd_t sockfd, int bufsize);

    //  Sets the socket receive buffer size.
    void set_tcp_receive_buffer (fd_t sockfd, int bufsize);

    //  Tunes TCP keep-alives
    void tune_tcp_keepalives (fd_t s, int keepalive, int keepalive_cnt, int keepalive_idle, int keepalive_intvl);

    //  Tunes TCP retransmit timeout
    void tune_tcp_retransmit_timeout (fd_t sockfd, int timeout);

    //  Writes data to the socket. Returns the number of bytes actually
    //  written (even zero is to be considered to be a success). In case
    //  of error or orderly shutdown by the other peer -1 is returned.
    int tcp_write (fd_t s, const void *data, size_t size);

    //  Reads data from the socket (up to 'size' bytes).
    //  Returns the number of bytes actually read or -1 on error.
    //  Zero indicates the peer has closed the connection.
    int tcp_read (fd_t s, void *data, size_t size);

}



#endif //YMQ_TCP_HPP
