#ifndef SUIT_TYPE_HPP
#define SUIT_TYPE_HPP

enum class Suit{
    Diamonds = 1,
    Hearts = 2,
    Clubs = 3,
    Spades = 4
};

std::ostream& operator<<(std::ostream& os, const Suit& suit) {
    switch(suit) {
        case Suit::Diamonds:
            os << "Diamonds";
            break;
        case Suit::Hearts:
            os << "Hearts";
            break;
        case Suit::Clubs:
            os << "Clubs";
            break;
        case Suit::Spades:
            os << "Spades";
            break;
        default:
            // Handle unexpected values
            os.setstate(std::ios_base::failbit);
    }
    return os;
}

#endif