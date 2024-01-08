#include "Player.hpp"

Player::Player(string name, int sock, int id){
    this->sock = sock;
    this->name = name;
    this->id = id;
    this->money = 1000;
    this->state = PlayerState::Fold;
}

const string Player::getName() const{
    return name;
}

const int Player::getId() const{
    return id;
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
