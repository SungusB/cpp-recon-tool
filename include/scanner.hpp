#ifndef SCANNER_HPP
#define SCANNER_HPP

#include <string>

class scanner
{
    public:
        scanner();

        void run(std::string target, int startPort, int endPort, int mode);
};

#endif