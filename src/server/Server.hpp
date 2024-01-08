#ifndef SERVER_HPP_
#define SERVER_HPP_

#include <vector>
#include "../poker/Table.hpp"

using namespace std;

class Server{
    protected:
        static vector<Table*> tables;
        static vector<Player*> players;
        int port;
        int portRange;
        char ip[10] = "127.0.0.1";
        int maxTablePlayers;

    public:
        static int totalConnections;
        static bool firstConnection;
        Server(int port, int portRange, int maxTablePlayers = 6);
        virtual ~Server();


        typedef vector<Table*>::iterator TableIterator;
        TableIterator tablesBegin();
        TableIterator tablesEnd();
        int tablesSize();
        Table* tableBack();

        static bool connect(void *param);
        bool start();

        bool checkAvailableTable(Table *);

        static Table* createTable();
        static bool newPlayer(Player* player);

        int totalPlayers();
};


void *tableStart(void*);
void *newPlayerHandle(void*);

#endif