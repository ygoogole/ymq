#ifndef EPOLLER_BASE_HPP
#define EPOLLER_BASE_HPP

namespace ymq {
    class EpollerBase {
        public:
            virtual ~EpollerBase() {}
            virtual void inEvent() = 0;
            virtual void outEvent() = 0;
    };
}

#endif
