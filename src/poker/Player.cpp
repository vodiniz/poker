#include "Player.hpp"

Player::Player() : sock(), name(""), id(0), money(1000), moneyOnTable(0), state(PlayerState::WaitingBet){}

Player::Player(string name, int sock, int id){
    this->sock = sock;
    this->name = name;
    this->id = id;
    this->money = 1000;
    this->moneyOnTable = 0;
    this->state = PlayerState::WaitingBet;
}

bool Player::setName(string name){
    this->name = name;

    return this->name == name;   
}

const string Player::getName() const{
    return name;
}

const int Player::getId() const{
    return id;
}

bool Player::setId(int id){
    this->id = id;
    
    return this->id == id;
        
}

const float Player::getMoneyOnTable() const{
    return moneyOnTable;
}

bool Player::setMoneyOnTable(float moneyOnTable){
    this->moneyOnTable = moneyOnTable;

    return this->moneyOnTable == moneyOnTable;
}


bool Player::setSock(int sock){
    this->sock = sock;
    return this->sock == sock;
}

const int Player::getSock() const{
    return sock;
}

const double Player::getMoney() const{
    return money;
}

bool Player::setMoney(double value){
    money = value;

    if(money != value)
        return false;

    return true;
}

Player::HandIterator Player::handBegin(){
    return hand.begin();
}
Player::HandIterator Player::handEnd(){
    return hand.end();
}

bool Player::setState(PlayerState stateEnum){
    state = stateEnum;
    return true;
}

const PlayerState Player::getState() const{
    return this->state;
}


bool Player::addHand(Card *card){
    hand.push_back(card);
    //NÃO TÁ LEGAL ESSE RETURN TRUE AQUI NÃO
    return true;
}

bool Player::clearHand(){
    hand.clear();

    return hand.empty();
}

bool Player::sortHand(){
    return false;
}
