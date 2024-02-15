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

std::vector<Server> servers;

void parseConfig(const std::string &filename)
{
    std::ifstream configFile(filename);
    /*      if (!configFile.is_open()) {
            std::cerr << "Error opening file: " << filename << std::endl;
            return;
        } */
    std::string line;

    Server currentServer;
    while (std::getline(configFile, line))
    {
        std::istringstream iss(line);
        std::string token;
        iss >> token;
        if (token == "server")
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
        else if (token == "host") {
            iss >> currentServer.host;
        } else if (token == "client_max_body_size") {
            iss >> currentServer.client_max_body_size;
        } else if (token == "root") {
            iss >> currentServer.root;
        } else if (token == "index") {
            std::string index_name;
            while (iss >> index_name) {
                currentServer.index.push_back(index_name);
            }
        } else if (token == "location") {
            Location loc;
            std::string location_path;
            iss >> location_path;


            while (iss >> token && token != "}")
            {
                std::cout << token << std::endl;
                if (token == "allow_methods")
                {
                    while (iss >> token && token != ";") {
                        loc.allow_methods.push_back(token);
                    }
                }
                else if (token == "autoindex")
                {
                    std::string value;
                    iss >> value;
                    loc.autoindex = (value == "on");
                }
                else if (token == "index")
                {
                    iss >> loc.index;
                }
            }
            currentServer.locations[location_path] = loc;
        }
        std::cout  << " "  << currentServer.listen_port << " " <<  " " << currentServer.host << " "
                  << currentServer.client_max_body_size << " " << std::endl;

    /* while (std::getline(configFile, line)) {
        std::cout << line << std::endl;

    }
    servers.push_back(currentServer); // Add the last server */
}}

/* int main()
{
    parseConfig("config.conf");

    // Now you can use the 'servers' vector to access parsed configuration data
    for (const auto &server : servers)
    {
        std::cout << "Server listening on port " << server.listen_port << std::endl;
        // Output other server attributes
        for (const auto &location_pair : server.locations)
        {
            const Location &location = location_pair.second;
            std::cout << "Location: " << location.path << std::endl;
            // Output other location attributes
        }
    }

    return 0;
} */
