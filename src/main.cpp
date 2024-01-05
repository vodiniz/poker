#include "Server.hpp"

int main(void){

    Server *server = new Server(25555, 10, 30);
    server->start();


    return 0;
}