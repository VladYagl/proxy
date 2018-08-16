#ifndef EPOLL_HELPER_H
#define EPOLL_HELPER_H

#include <sys/epoll.h>

class epoll_helper {
    // FIXME
public:
    constexpr static int CREATE_FLAGS = ::EPOLL_CLOEXEC;
    constexpr static uint16_t MAX_EVENTS = 16;

    int epoll_fd;
    int signal_fd;
    int event_count;
    int event_position;

    epoll_event events[MAX_EVENTS];

    void add_event(int fd, uint32_t events);
public:
    epoll_helper(int server_fd);

    ~epoll_helper();

    void add_client(int client_fd);

    void remove_client(int client_fd);

    void sleep(int timeout);

    epoll_event& next_event();

    bool empty();
};

#endif  // EPOLL_HELPER_H
