#include <iostream>
#include <string>
#include <scanner.hpp>

int main(int argc, char* argv[])
{
    if(argc!=5)
    {
        std::cerr << "Input should be: " << argv[0] << " <MODE> <IP_ADDRESS> <START_PORT> <END_PORT>" << std::endl;
        return 1;
    }

    std::string ipAdress = argv[2];
    std::string mode = argv[1];
    int startPort = std::stoi(argv[3]);
    int endPort = std::stoi(argv[4]);

    scanner scan;

    if(mode == "s")
    {
        std::cout << "Slow scan starting;" << std::endl;
        
        scan.run(ipAdress, startPort, endPort, 0);
    }

    else if(mode == "f")
    {
        std::cout << "Fast scan starting;" << std::endl;

        scan.run(ipAdress, startPort, endPort, 1);
    }

    else
    {
        std::cerr << "Input mode shoud be s(slow) or f(fast)" << std::endl;
        return 1;
    }

    return 0;
}