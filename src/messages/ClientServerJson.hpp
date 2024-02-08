#ifndef CLIENT_SERVER_JSON_HPP
#define CLIENT_SERVER_JSON_HPP


#include <string>
#include "../jsonMapping/json_struct.h"


using namespace std;

//Classe que vai fazer a conversão de JSON para minha estrutura de comando.


struct ClientServerJson{
    int newMoneyValue;
    double playerMoneyOnTable;
    int playerState;
    JS_OBJ(playerMoneyOnTable, newMoneyValue, playerState);

};

//algo como 

/* 
{
    "playerID": "54523",
    "command": "fold",
    "value": "0"
}
*/

#endif