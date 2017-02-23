#include <iostream>
#include <string>
#include <memory>
#include "Mailbox.hpp"
#include "IoThread.hpp"
#include "Context.hpp"
#include "SocketBase.hpp"
#include "RwQueue.hpp"

using namespace ymq;

int main(int argc, char *argv[]) {

    /*
    ymq::Mailbox box;
    IoThread thread(&ctx, 0);

    thread.start();
    sleep(5);
    thread.stop();

    sleep(10000);*/

    Context ctx(1);
    std::cout << "Testing starts..." << std::endl;

    SocketBase *sock = ctx.create_socket(0);

    sock->bind(std::string(argv[1]));

    sleep(10000);

    return 0;
}
