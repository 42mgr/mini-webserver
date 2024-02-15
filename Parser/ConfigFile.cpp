#include "ConfigFile.hpp"

const std::string DEFAULT_CONFIG = "../Configs/config.conf";

ConfigFile::~ConfigFile()
{
    if (configFile)
    {
        configFile.close();
    }
}

ConfigFile::ConfigFile(const std::string configFileString) : configFile(configFileString)
{
    if (isExisting())
    {
        readConfig();
        populateIpPort();
        serverCount = serverBlocks.size();


        std::cout << "----CONFIG START-----" << std::endl;
        printServerBlocks(serverBlocks);
        std::cout << "-------CONFIG END-------" << std::endl;
/*         serverAt(8888)->printMapOptions();
        std::cout << serverAt(8888)->hasPath("sdaf") << "  " << serverAt(8888)->hasPath("/cgi-bin") << " "
                  << serverAt(8888)->hasPath("/asdf") << std::endl;
        serverAt(8888)->printMapLocations(); */
    }
}

bool ConfigFile::isExisting()
{
    if (!(configFile.is_open()))
    {
        std::cerr << "Error opening file" << std::endl;
        return false;
    }
    return true;
}

void ConfigFile::readConfig()
{
    inLocationBlock = false;
    while (std::getline(configFile, line))
    {
        std::istringstream iss(line);
        std::string token;
        iss >> token;

        if (token == "server")
        {
            currentServer = ServerBlock();
            std::cout << "server block opened" << std::endl;
        }
        else if (token == "location")
        {
            currentLocation = LocationBlock();
            inLocationBlock = true;
            iss >> token;
            currentLocationPath = token.c_str();
            currentLocation.path = token;
            std::cout << "location block opened " << currentLocation.path << std::endl;
        }
        else if (token == "}")
        {
            if (inLocationBlock)
            {
                std::cout << "location key is: " << currentLocation.path << std::endl;
                currentServer.locations[currentLocation.path] = currentLocation;

                inLocationBlock = false;
                std::cout << "location block closed" << std::endl;
            }
            else
            {
                std::cout << "server block closed" << std::endl;
                serverBlocks.push_back(currentServer);
            }
        }
        else
        {
            std::string key = token;
            std::string value;
            std::getline(iss, value, ';');
            value = trim(value);
            std::cout << key << "\t\t\t" << value << std::endl;
            if (inLocationBlock)
            {
                currentLocation.options[key] = value;
            }
            else
            {
                currentServer.options[key] = value;
                if (key == "listen")
                {
                    currentServer.socket = std::stoi(value);
                }
            }
        }
    }
    if (!currentServer.options.empty())
    {
    }
}

void ConfigFile::printServerBlocks(const std::deque<ServerBlock> &serverBlocks)
{
    int serverIndex = 1;
    std::cout << "Number of server blocks: " << serverBlocks.size() << std::endl;
    for (const auto &server : serverBlocks)
    {
        std::cout << "Server " << serverIndex++ << ":\n";
        for (const auto &option : server.options)
        {
            std::cout << "\t" << option.first << "\t\t" << option.second << "\n";
        }

        int locationIndex = 1;
        for (const auto &location : server.locations)
        {
            std::cout << " Location " << location.first << ":\n";
            for (const auto &option : location.second.options)
            {
                std::cout << "\t\t" << option.first << "\t\t" << option.second << "\n";
            }
        }
    }
}
/* int main()
{
    ConfigFile configFile("../Configs/config.conf");
} */

std::string ConfigFile::trim(const std::string &str)
{
    auto start = std::find_if_not(str.begin(), str.end(), ::isspace);
    auto end = std::find_if_not(str.rbegin(), str.rend(), ::isspace).base();

    return (start < end) ? std::string(start, end) : std::string();
}

ServerBlock *ConfigFile::serverAt(const int socket)
{
    for (auto &serverBlock : serverBlocks)
    {
        if (serverBlock.socket == socket)
        {
            return &serverBlock;
        }
    }
    return nullptr;
}

std::deque<ServerBlock> ConfigFile::getServers()
{
    return serverBlocks;
}

// for looping through the options of ServerBlock and LocationBlock
template <typename T>
std::string ConfigFile::optionValue(T &block, const std::string &optionName)
{
    std::map<std::string, std::string>::iterator optionsIt = block.options.find(optionName);
    if (optionsIt != block.options.end())
    {
        return optionsIt->second;
    }
    else
    {
        return "";
    }
}

void ConfigFile::populateIpPort()
{
    for (std::deque<ServerBlock>::iterator it = serverBlocks.begin(); it != serverBlocks.end(); ++it)
    {
        std::string temp = optionValue(*it, "host");
        if (temp.empty())
        {
            it->serverIp = "127.0.0.1";
        } else {
            it->serverIp = temp;
        }
        temp = optionValue(*it, "listen");
        if (temp.empty())
        {
            it->port = "66666";
        } else {
            it->port = temp;
        }
        std::cout << "popIpPort " << it->serverIp << ":" << it->port << std::endl;
    }
}