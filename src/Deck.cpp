#include <algorithm>
#include <random>
#include "Deck.hpp"


using namespace std;

Deck::Deck(){

    constexpr CardValue allCardValues[] = {
        CardValue::TWO,
        CardValue::THREE,
        CardValue::FOUR,
        CardValue::FIVE,
        CardValue::SIX,
        CardValue::SEVEN,
        CardValue::EIGHT,
        CardValue::NINE,
        CardValue::TEN,
        CardValue::JACK,
        CardValue::QUEEN,
        CardValue::KING,
        CardValue::ACE
    };

    constexpr Suit allSuitTypes[] = {
        Suit::Diamonds,
        Suit::Hearts,
        Suit::Clubs,
        Suit::Spades
    };


    for (Suit currentSuit:  allSuitTypes){
        for(CardValue currentValue: allCardValues){
            addDeckCard(new Card(currentValue, currentSuit));
        }
    }
}

Deck::~Deck(){
    for(DeckIterator it = deckBegin(); it < deckEnd(); it++){
        delete *it;
    }
    for(DrawedCardsIterator it = drawedCardsBegin(); it < drawedCardsEnd(); it++){
        delete *it;
    }
}

bool Deck::addDeckCard(Card* card){
    this->deck.push_back(card);

    if(deck.back() == card)
        return true;

    else
        return false;
}

bool Deck::removeDeckCard(Card* card){
    remove(deckBegin(), deckEnd(), card);
    //ta muito legal esse return true não.
    return true;
}

bool Deck::addDrawedCard(Card* card){
    this->drawedCards.push_back(card);

    if(drawedCards.back() == card)
        return true;

    else
        return false;
}

bool Deck::removeDrawedCard(Card* card){
    remove(drawedCardsBegin(), drawedCardsEnd(), card);
    //ta muito legal esse return true não.
    return true;
}

Deck::DeckIterator Deck::deckBegin(){
    return deck.begin();
}


Deck::DeckIterator Deck::deckEnd(){
    return deck.end();
}

int Deck::deckSize(){
    return deck.size();
}

Deck::DrawedCardsIterator Deck::drawedCardsBegin(){
    return drawedCards.begin();
}

Deck::DrawedCardsIterator Deck::drawedCardsEnd(){
    return drawedCards.end();
}

int Deck::drawedCardsSize(){
    return drawedCards.size();
}

bool Deck::shuffle(){

    auto rd = std::random_device {}; 
    auto rng = std::default_random_engine {rd()};
    
    std::shuffle(deck.begin(), deck.end(), rng);

    return true;
}

bool Deck::resetDeck(){
    for(DrawedCardsIterator it = drawedCardsBegin(); it < drawedCardsEnd(); it++){
        addDeckCard(*it);
        removeDrawedCard(*it);
    }

    if (deckSize() == 52 && drawedCardsSize() == 0)
        return true;
    return false;
}

bool Deck::drawCard(){
    int deck_size = deckSize();
    int drawed_size = drawedCardsSize();

    if(deck_size == 0)
        return false;

    Card* card = *(deckBegin());
    addDrawedCard(card);
    removeDeckCard(card);

    if(deckSize() == deck_size + 1 && drawed_size + 1== drawedCardsSize())
        return true;
    
    return false;
}
