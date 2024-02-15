#pragma once

#include "../webserver.hpp"

class ServerBlock;

class LocationBlock
{
  public:
    std::map<std::string, std::string> options;
    std::string path;
};
