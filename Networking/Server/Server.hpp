#pragma once

#include "SimpleServer.hpp"
#include "../../Parser/ServerBlock.hpp"

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
    ServerBlock *serverConfig;

  public:
    void launch();
    Server();
    Server(std::string interfaceIp, uint16_t port, ServerBlock* serverConfig);
    Server(int domain, int service, int protocol, uint16_t port, std::string interfaceIp, int backlog, ServerBlock* serverConfig);

};
} // namespace NTW