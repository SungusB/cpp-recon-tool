#include "scanner.hpp"
#include "network.hpp" 
#include <iostream>
#include "threadpool.hpp" 
#include <mutex>

std::mutex printMtx;

scanner::scanner()
{}

void scanner::run(std::string target, int startPort, int endPort, int mode)
{
    network net; 

    if (mode == 0) 
    {
        std::cout << "--- Starting Slow scan on " << target << " ---" << std::endl;
        
        bool noPorts = true;

        for(int i = startPort; i <= endPort; i++)
        {
            bool isOpen = net.checkport(target, i, 2);

            if (isOpen)
            {
                std::cout << "Port " << i <<" Status: Open" << std::endl;
                noPorts = false;
            }
            
        }
        if (noPorts)
        {
            std::cout << "No ports are open" << std::endl;
        }
    }
    else if (mode == 1) 
    {
        std::cout << "--- Starting FAST Scan (50 threads) on " << target << " ---" << std::endl;

        threadpool pool(50);

        int timeout = 1;

        for(int i=startPort; i<= endPort; i++)
        {
            pool.enqueue([target, i, timeout]()
            {
                network localNet;

                bool isOpen = localNet.checkport(target,i,timeout);

                if(isOpen)
                {
                    std::lock_guard<std::mutex> lock(printMtx);
                    std::cout << "Port " << i << " Status: Open" << std::endl;
                }
            }
            
            );

        }
    }
}