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
    /* Here the request is read and the server does its job

    I have thought that it is a better design if the handler() is organzing all the necessary data for the response, so that the response is "only building header and html" out of the provided information.

    So something should be put between the request and the response classes. The response does way too much right now. Ideally each server receives its corresponding parser object and then does the checking if that matches with the request.

    Chatty suggets:
    - The handler is responsible for processing the incoming requests from clients.
    - It parses the incoming requests, extracts relevant information (such as HTTP headers, request parameters, etc.), and performs the necessary actions based on the request type (e.g., serving static files, executing server-side code, querying a database, etc.).
    - The handler may also perform authentication, authorization, and request validation tasks before processing the request further.

    */
    Response res(req);
    std::string response = res.createHTTPResponse();
    send(new_socket, response.c_str(), response.length(), 0); // what is the difference to write()?
}

void NTW::Server::responder()
{

    /* Response should be built here out of handler information

    Chattys thoughts:
    - The responder is responsible for generating and sending responses back to clients based on the results of request handling.
    - It constructs HTTP responses with appropriate status codes, headers, and content (e.g., HTML, JSON, etc.).
    - The responder sends the response back to the client over the established connection.
     */
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