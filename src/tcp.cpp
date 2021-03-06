#include <sys/socket.h>
#include <netinet/in.h>
#include <netinet/tcp.h>
#include <assert.h>
#include "tcp.hpp"

using namespace ymq;

void ymq::tune_tcp_socket(fd_t s) {

    int nodelay = 1;

    // using positive int value to enable NO_DELAY, zero to disable
    int rc = setsockopt(s, IPPROTO_TCP, TCP_NODELAY, (char *) &nodelay, sizeof (int));
}

void ymq::set_tcp_send_buffer(fd_t sockfd, int bufsize) {

    const int rc = setsockopt (sockfd, SOL_SOCKET, SO_SNDBUF,
                               (char*) &bufsize, sizeof bufsize);
}

void ymq::set_tcp_receive_buffer(fd_t sockfd, int bufsize) {

    const int rc = setsockopt (sockfd, SOL_SOCKET, SO_RCVBUF,
                               (char*) &bufsize, sizeof bufsize);
}

void ymq::tune_tcp_keepalives(fd_t s, int keepalive, int keepalive_cnt, int keepalive_idle,
                                int keepalive_intvl) {

    if (keepalive != -1) {
        int rc = setsockopt (s, SOL_SOCKET, SO_KEEPALIVE, (char*) &keepalive, sizeof (int));
        assert (rc == 0);

        if (keepalive_cnt != -1) {
            int rc = setsockopt (s, IPPROTO_TCP, TCP_KEEPCNT, &keepalive_cnt, sizeof (int));
            assert (rc == 0);
        }

        if (keepalive_idle != -1) {
            int rc = setsockopt (s, IPPROTO_TCP, TCP_KEEPIDLE, &keepalive_idle, sizeof (int));
            assert (rc == 0);
        }

        if (keepalive_intvl != -1) {
            int rc = setsockopt(s, IPPROTO_TCP, TCP_KEEPINTVL, &keepalive_intvl, sizeof(int));
            assert (rc == 0);
        }
    }
}

void ymq::tune_tcp_retransmit_timeout(fd_t sockfd, int timeout) {

    if (timeout <= 0)
        return;

/*    int rc = setsockopt (sockfd, IPPROTO_TCP, TCP_USER_TIMEOUT, &timeout,
        sizeof(timeout));
    assert (rc == 0);
*/
}

int ymq::tcp_write(fd_t s, const void *data, size_t size) {

    const ssize_t rc = send(s, data, size, 0);

    return static_cast<int>(rc);
}

int ymq::tcp_read(fd_t s, void *data, size_t size) {

    const ssize_t rc = recv(s, data, size, 0);

    return static_cast<int>(rc);
}
