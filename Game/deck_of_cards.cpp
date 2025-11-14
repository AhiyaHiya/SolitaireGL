#include "deck_of_cards.hpp"

auto init_card_deck() -> std::vector< Card >
{
    constexpr auto total_cards = 52;
    constexpr auto suits       = 4;
    constexpr auto ranks       = 13;

    auto deck = std::vector< Card >{};
    deck.resize(total_cards);
    for (auto suit = 0; suit < suits; ++suit)
    {
        for (auto rank = 1; rank <= ranks; ++rank)
        {
            auto card = Card{.suit            = static_cast< Card::Suit >(suit),
                             .rank            = static_cast< Card::Rank >(rank),
                             .face_up         = false,
                             .screen_position = glm::vec2(0.0f, 0.0f)};
            deck.push_back(card); // Add card to the deck
        }
    }
    return deck;
}

void shuffle_deck(std::vector< Card >& deck)
{
    // Simple Fisher-Yates shuffle
    for (auto i = deck.size() - 1; i > 0; --i)
    {
        const auto j = static_cast< std::size_t >(rand()) % (i + 1);
        std::swap(deck[i], deck[j]);
    }
}
