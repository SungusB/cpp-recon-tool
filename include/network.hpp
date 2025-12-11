#ifndef NETWORK_HPP
#define NETWORK_HPP

#include <string>

class network
{
    public:
        bool checkport(std::string ip, int port, int timeout);  
};

#endif