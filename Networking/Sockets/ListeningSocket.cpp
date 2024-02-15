#include "ListeningSocket.hpp"


NTW::ListeningSocket::ListeningSocket(int domain, int service, int protocol, int port, u_long interface, int backlog)
    : BindingSocket(domain, service, protocol, port, interface)
{
    std::ostringstream oss;
    oss << "Listening socket for "  << domain << " (domain), " << service << " (service), " << protocol << " (protocol), "
        << port << " (port), " << interface << " (interface), " << backlog << " (backlog)";
    log(oss.str(), "LISTENING SOCK ", RESET);

    this->backlog = backlog;
    start_listening();
    test_connection(listening);
}

void NTW::ListeningSocket::start_listening()
{
    listening = listen(get_sock(), backlog);
}

NTW::ListeningSocket::~ListeningSocket() {

}