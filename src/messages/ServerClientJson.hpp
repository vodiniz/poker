#ifndef SERVER_CLIENT_JSON_HPP
#define SERVER_CLIENT_JSON_HPP

#include <string>
#include "../jsonMapping/json_struct.h"
#include "../poker/PlayerState.hpp"
using namespace std;
//Classe que vai fazer a conversão de JSON para minha estrutura de comando.


struct ServerClientJson{
    int newMoneyValue;
    double currentTableBet;
    double playerMoneyOnTable;
    int playerState;

    JS_OBJ(newMoneyValue, currentTableBet, playerMoneyOnTable, playerState);
};


#endif


