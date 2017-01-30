#ifndef SOCKET_BASE_HPP
#define SOCKET_BASE_HPP

#include <string>
#include <memory>
#include <unordered_map>
#include "EpollerBase.hpp"
#include "TcpListener.hpp"

namespace ymq {

    class Context;
    class SocketBase : EpollerBase {

        public:
            
            SocketBase(Context *ctx, unsigned type);
            int bind(std::string addr);
            int accept();
            void inEvent();
            void outEvent();

            Context *ctx_;
            std::unordered_map<std::string, std::shared_ptr<TcpListener> > endpoints_;
    };

}
#endif
