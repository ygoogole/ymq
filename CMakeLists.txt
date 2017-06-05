cmake_minimum_required(VERSION 2.8)
project(ymq)

enable_testing()

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -Wall -g")
add_subdirectory(tests)

include_directories(src)
file(GLOB SRCS
    *.cpp
    *.hpp
    src/*.cpp
    src/*.hpp
    )

#set(SOURCE_FILES main.cpp src/YyQueue.hpp src/YAtomicPtr.hpp src/YyPipe_base.hpp src/YyPipe.hpp src/YBaseSocket.cpp
#        src/YObject.cpp src/Context.cpp src/YReaper.cpp
#        src/YConstPool.hpp src/YIOThread.cpp src/YIOThread.hpp src/YBaseMailbox.hpp src/YMailbox.cpp src/YMailbox.hpp src/YCommon.hpp src/YBasePoller.cpp src/YBasePoller.hpp src/YEPoller.cpp src/YEPoller.hpp src/YSignaler.cpp src/YSignaler.hpp src/YIPCtrl.cpp src/YIPCtrl.hpp src/YThread.cpp src/YThread.hpp src/YMutex.hpp src/YOwner.cpp src/YOwner.hpp src/YArray.hpp src/YPipe.cpp src/YPipe.hpp src/YAtomicCounter.hpp src/YTcpListner.cpp src/YTcpListner.hpp src/YIoObject.cpp src/YIoObject.hpp src/tcp.cpp src/tcp.hpp src/YOption.cpp src/YOption.hpp src/YRouter.cpp src/YRouter.hpp src/YReply.cpp src/YReply.hpp src/YMsg.cpp src/YMsg.hpp)

set(CMAKE_THREAD_PREFER_PTHREAD TRUE)

add_executable(ymq ${SRCS} src/Msg.cpp src/Msg.h)

#add_definitions(-D_PTHREADS)

# CMAKE_THREAD_LIBS_INIT        - the thread library to link into an application (-lpthread )
# CMAKE_USE_SPROC_INIT          - are we using sproc?
# CMAKE_USE_WIN32_THREADS_INIT  - are we using WIN32 threads
# CMAKE_USE_PTHREADS_INIT       - are we using pthreads
# CMAKE_HP_PTHREADS_INIT        - are we using hp pthreads

# to link pthread library, otherwise there is link error.
find_package(Threads REQUIRED)
target_link_libraries(ymq ${CMAKE_THREAD_LIBS_INIT})
