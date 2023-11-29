#ifndef SERVER_HPP_
#define SERVER_HPP_

#include <vector>
#include "Table.hpp"

using namespace std;

class Server{
    protected:
        vector<Table> tables;
        int MaxPlayers;
        int port;
};

#endif