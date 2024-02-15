#pragma once

#include "SimpleServer.hpp"

namespace NTW
{
class Server : public SimpleServer
{
  private:
    void accepter();
    void handler();
    void responder();
    char buffer[30000];
    int new_socket;

  public:
    void launch();
    Server();
    Server(std::string interfaceIp, uint16_t port);
    Server(int domain, int service, int protocol, uint16_t port, std::string interfaceIp, int backlog);

};
} // namespace NTW