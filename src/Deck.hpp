#ifndef DECK_HPP_
#define DECK_HPP_

#include "Card.hpp"
#include <vector>

using namespace std;

class Deck{

    protected:
        vector<Card*> deck;
        vector<Card*> drawedCards;

    public:
        Deck();
        virtual ~Deck();

        bool addDeckCard(Card*);
        bool removeDeckCard(Card*);

        bool addDrawedCard(Card*);
        bool removeDrawedCard(Card*);

        typedef vector<Card*>::iterator DeckIterator;
        DeckIterator deckBegin();
        DeckIterator deckEnd();
        int deckSize();

        typedef vector<Card*>::iterator DrawedCardsIterator;
        DrawedCardsIterator drawedCardsBegin();
        DrawedCardsIterator drawedCardsEnd();
        int drawedCardsSize();



        bool shuffle();
        bool resetDeck();

        bool drawCard();

};

#endif