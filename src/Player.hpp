#ifndef PLAYER_HPP_
#define PLAYER_HPP_

#include <string>
#include <vector>

#include <Card.hpp>
#include "PlayerState.hpp"

using namespace std;

class Player{
    protected:
        string name;
        int id;
        double money;
        vector<Card> hand;
        PlayerState state;

    public:

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

};

#endif