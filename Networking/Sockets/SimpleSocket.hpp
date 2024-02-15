#pragma once

#include "../../webserver.hpp"
#include <netinet/in.h>
#include <sys/socket.h>

namespace NTW
{
class SimpleSocket
{
  public:
    SimpleSocket(int domain, int service, int protocol, uint16_t port, u_long interface);
    virtual int connect_to_network(int sock, struct sockaddr_in address) = 0;
    void test_connection(int);
    struct sockaddr_in get_address();
    int get_sock();

  private:
    int sock;
    struct sockaddr_in address;
};
} // namespace NTW