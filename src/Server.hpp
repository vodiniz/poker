#ifndef SERVER_HPP_
#define SERVER_HPP_

#include <vector>
#include "Table.hpp"

using namespace std;

class Server{
    protected:
        vector<Table> tables;
        int maxPlayers;

        int port;
        int portRange;

        int numThreads = 30;
        int *socketsThreadsIds;

    public:
        bool connect();
        bool start();

};

typedef struct str_thdata{
    int thread_no;
    int sock;
} thdata;


#endif