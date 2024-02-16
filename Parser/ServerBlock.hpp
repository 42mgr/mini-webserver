#pragma once

#include "../webserver.hpp"


#include "LocationBlock.hpp"

class ServerBlock
{
  public:
    std::map<std::string, std::string> options;
    std::map<std::string, LocationBlock> locations;
    int socket;
    void printMapOptions();
    void printMapLocations();
    bool hasPath(std::string path);
        std::string serverIp;
    std::string port;
    std::string getPathFor(std::string uri);
};
