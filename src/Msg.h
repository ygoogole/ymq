#ifndef YMQ_MSG_H
#define YMQ_MSG_H

namespace ymq {

class Msg {

public:
    Msg()
        : len_(0) {}

    bool Init();
    void Close();
    void setData(void *, unsigned);

    void* data_;
    //bool free;
    unsigned len_;

    Msg(const Msg &);

private:
    Msg& operator=(const Msg &) = delete;

};
}



#endif //YMQ_MSG_H
