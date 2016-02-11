#include <iostream>
#include "YyQueue.hpp"
#include "YyPipe.hpp"
#include "YyPipe_base.hpp"
#include "YCommand.hpp"
#include "YPollEvent.hpp"
#include "YContext.hpp"
#include "YBaseSocket.hpp"
#include "YSignaler.hpp"
#include "YMutex.hpp"
#include "YArray.hpp"
//#include "YAtomicCounter.hpp"

using namespace std;

int main() {

    ymq::YContext ctx(1);

    cout << "Hello, World!" << endl;
    return 0;
}