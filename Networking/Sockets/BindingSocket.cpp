#include "BindingSocket.hpp"

NTW::BindingSocket::BindingSocket(int domain, int service, int protocol, int port, u_long interface)
    : NTW::SimpleSocket::SimpleSocket(domain, service, protocol, port, interface)
{
    binding = connect_to_network(get_sock(), get_address());

    std::ostringstream oss;
    oss << "Binding socket for " << domain << " (domain), " << service << " (service), " << protocol << " (protocol), "
        << port << " (port), " << interface << " (interface) ";
    log(oss.str(), "BINDING SOCKET   ", RESET);

    test_connection(binding);
}

int NTW::BindingSocket::connect_to_network(int sock, struct sockaddr_in address)
{
    return bind(sock, (struct sockaddr *)&address, sizeof(address));
}

int NTW::BindingSocket::get_binding()
{
    return binding;
}
