#ifndef SERVER_HPP_
#define SERVER_HPP_

#include <vector>
#include "Table.hpp"

using namespace std;

class Server{
    protected:
        vector<Table> tables;

        int port;
        int portRange;

        int numThreads;//max tables
        int *socketsThreadsIds;

        int maxTablePlayers;

    public:
        Server(int port, int portRange, int maxTablePlayers = 6, int numThreads = 30);
        virtual ~Server();
        bool connect(void *param);
        bool start();
        bool newTable();

};

typedef struct str_thdata{
    int thread_no;
    int sock;
    static Server* server;
} thdata;


#endif