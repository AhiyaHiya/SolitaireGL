#pragma once

#include <glm/glm.hpp>

#include <vector>

struct Card
{
    enum class Suit
    {
        Hearts,
        Diamonds,
        Clubs,
        Spades
    };

    enum class Rank
    {
        Ace = 1,
        Two,
        Three,
        Four,
        Five,
        Six,
        Seven,
        Eight,
        Nine,
        Ten,
        Jack,
        Queen,
        King
    };

    Suit      suit;
    Rank      rank;
    bool      face_up;
    glm::vec2 screen_position;
};

auto init_card_deck() -> std::vector< Card >;
void shuffle_deck(std::vector< Card >& deck);
