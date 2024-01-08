#ifndef PLAYER_HPP_
#define PLAYER_HPP_

#include <string>
#include <vector>

#include "Card.hpp"
#include "PlayerState.hpp"
#include "HandScore.hpp"

using namespace std;

class Player{
    protected:
        int sock;
        string name;
        int id;
        double money;
        vector<Card*> hand; //MÃO DE 7 CARTAS COM AS CARTAS DA MESA
        PlayerState state;
        HandScore handscore;


    public:
        Player(string name);
        const string getName() const;
        const int getId() const;
        const int getSock() const;

        const double getMoney() const;
        bool setMoney(double value); // Substituir por uma função que calcula os ganhos poderia ser interessante

        typedef vector<Card*>::iterator HandIterator;
        HandIterator handBegin();
        HandIterator handEnd();
        bool clearHand();

        const PlayerState getState() const;
        bool setState(PlayerState);

        bool addHand(Card*);

        bool fold();
        bool check();
        bool bet();
        bool call();

        bool calculateHandScore();
        bool sortHand();

};

#endif