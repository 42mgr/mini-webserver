#pragma once

#include "../webserver.hpp"
#include <vector>
#include <map>

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
};
