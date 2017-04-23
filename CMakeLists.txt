cmake_minimum_required(VERSION 2.8)

set(CMAKE_CXX_STANDARD 14)

# set( CMAKE_VERBOSE_MAKEFILE on  )

# set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "out/")
set(EXECUTABLE_OUTPUT_PATH "../")

set(CMAKE_CXX_FLAGS "-pthread -lpthread -Wl,--no-as-needed")

add_executable(main
    src/main.cpp
    src/echo_server.cpp
    src/debug.cpp
    src/client_manager.cpp
    src/epoll_helper.cpp
)
