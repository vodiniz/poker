#ifndef SERVER_CLIENT_JSON_HPP
#define SERVER_CLIENT_JSON_HPP

#include <string>
#include "../jsonMapping/json_struct.h"
#include "../poker/PlayerState.hpp"
using namespace std;
//Classe que vai fazer a conversão de JSON para minha estrutura de comando.


struct ServerClientJson{
    string command;
    int newMoneyValue;
    double currentTableBet;
    double playerMoneyOnTable;
    int playerState;
    string tableCards;

    JS_OBJ(command, newMoneyValue, currentTableBet, playerMoneyOnTable, playerState, tableCards);
};


#endif


