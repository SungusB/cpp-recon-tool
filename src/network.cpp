#include "network.hpp"

#include <iostream>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <fcntl.h>      
#include <cerrno>       
#include <sys/select.h> 


bool network::checkport(std::string ip, int port, int timeout)
{
    int socketR = socket(AF_INET, SOCK_STREAM, 0);

    if (socketR<0)
    {
        std::cerr << "Socket generation error." << std::endl;
        return false;
    }

    int flags = fcntl(socketR, F_GETFL, 0);
    if(flags == -1)
    {
        close(socketR);
        return false;
    }

    fcntl(socketR, F_SETFL, flags | O_NONBLOCK);

    struct sockaddr_in server_addr;

    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(port);

    if(inet_pton(AF_INET, ip.c_str(), &server_addr.sin_addr) <= 0)
    {
        std::cerr << "Invalid address or unsupported: " << ip << std::endl;
        close(socketR);
        return false;
    }

    int result = connect(socketR, (struct sockaddr*)&server_addr, sizeof(server_addr));

    if (result < 0)
    {
        if(errno == EINPROGRESS)
        {
            fd_set personalset;
            FD_ZERO(&personalset);
            FD_SET(socketR, &personalset);

            struct timeval tv;
            tv.tv_sec = timeout;
            tv.tv_usec = 0;

            int res = select(socketR + 1, NULL, &personalset, NULL, &tv);
            if(res > 0)
            {
                int socketError;
                socklen_t len = sizeof(socketError);
                getsockopt(socketR, SOL_SOCKET, SO_ERROR, &socketError, &len);

                if(socketError == 0)
                {
                    close(socketR);
                    return true;
                }

            }
        }
        close(socketR);
        return false;
    }

    close(socketR);
    return true;
}