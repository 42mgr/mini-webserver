#pragma once

#include "SimpleServer.hpp"

namespace NTW
{
class TestServer : public SimpleServer
{
  private:
    void accepter();
    void handler();
    void responder();
    char buffer[30000];
    int new_socket;

  public:
    void launch();
    TestServer();
    //SimpleServer(AF_INET, SOCK_STREAM, 0, 8000, INADDR_ANY, 10
};
} // namespace NTW