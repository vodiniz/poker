#ifndef TABLE_HPP_
#define TABLE_HPP_

#include <vector>
#include <pthread.h>

#include "Player.hpp"
#include "Deck.hpp"
#define SMALLBINDVALUE 500
#define TIMER 30

using namespace std;

class Table{
    protected:
        pthread_t thread;
        pthread_mutex_t *mutex;
        Deck deck;
        vector<Card*> tableCards;
        vector<Player*> players; // Usar um deck com ponteiros pode ser mais interessante para efeito de lista circular
        double pot;
        Player* smallBinder; 
        double smallBindValue;
        int timer;
    


    public:
        Table(pthread_mutex_t *mutex);
        virtual ~Table();

        typedef vector<Card*>::iterator TableCardsIterator;
        TableCardsIterator tableCardsBegin();
        TableCardsIterator tablecardsEnd();
        const int tableCardsSize() const;

        typedef vector<Player*>::iterator PlayerIterator;
        PlayerIterator playersBegin();
        PlayerIterator playersEnd();
        const int playersSize() const;
        Player* playersBack();

        Player* untie(Player *player1, Player *player2);
        
        const double getPot() const;

        //loop principal da mesa, e esperando conexões;
        //mutex para controle de acesso de região crítica
        bool start(pthread_mutex_t *mutex);

        pthread_t* getThread();

        bool addPlayer(Player *player);
        bool removePlayer(Player*);

        bool newRound();
        bool dealCards();

        bool preFlop();
        bool flop();
        bool turn();
        bool river();

        bool showCards();
        bool showWinner();

};

#endif