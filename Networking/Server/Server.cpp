#include "Server.hpp"
#include "../HandlerResponder/Request.hpp"
#include "../HandlerResponder/Response.hpp"

void NTW::Server::accepter()
{
    int socket = get_socket()->get_sock();
    struct sockaddr_in address_in = get_socket()->get_address();
    struct sockaddr *address = (struct sockaddr *)&(address_in);
    int address_size = sizeof(address_in);
    socklen_t *address_len = (socklen_t *)&(address_size);

    new_socket = accept(socket, address, address_len);
    read(new_socket, buffer, 30000);

    std::ostringstream oss;
    char ipstr[INET_ADDRSTRLEN];
    inet_ntop(AF_INET, &(address_in), ipstr, sizeof(ipstr));
    oss << "Client connected from: " << inet_ntoa(address_in.sin_addr) << ":" << ntohs(address_in.sin_port)
        << " serverside: " << socket << " (listening socket), " << new_socket << " (internal socket)";
    log(oss.str(), " ACCEPTER ", YELLOW);
}

void NTW::Server::handler()
{
    std::cout << buffer << std::endl;
    Request req(buffer);
    Response res(req);
    std::string response = res.createHTTPResponse();
    send(new_socket, response.c_str(), response.length(), 0);
}

void NTW::Server::responder()
{

    std::ifstream file("./www/index.html");
    std::stringstream buffer;
    buffer << file.rdbuf();
    std::string contents = buffer.str();

    std::cout << contents.c_str() << std::endl;
    write(new_socket, contents.c_str(), contents.size());
    close(new_socket);
}

void NTW::Server::launch()
{
    accepter();
    handler();
    responder();
}
NTW::Server::Server(int domain, int service, int protocol, uint16_t port, std::string interfaceIp, int backlog)
    : SimpleServer(domain, service, protocol, port, interfaceIp, backlog)
{
}

NTW::Server::Server()
    : SimpleServer(AF_INET, SOCK_STREAM, 0, 9090, "192.168.178.25",
                   10) // INADDR_ANY inet_addr("192.168.178.25") INADDR_LOOPBACK
{
}

NTW::Server::Server(std::string interfaceIp, uint16_t port)
    : NTW::SimpleServer(AF_INET, SOCK_STREAM, 0, port, interfaceIp, 5)
{
}