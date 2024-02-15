#include "./Networking/Server/Server.hpp"
#include <poll.h>

int main()
{
    NTW::Server server1("127.0.0.1", 9898);
    NTW::Server server2("192.168.178.25", 8099);

    std::vector<pollfd> fds;

    pollfd test1 = {server1.get_socket()->get_sock(), POLLIN, 0};
    pollfd test2 = {server2.get_socket()->get_sock(), POLLIN, 0};

    fds.push_back(test1);
    fds.push_back(test2);

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
                if (fds[i].fd == server1.get_socket()->get_sock())
                {
                    server1.launch();
                }
                else if (fds[i].fd == server2.get_socket()->get_sock())
                {
                    std::cout << "server2 about to launch()" << std::endl;
                    server2.launch();
                }
            }
        }
    }
    return 0;
}