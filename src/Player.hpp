#ifndef PLAYER_HPP_
#define PLAYER_HPP_

#include <string>
#include <vector>

#include "Table.hpp"
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
        vector<Card*> hand;
        PlayerState state;
        //BRUNO 
        // DEPENDENCIA CIRCULAR SE COLOCAR TABLE AQUI
        //EU ACHEI QUE SERIA BOM SABER EM QUAL MESA A PESSOA ESTÁ
        // MAS DÁ PRA FAZER UMA BUSCA BEM FÁCIL PELO ID ENTÃO ACHO QUE NÃO TEM TANTO
        //PROBLEMA NÃO DEIXAR ESSE PONTEIRO AQUI
        
        // Table *currentTable;
        HandScore handscore;


    public:
        Player();
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
        bool clearHand();

        bool fold();
        bool check();
        bool bet();
        bool call();

        bool calculateHandScore();
        bool sortHand();

};

#endif