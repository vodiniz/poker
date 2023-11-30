#ifndef SERVER_HPP_
#define SERVER_HPP_

#include <vector>
#include "Table.hpp"

using namespace std;

class Server{
    protected:
        vector<Table*> tables;

        int port;
        int portRange;

        int *socketsThreadsIds;
        int maxTablePlayers;

    public:
        Server(int port, int portRange, int maxTablePlayers = 6);
        virtual ~Server();


        typedef vector<Table*>::iterator TableIterator;
        TableIterator tablesBegin();
        TableIterator tablesEnd();
        const int tablesSize() const;
        Table* tableBack();

        static bool connect(void *param);
        bool start();

        Table* createTable(void *param);
        bool newPlayer();

        int totalPlayers();


};

typedef struct str_thdata{
    int thread_no;
    int sock;
    Table* table;
} thdata;


void *conexao(void*);
void *newPlayerHandle(void*);

#endif