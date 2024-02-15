#pragma once

#include "../../webserver.hpp"
#include "../Sockets/ListeningSocket.hpp"

namespace NTW
{
class SimpleServer
{
  public:
    SimpleServer(int domain, int service, int protocol, uint16_t port, std::string interfaceIp, int backlog);
    virtual ~SimpleServer();
    virtual void launch() = 0;
    ListeningSocket *get_socket();

  private:
    ListeningSocket *socket;
    virtual void accepter() = 0;
    virtual void handler() = 0;
    virtual void responder() = 0;
};
} // namespace NTW