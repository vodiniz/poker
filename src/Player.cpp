#include "Player.hpp"


Player::Player(){
    //BRUNO 
    // AQUI DENTRO EU TENHO ALGUMAS OPÇÕES DE COMO FAZER ESSE CONSTRUTOR.
    // PODERIAMOS RECEBER A STRING DO BUFFER DE COMUNICAÇÃO,
    // PODERIAMOS RECEBER O JSON QUE JÁ FOI CONVERTIDO PELA FUNÇÃO DE ADICIONAR PLAYER NO SERVER
    // OU SÓ OS PARÂMETROS JÁ TRATADOS. TODAS OPÇÕES SÃO VÁLIDAS E NÃO TENHO IDEIA DE QUAL A MELHOR
    // QUAL SUA OPINIÃO?

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
