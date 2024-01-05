#ifndef HANDSCORE_HPP_
#define HANDSCORE_HPP_

enum class HandScore{
    high_card = 0,
    one_pair,
    two_pair,
    three_of_a_kind,
    straight,
    flush,
    full_house,
    four_of_a_kind,
    straight_flush,
    royal_flush,
};

std::ostream& operator<<(std::ostream& os, const HandScore& handScore) {
    switch(handScore) {
        case HandScore::high_card:
            os << "High Card";
            break;
        case HandScore::one_pair:
            os << "One Pair";
            break;
        case HandScore::two_pair:
            os << "Two Pair";
            break;
        case HandScore::three_of_a_kind:
            os << "Three of a Kind";
            break;
        case HandScore::straight:
            os << "Straight";
            break;
        case HandScore::flush:
            os << "Flush";
            break;
        case HandScore::full_house:
            os << "Full House";
            break;
        case HandScore::four_of_a_kind:
            os << "Four of a Kind";
            break;
        case HandScore::straight_flush:
            os << "Straight Flush";
            break;
        case HandScore::royal_flush:
            os << "Royal Flush";
            break;
        default:
            // Handle unexpected values
            os.setstate(std::ios_base::failbit);
    }
    return os;
}


#endif