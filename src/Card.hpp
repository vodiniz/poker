#ifndef CARD_HPP_
#define CARD_HPP_

#include <iostream>

#include "CardValue.hpp"
#include "SuitType.hpp"

using namespace std;

class Card{

    protected:
        CardValue value;
        Suit suit;

    public:
    
        Card(CardValue, Suit);
        virtual ~Card();

        const CardValue getValue() const;
        const Suit getSuit() const;

        bool operator ==(const Card &card);
        friend ostream& operator<<(ostream& os, const Card& card);
};

#endif