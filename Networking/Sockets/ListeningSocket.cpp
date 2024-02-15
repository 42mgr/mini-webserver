#include "ListeningSocket.hpp"

NTW::ListeningSocket::ListeningSocket(int domain, int service, int protocol, uint16_t port, u_long interface,
                                      int backlog)
    : BindingSocket(domain, service, protocol, port, interface)
{
    std::ostringstream oss;
    std::string ip = inet_ntoa((*(struct in_addr *)&(interface = ntohl(interface))));
    oss << "Listening socket for " << domain << " (domain), " << service << " (service), " << protocol
        << " (protocol), " << ip << ":" << port << ", " << backlog << " (backlog)";
    log(oss.str(), "LISTENING SOCK ", RESET);

    this->backlog = backlog;
    start_listening();
    test_connection(listening);
}

void NTW::ListeningSocket::start_listening()
{
    listening = listen(get_sock(), backlog);
}

NTW::ListeningSocket::~ListeningSocket()
{
}