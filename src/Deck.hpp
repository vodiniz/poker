#ifndef DECK_HPP_
#define DECK_HPP_

#include "Card.hpp"
#include <vector>

using namespace std;

class Deck{

    protected:
        vector<Card> baseCards;
        vector<Card> currentCards;

    public:
        Deck();
        virtual ~Deck();

        bool shuffle();
        bool reset();

        bool removeTop();
};

#endif