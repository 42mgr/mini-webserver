#include "SimpleServer.hpp"
#include <netinet/in.h>

NTW::SimpleServer::SimpleServer(int domain, int service, int protocol, uint16_t port, std::string interfacIp, int backlog)
{
    socket = new ListeningSocket(domain, service, protocol, port, htonl(inet_addr(interfacIp.c_str())), backlog);

    std::ostringstream oss;
    //std::string ip = inet_ntoa((*(struct in_addr *)&(interface = ntohl(interface))));
    oss << "Created listening socket " << socket->get_sock() << RESET << " for " << domain << " (domain), " << service
        << " (service), " << protocol << " (protocol), " << interfacIp << ":" << port <<", "
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