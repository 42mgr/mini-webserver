#include "SimpleServer.hpp"
#include <netinet/in.h>

NTW::SimpleServer::SimpleServer(int domain, int service, int protocol, int port, u_long interface, int backlog)
{
    socket = new ListeningSocket(domain, service, protocol, port, interface, backlog);

    std::ostringstream oss;
    oss << "Created listening socket " << socket->get_sock() << RESET << " for " << domain << " (domain), " << service
        << " (service), " << protocol << " (protocol), " << port << " (port), " << interface << " (interface), "
        << backlog << " (backlog)";
    log(oss.str(), "SIMPLE SERVER ", YELLOW);
}

NTW::SimpleServer::~SimpleServer()
{
    delete socket;
}

NTW::ListeningSocket *NTW::SimpleServer::get_socket()
{
    return socket;
}