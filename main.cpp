#include <iostream>
#include "YyQueue.hpp"
#include "YyPipe.hpp"
#include "YyPipe_base.hpp"
#include "YCommand.hpp"
#include "YPollEvent.hpp"
#include "Context.hpp"
#include "YBaseSocket.hpp"
#include "YSignaler.hpp"
#include "YMutex.hpp"
#include "YArray.hpp"
//#include "YAtomicCounter.hpp"
#include "Signaler.hpp"

using namespace std;
//using namespace ymq;

int main() {

    ymq::Context ctx(1);

    ymq::Signaler sig;
    sig.send();

    cout << "Hello, World!" << endl;
    return 0;
}
