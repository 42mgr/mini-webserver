#include "TestServer.hpp"


void NTW::TestServer::accepter()
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
    oss << "Client connected from: " << inet_ntoa(address_in.sin_addr) << ":" << ntohs(address_in.sin_port) << " serverside: " << socket << " (listening socket), "  << new_socket << " (internal socket)" ;
    log(oss.str(), " ACCEPTER ", YELLOW);
}

void NTW::TestServer::handler()
{
    std::cout << buffer << std::endl;
}

void NTW::TestServer::responder()
{

    std::ifstream file("./www/index.html");
    std::stringstream buffer;
    buffer << file.rdbuf();
    std::string contents = buffer.str();

    std::cout << contents.c_str() << std::endl;
    write(new_socket, contents.c_str(), contents.size());
    close(new_socket);
}

void NTW::TestServer::launch()
{

    while (true)
    {
        std::cout << " ==== WAITING =====" << std::endl;
        accepter();
        handler();
        responder();
        std::cout << "== DONE ==" << std::endl;
    }
}

NTW::TestServer::TestServer() : SimpleServer(AF_INET, SOCK_STREAM, 0, 8000, INADDR_ANY, 10)
{
    //launch();
}