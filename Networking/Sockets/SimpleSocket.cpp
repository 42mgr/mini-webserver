#include "SimpleSocket.hpp"

NTW::SimpleSocket::SimpleSocket(int domain, int service, int protocol, uint16_t port, u_long interface)
{
    address.sin_family = domain;
    address.sin_port = htons(port);
    address.sin_addr.s_addr = htonl(interface);

    sock = socket(domain, service, protocol);
    test_connection(sock);

    std::ostringstream oss;
    oss << "Creating socket for " << domain << " (domain), " << service << " (service), " << protocol << " (protocol), "
        << sock << " (socket);";
    log(oss.str(), "SIMPLE SOCKET   ", RESET);
}

void NTW::SimpleSocket::test_connection(int item_to_test)
{
    if (item_to_test < 0)
    {
        perror("Failed to connect...");
        exit(EXIT_FAILURE);
    }
}

sockaddr_in NTW::SimpleSocket::get_address()
{
    return address;
}

int NTW::SimpleSocket::get_sock()
{
    return sock;
}
