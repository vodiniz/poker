#include "Table.hpp"
#include <sys/socket.h>
#include <pthread.h>    /* POSIX Threads */ 
#include <sys/types.h>    // AF_INET, SOCK_STREAM
#include "../messages/ServerClientJson.hpp"
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
    int waitingBetPlayers = 0;
    for(auto element : players){
        if(element->getState() == PlayerState::WaitingBet)
            waitingBetPlayers++;
    }

    return waitingBetPlayers == 0;
}

bool Table::start(pthread_mutex_t *mutex){

    char buffer[1024];



    int contador = 0;


    while(true){

        if(playersSize() == 0 && getFirstConnection())
            break;
        
        sleep(5);
        


        if(!this->endRound())
            continue;

        


        while(true){

            if(!this->endRound())
                continue;

            for(auto currentPlayer : players){

                currentPlayer->setState(PlayerState::WaitingBet);

                ServerClientJson serverJson;
                serverJson.newMoneyValue = 10000;
                serverJson.currentTableBet = 1000;
                serverJson.playerMoneyOnTable = 500;
                serverJson.playerState = 0;
                std::string pretty_json = JS::serializeStruct(serverJson);

                send(currentPlayer->getSock(), pretty_json.c_str(), sizeof(pretty_json.c_str()), 0);
                recv(currentPlayer->getSock(), buffer, sizeof(buffer), 0);
                
                cout << buffer << endl;
            }
        }

            
           
    }

    return true;
}

const bool Table::getFirstConnection() const{
    return firstConnection;
}
