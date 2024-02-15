#pragma once

#include "SimpleSocket.hpp"

namespace NTW
{
class BindingSocket : public SimpleSocket
{
  public:
    BindingSocket(int domain, int service, int protocol, int port, u_long interface);
    int get_binding();

  private:
    int binding;
    int connect_to_network(int sock, struct sockaddr_in address);
};
} // namespace NTW