#pragma once


#include <string.h>
#include <string>

#include <algorithm>
#include <cctype>
#include <fstream>
#include <iostream>
#include <set>
#include <sstream>
#include <string>

#include "../Networking/Server/Server.hpp"
#include "LocationBlock.hpp"
#include "ServerBlock.hpp"

class ConfigFile
{
  public:
    // ConfigFile();
    ConfigFile(const std::string configFile);
    ~ConfigFile();
    std::deque<ServerBlock> getServers();
    int serverCount;
    std::deque<ServerBlock> serverBlocks;

  private:
    std::string currentLocationPath;
    std::ifstream configFile;
    std::string line;
    ServerBlock currentServer;
    LocationBlock currentLocation;
    bool inLocationBlock;
    bool isExisting();
    void readConfig();
    void checkToken(std::string token);
    void populateLocations();

    void populateIpPort();
    std::string getOptionValue(const std::string &optionName);
    template <typename T> std::string optionValue(T &block, const std::string &optionName);

    ServerBlock *serverAt(const int socket);

    void printServersInfo();
    void printServerBlocks(const std::deque<ServerBlock> &serverBlocks);
    std::string trim(const std::string &str);
};
