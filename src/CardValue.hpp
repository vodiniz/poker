#ifndef CARDVALUE_HPP_
#define CARDVALUE_HPP_

#include <string>


enum class CardValue{
    TWO = 2,
    THREE = 3,
    FOUR = 4,
    FIVE = 5,
    SIX = 6,
    SEVEN = 7,
    EIGHT  = 8,
    NINE = 9,
    TEN = 10,
    JACK = 11,
    QUEEN = 12,
    KING = 13,
    ACE = 1
};

std::ostream& operator<<(std::ostream& os, const CardValue& cardValue) {
    switch(cardValue) {
        case CardValue::TWO:
        case CardValue::THREE:
        case CardValue::FOUR:
        case CardValue::FIVE:
        case CardValue::SIX:
        case CardValue::SEVEN:
        case CardValue::EIGHT:
        case CardValue::NINE:
        case CardValue::TEN:
            os << static_cast<char>(cardValue);
            break;
        case CardValue::JACK:
            os << "J";
            break; 
        case CardValue::QUEEN:
            os << "Q";
            break; 
        case CardValue::KING:
            os << "K";
            break; 
        case CardValue::ACE:
            os << "A";
            break; 
        default:
            os.setstate(std::ios_base::failbit);
            break;
    }
    return os;
}

#endif