#ifdef CLIENT_HPP
#define CLIENT_HPP

#include <stdio.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <string.h>
#include <pthread.h>    /* POSIX Threads */ 
#include <stdlib.h>

#include <fcntl.h> // for open
#include <unistd.h> // for close
#include <arpa/inet.h>    // htons(), inet_addr()
#include <sys/types.h>    // AF_INET, SOCK_STREAM

#include "../poker/GameState.hpp"
#include "../Player.hpp"
using namespace std;

class Client{
protected:
    int sock;
    int thread;
    GameState gameState;
    Player player;    
public:

};



#endif