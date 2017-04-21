#ifndef CLIENT_MANAGER_H
#define CLIENT_MANAGER_H

#include <netinet/in.h>

class client_manager {

    int client_fd;
    ::sockaddr_in client_addr;

    bool is_accepted = false;
public:

    void accept(int server_fd);

    size_t read(char* buffer, size_t size);

    void write(char* buffer, size_t size);
    
    void close();
};

#endif // CLIENT_MANAGER_H
