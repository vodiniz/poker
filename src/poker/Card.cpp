#include <iostream>

#include "Card.hpp"

using namespace std;

Card::Card(CardValue value, Suit suit):
    value(value), suit(suit){}

Card::~Card(){}

const CardValue Card::getValue() const{
    return value;
}

const Suit Card::getSuit() const{
    return suit;
}

bool Card::operator==(const Card &card){

    if (this->suit == card.getSuit() && this->value == card.getValue())
        return true;
    return false;
}

bool Card::operator<(const Card &card){
    
    if(static_cast<int>(this->getSuit()) < static_cast<int>(card.getSuit()))
        return true;
    else if(static_cast<int>(this->getSuit()) > static_cast<int>(card.getSuit()))
        return false;
    else{
        if(static_cast<int>(this->getValue()) < static_cast<int>(card.getValue()))
            return true;
        else
            return false;
    }

    return false;
}

bool Card::operator>(const Card &card){
    
    if(static_cast<int>(this->getSuit()) > static_cast<int>(card.getSuit()))
        return true;
    else if(static_cast<int>(this->getSuit()) < static_cast<int>(card.getSuit()))
        return false;
    else{
        if(static_cast<int>(this->getValue()) > static_cast<int>(card.getValue()))
            return true;
        else
            return false;
    }

    return false;
}

ostream &operator<<(ostream &os, const Card &card){

    // os << card.getValue() << "of" << card.getSuit();

    return os;
}
