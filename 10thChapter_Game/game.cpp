/*
 * game.cpp
 *
 *  Created on: 28 окт. 2022 г.
 *      Author: Omineva
 */

#include <algorithm> // std::shuffle
#include <array>
#include <ctime>
#include <iostream>
#include <random>

namespace Cards {

	enum Ranks{
		rank2,
		rank3,
		rank4,
		rank5,
		rank6,
		rank7,
		rank8,
		rank9,
		rank10,
		rankJack,
		rankQueen,
		rankKing,
		rankAce,

		all_ranks
	};

	enum Suits {
		clubs,
		diamonds,
		hearts,
		spades,

		all_suits
	};

	const int numberOfCards = 52;
}

struct Card {

	Cards::Ranks rank;
	Cards::Suits suit;
};

void printCard(const Card& card) {

	switch(card.rank) {
	case Cards::rank2:
		printf("2");
		break;
	case Cards::rank3:
		printf("3");
		break;
	case Cards::rank4:
		printf("4");
		break;
	case Cards::rank5:
		printf("5");
		break;
	case Cards::rank6:
		printf("6");
		break;
	case Cards::rank7:
		printf("7");
		break;
	case Cards::rank8:
		printf("8");
		break;
	case Cards::rank9:
		printf("9");
		break;
	case Cards::rank10:
		printf("10");
		break;
	case Cards::rankJack:
		printf("J");
		break;
	case Cards::rankQueen:
		printf("Q");
		break;
	case Cards::rankKing:
		printf("K");
		break;
	case Cards::rankAce:
		printf("A");
		break;
	default:
		printf("?");
		break;
	}

	switch(card.suit) {
	case Cards::clubs:
		printf("C");
		break;
	case Cards::diamonds:
		printf("D");
		break;
	case Cards::hearts:
		printf("H");
		break;
	case Cards::spades:
		printf("S");
		break;
	default:
		printf("?");
		break;
	}
}

void createDeck(std::array<Card,Cards::numberOfCards>& deck) {

	int counter = 0;
	for (int i = 0; i < Cards::all_suits; ++i) {
		for (int j = 0; j < Cards::all_ranks; ++j) {
			deck[counter].rank = static_cast<Cards::Ranks>(j);
			deck[counter].suit = static_cast<Cards::Suits>(i);
			++counter;
		}
	}
}

void printDeck(std::array<Card,Cards::numberOfCards>& deck) {

	int counter = 0;
	for (Card i: deck) {
		printCard(i);
		++counter;
		(counter%13 == 0) ? printf(" \n") : printf(" ");
	}
}

void shuffleDeck(std::array<Card,Cards::numberOfCards>& deck) {

	std::mt19937 mt{ static_cast<std::mt19937::result_type>(std::time(nullptr)) };
	std::shuffle(deck.begin(), deck.end(), mt);
}

int getCardValue(Card& card) {

	switch(card.rank) {
	case Cards::rank2:
		return 2;
	case Cards::rank3:
		return 3;
	case Cards::rank4:
		return 4;
	case Cards::rank5:
		return 5;
	case Cards::rank6:
		return 6;
	case Cards::rank7:
		return 7;
	case Cards::rank8:
		return 8;
	case Cards::rank9:
		return 9;
	case Cards::rank10:
		return 10;
	case Cards::rankJack:
		return 10;
	case Cards::rankQueen:
		return 10;
	case Cards::rankKing:
		return 10;
	case Cards::rankAce:
		return 11;
	default:
		return 0;
	}
}

int main() {

	std::array<Card,Cards::numberOfCards> deck{};
	createDeck(deck);

	shuffleDeck(deck);
	printDeck(deck);

	return 0;
}


