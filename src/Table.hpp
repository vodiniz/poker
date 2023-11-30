#ifndef TABLE_HPP_
#define TABLE_HPP_

#include <vector>

#include "Player.hpp"
#include "Deck.hpp"

using namespace std;

class Table{
    protected:
        Deck deck;
        vector<Card> cards;
        double pot;
        vector<Player> players; // Usar um deck com ponteiros pode ser mais interessante para efeito de lista circular
        Player* smallBinder; //um iterator para esse cara seria interessante para evitar esforço
        double smallBindValue;
        int timer;
    
    public:
        Table();
        virtual ~Table();

        bool addPlayer();
        bool removePlayer();

        bool newRound();
        bool dealCards();

        bool flop();
        bool turn();
        bool river();

        bool showCards();
        bool showWinner();
};

#endif