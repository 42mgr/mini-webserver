#pragma once

#include "../../webserver.hpp"
#include "../../Parser/ConfigFile.hpp"


class ServerManager {
	public:
      void launch();
      ServerManager(const std::string configFile);
	private:
      std::vector<NTW::Server> servers;
      std::vector<pollfd> fds;
};