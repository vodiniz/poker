#include "Table.hpp"


const double Table::getPot() const{
    return pot;
}

const int Table::tableCardsSize() const{
    return tableCards.size();
}

Table::TableCardsIterator Table::tableCardsBegin(){
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
    return thread;
}

bool Table::addPlayer(Player *player){
    int players_size = playersSize();

    players.push_back(player);

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
}

bool Table::dealCards(){
    for(PlayerIterator playerIt = playersBegin(); playerIt < playersEnd(); playerIt++){
        for(int i = 0; i < 2; i++)
            (*playerIt)->addHand(deck.drawCard());
    }
}