#pragma once

#include "BindingSocket.hpp"

namespace NTW
{
class ListeningSocket : public BindingSocket
{
  public:
    ListeningSocket(int domain, int service, int protocol, uint16_t port, u_long interface, int backlog);
    virtual ~ListeningSocket();
    void start_listening();

  private:
    int backlog;
    int listening;
};
} // namespace NTW