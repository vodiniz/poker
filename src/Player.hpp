#ifndef PLAYER_HPP_
#define PLAYER_HPP_

#include <string>
#include <vector>

#include "Card.hpp"
#include "Table.hpp"
#include "PlayerState.hpp"
#include "HandScore.hpp"

using namespace std;

class Player{
    protected:
        int sock;
        string name;
        int id;
        double money;
        vector<Card> hand;
        PlayerState state;
        Table* currentTable;
        HandScore handscore;


    public:
        Player();
        const string getName() const;
        const int getId() const;

        const double getMoney() const;
        bool setMoney(); // Substituir por uma função que calcula os ganhos poderia ser interessante

        const vector<Card> getHand() const;
        const PlayerState getState() const;
        bool setState();

        bool addHand(Card);
        bool clearHand();

        bool fold();
        bool check();
        bool bet();
        bool call();

        bool calculateHandScore();
        bool sortHand();

};

#endif