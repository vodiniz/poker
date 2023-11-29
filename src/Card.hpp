#ifndef CARD_HPP_
#define CARD_HPP_

#include <iostream>

#include <SuitType.hpp>

using namespace std;

class Card{

    protected:
        char value;
        Suit suit;

    public:
    
        Card(char, Suit);
        virtual ~Card();

        const char getValue() const;
        const Suit getSuit() const;

        friend ostream& operator<<(ostream& os, const Card& card);
};

#endif