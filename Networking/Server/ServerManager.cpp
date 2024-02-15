#include "ServerManager.hpp"


ServerManager::ServerManager(const std::string configFile) {
    ConfigFile config(configFile);

    for (int i = 0; i < config.serverCount; ++i)
    {
        servers.emplace_back(config.serverBlocks[i].serverIp, std::stoi(config.serverBlocks[i].port));
        pollfd temp = {servers.back().get_socket()->get_sock(), POLLIN, 0};
        fds.push_back(temp);
    }
    launch();
}

void ServerManager::launch() {

    while (true)
    {
        int num_ready = poll(fds.data(), fds.size(), -1);

        if (num_ready == -1)
        {
            perror("poll");
            break;
        }

        for (size_t i = 0; i < fds.size(); ++i)
        {
            if (fds[i].revents & POLLIN)
            {
                std::vector<NTW::Server>::iterator it;
                for (it = servers.begin(); it != servers.end(); ++it) {
					if (fds[i].fd == it->get_socket()->get_sock()) {
                        it->launch();
                    }
                }
            }
        }
    }
}