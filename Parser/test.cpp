#include <fstream>
#include <iostream>
#include <map>
#include <sstream>
#include <string>
#include <vector>

struct Location
{
    std::string path;
    std::vector<std::string> allow_methods;
    bool autoindex;
    std::string index;
};

struct Server
{
    int listen_port;
    std::vector<std::string> server_names;
    std::string host;
    int client_max_body_size;
    std::string root;
    std::vector<std::string> index;
    std::map<std::string, Location> locations;
};

//std::vector<Server> servers;

void printServerInfo(const std::vector<Server> &servers)
{
    // print
    for (const Server &server : servers)
    {
        std::cout << "\n"
                  << "Listening port: " << server.listen_port << "\n"
                  << "Host: " << server.host << "\n"
                  << "Max body size: " << server.client_max_body_size << "\n"
                  << "Root: " << server.root << std::endl;

        if (!server.server_names.empty())
        {
            std::cout << "Server name: " << server.server_names[0] << std::endl;
        }
        if (!server.index.empty())
        {
            std::cout << "Index: " << server.index[0] << std::endl;
        }
    }
}

/* int main()
{
    std::ifstream configFile("config.conf");
    if (!(configFile.is_open()))
    {
        std::cerr << "Error opening file" << std::endl;
        return EXIT_FAILURE;
    }
    std::string line;
    Server currentServer;

    while (std::getline(configFile, line))
    {
        std::istringstream iss(line);
        std::string token;
        iss >> token;

        if (token == "location")
        {
            std::string location_path;
            iss >> location_path;

            // Skip everything between "location" and the next "}"
            while (std::getline(configFile, line))
            {
                // Stop skipping when reaching the closing curly brace
                if (line.find("}") != std::string::npos)
                {
                    break;
                }
            }
        }
        else if (token == "server")
        {
            servers.push_back(currentServer);
            currentServer = Server();
        }
        else if (token == "listen")
        {
            iss >> currentServer.listen_port;
        }
        else if (token == "server_name")
        {
            std::string server_name;
            while (iss >> server_name)
            {
                currentServer.server_names.push_back(server_name);
            }
        }
        else if (token == "host")
        {
            iss >> currentServer.host;
        }
        else if (token == "client_max_body_size")
        {
            iss >> currentServer.client_max_body_size;
        }
        else if (token == "root")
        {
            iss >> currentServer.root;
            std::cout << "!!! found a root " << currentServer.root << " " << std::endl;
        }
        else if (token == "index")
        {
            std::string index_name;
            while (iss >> index_name)
            {
                currentServer.index.push_back(index_name);
            }
        }
        else if (token == "allow_methods") {
            // add to set
        }
        else if (token == "autoindex") {
            // change boolean
        }
        else if (token == "cgi_path") {
            // add to set
        } else if (token == "cgi_ext") {
            // add to set
        } else if (token == "error_page") {
            // add to map
        }
    }
    servers.push_back(currentServer);

    printServerInfo(servers);
    std::cout << "\nParser finished" << std::endl;
} */