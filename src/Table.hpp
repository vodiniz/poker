#ifndef TABLE_HPP_
#define TABLE_HPP_

#include <vector>

#include "Player.hpp"
#include "Deck.hpp"

using namespace std;

class Table{
    protected:
        Deck deck;
        vector<Card*> cards;
        vector<Player*> players; // Usar um deck com ponteiros pode ser mais interessante para efeito de lista circular
        double pot;
        Player* smallBinder; 
        double smallBindValue;
        int timer;
        int thread_no;
        int sock;
    
    public:
        Table(int thread_no, int sock);
        virtual ~Table();

        typedef vector<Card*>::iterator CardIterator;
        CardIterator cardBegin();
        CardIterator cardEnd();
        const int cardSize() const;
        Card* cardBack();

        typedef vector<Player*>::iterator PlayerIterator;
        PlayerIterator playersBegin();
        PlayerIterator playersEnd();
        const int playersSize() const;
        Player* playersBack();

        const double getPot() const;

        //loop principal da mesa, e esperando conexões;
        //mutex para controle de acesso de região crítica
        bool start(pthread_mutex_t mutex);

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