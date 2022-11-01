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
#include <vector>

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

namespace Players {

	enum Types {
		croupier,
		player
	};
}

const int maxScore = 21;
const int dealerStopPoints = 17;

struct Card {

	Cards::Ranks rank{};
	Cards::Suits suit{};
};

using deck_type = std::array<Card,Cards::numberOfCards>;

struct Player {

	std::vector<Card> hand{};
	Players::Types role;
	std::string name;
	int points = 0;
};

std::string recvInputFromUser(std::string& str) {

	std::getline(std::cin >> std::ws,str);
	return str;
}

char recvInputFromUser(char& value) {

	while (true) {
		std::cin >> value;
		if (std::cin.fail()) {
			std::cin.clear();
			std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
			printf("Try again\n");
		}
		else {
			std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
			return value;
		}
	}
}

std::string getName() {

	printf("Enter your name: ");
	std::string name;
	return recvInputFromUser(name);
}

void printCard(const Card& card) {

	switch(card.rank) {
	case Cards::rank2:		printf("2");	break;
	case Cards::rank3:		printf("3");	break;
	case Cards::rank4:		printf("4");	break;
	case Cards::rank5:		printf("5");	break;
	case Cards::rank6:		printf("6");	break;
	case Cards::rank7:		printf("7");	break;
	case Cards::rank8:		printf("8");	break;
	case Cards::rank9:		printf("9");	break;
	case Cards::rank10:		printf("10");	break;
	case Cards::rankJack:	printf("J");	break;
	case Cards::rankQueen:	printf("Q");	break;
	case Cards::rankKing:	printf("K");	break;
	case Cards::rankAce:	printf("A");	break;
	default:				printf("?");	break;
	}

	switch(card.suit) {
	case Cards::clubs:		printf("C");	break;
	case Cards::diamonds:	printf("D");	break;
	case Cards::hearts:		printf("H");	break;
	case Cards::spades:		printf("S");	break;
	default:				printf("?");	break;
	}
}

void createDeck(deck_type& deck) {

	int counter = 0;
	for (int i = 0; i < Cards::all_suits; ++i) {
		for (int j = 0; j < Cards::all_ranks; ++j) {
			deck[counter].rank = static_cast<Cards::Ranks>(j);
			deck[counter].suit = static_cast<Cards::Suits>(i);
			++counter;
		}
	}
}

void printDeck(deck_type& deck) {

	int counter = 0;
	for (Card i: deck) {
		printCard(i);
		++counter;
		(counter%13 == 0) ? printf(" \n") : printf(" ");
	}
}

void printHand(Player& user) {

	int counter = 0;
	for (int i=0; i<static_cast<int>(user.hand.size()); ++i) {
		printCard(user.hand[i]);
		++counter;
		(counter%13 == 0) ? printf(" \n") : printf(" ");
	}
}

void shuffleDeck(deck_type& deck) {

	std::mt19937 mt{ static_cast<std::mt19937::result_type>(std::time(nullptr)) };
	std::shuffle(deck.begin(), deck.end(), mt);
}

int getCardValue(Card& card) {

	switch(card.rank) {
	case Cards::rank2:		return 2;
	case Cards::rank3:		return 3;
	case Cards::rank4:		return 4;
	case Cards::rank5:		return 5;
	case Cards::rank6:		return 6;
	case Cards::rank7:		return 7;
	case Cards::rank8:		return 8;
	case Cards::rank9:		return 9;
	case Cards::rank10:		return 10;
	case Cards::rankJack:	return 10;
	case Cards::rankQueen:	return 10;
	case Cards::rankKing:	return 10;
	case Cards::rankAce:	return 11;
	default:				return 0;
	}
}

int handScore(std::vector<Card>& hand) {

	int total = 0;
	for (Card i: hand) {
		total += getCardValue(i);
	}
	return total;
}

Card getCard(deck_type& deck) {

	static int counter = 0;
	++counter;

	return deck[counter-1];
}

void deal(Player& user, deck_type& deck) {

	user.hand.push_back(getCard(deck));
	if (user.role == Players::player) {
		user.hand.push_back(getCard(deck));
	}
}

bool makeDecision(char choice) {

	return (choice == 'h') ? true : false;
}

void printScore(Player& user) {

	printf("%s's score now is: %d ( ",user.name.c_str(),user.points);
	printHand(user);
	printf(")%s\n",(user.role == Players::croupier)?" - croupier":"");
}

void move(Player& user, deck_type& deck, bool& gameStatus) {

	switch (user.role) {
	case Players::player:
		if (user.points > maxScore) {
			gameStatus = false;
		}
		else if (user.points < maxScore) {
			printf("Press 'h' if you want to get one more card or press anything in other way");
			printf("\n");
			char choice = recvInputFromUser(choice);
			if (makeDecision(choice)) {
				user.hand.push_back(getCard(deck));
				int index = static_cast<int>(user.hand.size())-1;
				user.points += getCardValue(user.hand[index]);
				printScore(user);
				move(user,deck,gameStatus);
			}
			else {
				printf("\n--- Move goes to next player... ---\n\n");
			}
		}
		else {
			printf("\nYou get exactly %d points. It's enough\n",maxScore);
			printf("--- Move goes to next player... ---\n\n");
		}
		break;
	case Players::croupier:
		if (user.points < dealerStopPoints) {
			user.hand.push_back(getCard(deck));
			int index = static_cast<int>(user.hand.size())-1;
			user.points += getCardValue(user.hand[index]);
			printScore(user);
			move(user,deck,gameStatus);
		}
		break;
	default:
		break;
	}
}

bool playBlackjack(Player& user, Player& dealer, deck_type& deck) {

	printScore(user);
	printScore(dealer);

	bool gameStatus = true;
	move(user,deck,gameStatus);
	if (gameStatus) {
		move(dealer,deck,gameStatus);
		if (user.points <= dealer.points) {
			gameStatus = false;
			if (dealer.points > maxScore) {
				gameStatus = true;
			}
		}
	}
	return gameStatus;
}

void printGameOverMsg(bool gameStatus) {

	printf("%s",(gameStatus)
		? "\n\tСongratulations! You're win!\n\n"
		: "\n\tYou've lost! What a pity :(\n\n");
}

int main() {

	deck_type deck{};
	createDeck(deck);

	shuffleDeck(deck);
//	printDeck(deck);

	Player croupier;
	croupier.role = Players::croupier;
	croupier.name = "Mr.Dealer";
	deal(croupier,deck);
	croupier.points = handScore(croupier.hand);

	Player player1;
	player1.role = Players::player;
	player1.name = getName();
	printf("\n");
	deal(player1,deck);
	player1.points = handScore(player1.hand);

	bool gameStatus = playBlackjack(player1,croupier,deck);
	printGameOverMsg(gameStatus);
	printf("Final results are:\n\n%15s%15d\n%15s%15d\n",
			player1.name.c_str(),player1.points,
			croupier.name.c_str(),croupier.points);

	return 0;
}


