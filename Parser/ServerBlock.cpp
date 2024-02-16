#include "ServerBlock.hpp"

void ServerBlock::printMapOptions()
{
    std::map<std::string, std::string>::iterator it;
    for (it = options.begin(); it != options.end(); ++it)
    {
        std::cout << "{ '" << it->first << "', '" << it->second << "' }" << std::endl;
    }
}

void ServerBlock::printMapLocations()
{
    /*     std::map<std::string, LocationBlock>::iterator it;
        for (it = path.begin(); it != path.end(); ++it)
        {
            std::cout << "{ '" << it->first << "', '" << it->second.options. << "' }"<< std::endl;
        } */
}

bool ServerBlock::hasPath(std::string path)
{
    return locations.find(path) != locations.end();
}


std::string ServerBlock::getPathFor(std::string uri) {
    return "/index.html";
}