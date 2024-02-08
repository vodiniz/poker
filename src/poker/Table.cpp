#include "Table.hpp"
#include <sys/socket.h>
#include <pthread.h>    /* POSIX Threads */ 
#include <sys/types.h>    // AF_INET, SOCK_STREAM
#include "../messages/ServerClientJson.hpp"
#include "../messages/ClientServerJson.hpp"


#include "unistd.h"


using namespace std;

const double Table::getPot() const{
    return pot;
}

const int Table::tableCardsSize() const{
    return tableCards.size();
}

Table::Table(pthread_mutex_t *mutex){
    this->mutex = mutex;

    this->pot = 0;
    this->deck = Deck();
    this->smallBindValue = SMALLBINDVALUE;
    this->timer = 30;
    this->firstConnection = false;

}

Table::~Table(){}

const double Table::getCurrentBet() const{
    return this->currentBet;
}

bool Table::setCurrentBet(double currentBet){
    this->currentBet = currentBet;

    return this->currentBet == currentBet;
}

Table::TableCardsIterator Table::tableCardsBegin()
{
    return tableCards.begin();
}

Table::TableCardsIterator Table::tablecardsEnd(){
    return tableCards.end();
}


Table::PlayerIterator Table::playersBegin(){
    return players.begin();
}

Table::PlayerIterator Table::playersEnd(){
    return players.end();
}

const int Table::playersSize() const{
    return players.size();
}

Player* Table::playersBack(){
    return players.back();
}


pthread_t* Table::getThread(){
    return &thread;
}

bool Table::addPlayer(Player *player){
    int players_size = playersSize();

    players.push_back(player);

    firstConnection = true;
    
    return playersSize() > players_size;
}

bool Table::removePlayer(Player *player){

    if(playersSize() == 0)
        return false;

    for(PlayerIterator it = playersBegin(); it < players.end(); it++){
        if(player == *it){
            players.erase(it);
            return true;
        }
    }

    return false;

}

bool Table::newRound(){
    for(PlayerIterator playerIt = playersBegin(); playerIt < playersEnd(); playerIt++){
        (*playerIt)->clearHand();
    }
    return true;
}

bool Table::dealCards(){
    for(PlayerIterator playerIt = playersBegin(); playerIt < playersEnd(); playerIt++){
        for(int i = 0; i < 2; i++)
            (*playerIt)->addHand(deck.drawCard());
    }
    return true;
}

bool Table::endRound(){

    int InPlayers = 0;
    for(auto element : players){
        if(element->getState() == PlayerState::In)
            InPlayers++; 
    }

    cout << "inPlayers: " << InPlayers << " playerssize" << playersSize() << endl;
    return InPlayers == playersSize();
}

bool Table::start(pthread_mutex_t *mutex){

    char buffer[2048];

    

    // serverJson.newMoneyValue = 10000;
    // serverJson.currentTableBet = 1000;
    // serverJson.playerMoneyOnTable = 500;
    // serverJson.playerState = 0;

    int contador = 1;

    while(true){

        if(playersSize() == 0 && getFirstConnection())
            break;

        sleep(5);

        cout << "-----------ROUND " << contador << " ---------------" << endl;  

        while(true){


            if(this->endRound())
                break;

            int contador = 0;

            for(auto currentPlayer : players){

                cout << "Vez do jogador: " << currentPlayer->getName() << " Com state: " << static_cast<int>(currentPlayer->getState()) << endl;

                

                currentPlayer->setState(PlayerState::WaitingBet);

                ServerClientJson serverJson;
                
                serverJson.newMoneyValue = currentPlayer->getMoney();
                serverJson.playerMoneyOnTable = currentPlayer->getMoneyOnTable();
                serverJson.playerState = static_cast<int>(currentPlayer->getState());
                serverJson.currentTableBet = this->getCurrentBet();

                std::string pretty_client_json = JS::serializeStruct(serverJson);

                cout << "Enviando json para o client:\n" << pretty_client_json.c_str() << endl;

                send(currentPlayer->getSock(), pretty_client_json.c_str(), sizeof(pretty_client_json.c_str()), 0);
                recv(currentPlayer->getSock(), (void*)pretty_client_json.c_str(), sizeof((void*)pretty_client_json.c_str()), 0);
                

                cout<< "Buffer:\n" << (void*)pretty_client_json.c_str() << endl;
                cout<< "Buffer2:\n" << pretty_client_json.c_str() << endl;

                
                //usando parser para preencher a struct
                JS::ParseContext context(buffer);
                ClientServerJson jsonTeste;
                context.parseTo(jsonTeste);

                cout << "JsonTeste:\n" << (string) JS::serializeStruct(jsonTeste) << endl;

                

                currentPlayer->setMoney(serverJson.newMoneyValue);
                
                //if(serverJson.currentTableBet > this->getCurrentBet())
                //    this->setCurrentBet(serverJson.playerMoneyOnTable);

                currentPlayer->setMoneyOnTable(serverJson.playerMoneyOnTable);
                
                std::string pretty_json = JS::serializeStruct(serverJson);
                cout << "Recebi o serverJson: " << pretty_json << endl;
                

                switch (serverJson.playerState)
                {
                case 0:
                    for(auto elem : players){
                        cout << "TESTEEEEEEEEEEEEEEEEEEEEE" << endl;
                        if(elem->getState() != PlayerState::Fold)
                            elem->setState(PlayerState::WaitingPlayers);
                    }
                        currentPlayer->setState(PlayerState::In);
                    break;
                case 2:
                    currentPlayer->setState(PlayerState::Fold);
                    break;
                
                case 3:
                    currentPlayer->setState(PlayerState::In);
                    cout << "Switch case 3" << endl;
                    break;
                
                case 4:
                    auto it = players.begin() + contador;
                    players.erase(it);
                    break;
                }

                

                
                
                cout << "terminou a vez do jogador " << currentPlayer->getName() << endl;

            }

        }

            
            cout << "calcula pontuação" << endl;
            cout << "------------Fim do round " << contador << " -------------" << endl;
            contador++;

           
    }

    return true;
}

const bool Table::getFirstConnection() const{
    return firstConnection;
}
