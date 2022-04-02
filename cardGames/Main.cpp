// cardGames.cpp : This file contains the 'main' function. Program execution begins and ends there.
//
#include <iostream>
#include <vector>
#include <string>
#include <cstdlib>
#include<ctime>

using std::vector;
using std::string;

enum Suit { Heart, Clubs, Diamond, Spade };
enum Rank { Jack = 2, Queen, King, Ten = 10, Ace };

struct Card {
    Rank rank;
    Suit suit;
    int num_suits = 4;
    int num_ranks = 5;
};

struct Deck {
    vector<Card> cards;
    string card_back;

};

void initialize(Deck&);
void print_deck(const Deck&);
void print_card(const Card&);
void shuffle(Deck&);
void deal_cards(Deck&, vector<Card>&, vector<Card>&, int);
void print_hand(const vector<Card>&);
void add_card(vector<Card>& table, vector<Card>& hand, int cards);
void deck_on_table(Deck& deck, vector<Card>& rest_of_deck, int num_cards);
void invalid_move(int& move, const vector<Card> player_hand);
void play_game(Deck my_deck);
void rules();



int main()
{

    Deck my_deck;
    initialize(my_deck);
    shuffle(my_deck);
    int decision{};
    char play = 'Y';

    while (play == 'Y' || play == 'y') {
        std::cout << "\n Welcome!\n\n1.) Rules\n2.) Play game\n";
        std::cin >> decision;

        if (decision == 1) {
            rules();
        }
        else if (decision == 2) {
            play_game(my_deck);
            std::cout << "\n\nDo you want to play again? Y/N\n";
            std::cin >> play;
        }

        
    }
    

}

void rules() {
    string back{};

    while (back != "B" && back != "b") {
        std::cout << "\nGame is played with a pack of 20 cards (J, Q, K, 10, A). The cards have the following value:\n";
        std::cout << "\nJack:  2\nQueen:  3\nKing:  4\n 10:  10\nAce:  11\n";
        std::cout << "Each player gets five cards. The remaining cards are put in the stack. Every player puts one card on the table\n";
        std::cout << "and the highest card win. Player who wins the round picks all cards from the table and puts them in his deck.\n";
        std::cout << "After each round players draw one card from the deck. Player who won the previous round is the one who draws first.\n";
        std::cout << "If players put on the table the card of the same value we call it a draw and players must each draw one card from the stack\n";
        std::cout << "and then put one more card on the table. The player who has the biggest card wins the round.\n";
        std::cout << "After the stack is gone the players continue to play until they are out of cards.\n";
        std::cout << "When the players are out of cards the game is finished.\n";
        std::cout << "Winner is a player who has more points\n";
        std::cout << "\nPress B to go back\n";
        std::cin >> back;
    }
    
}
void initialize(Deck& deck) {

    Card card;
    for (int suit = 0; suit < card.num_suits; suit++) {
        for (int rank = 2; rank < 5; rank++) {
            card.suit = Suit(suit);
            card.rank = Rank(rank);
            deck.cards.push_back(card);
        }
        for (int rank = 10; rank < 12; rank++) {
            card.suit = Suit(suit);
            card.rank = Rank(rank);
            deck.cards.push_back(card);
        }
    }

}

// Function to print deck of cards
void print_deck(const Deck& deck) {
    for (Card c : deck.cards) {
        print_card(c);
    }
}

void print_card(const Card& card) {
    //Cards

    if (card.rank == 2) {
        std::cout << "Jack of ";
    }
    else if (card.rank == 3)
    {
        std::cout << "Queen of ";
    }
    else if (card.rank == 4)
    {
        std::cout << "King of ";
    }
    else if (card.rank == 10)
    {
        std::cout << "Ten of ";
    }
    else if (card.rank == 11)
    {
        std::cout << "Ace of ";
    }

    // Suits of cards
    if (card.suit == 0) {
        std::cout << "Hearts" << std::endl;
    }
    else if (card.suit == 1) {
        std::cout << "Clubs" << std::endl;
    }
    else if (card.suit == 2) {
        std::cout << "Diamonds" << std::endl;
    }
    else if (card.suit == 3) {
        std::cout << "Spades" << std::endl;
    }

}

//Function to shuffle and get random cards
void shuffle(Deck& deck) {
    Deck shuffled;
    while (!deck.cards.empty()) {
        srand(time(0));
        size_t rand_index = rand() % deck.cards.size();
        shuffled.cards.push_back(deck.cards[rand_index]);
        deck.cards.erase(deck.cards.begin() + rand_index);
    }
    deck = shuffled;
}

//Function to deal cards to players
void deal_cards(Deck& deck, vector<Card>& hand_1, vector<Card>& hand_2, int num_cards) {
    for (int card = 0; card < num_cards; card++) {
        hand_1.push_back(deck.cards[0]);
        deck.cards.erase(deck.cards.begin());
        hand_2.push_back(deck.cards[0]);
        deck.cards.erase(deck.cards.begin());
    }
}

void deck_on_table(Deck& deck, vector<Card>& rest_of_deck, int num_cards) {
    for (int card = 0; card < 10; card++) {
        rest_of_deck.push_back(deck.cards[0]);
        deck.cards.erase(deck.cards.begin());
    }
}

void print_hand(const vector<Card>& hand) {
    for (Card c : hand) {
        print_card(c);
    }

}void print_player_hand(const vector<Card>& hand) {
    int i = 1;
    for (Card c : hand) {
        std::cout << i << ") ";
        print_card(c);
        i++;
    }
}

// Function to add cards on the table
void add_card(vector<Card>& table, vector<Card>& hand, int cards) {

    for (int i = 0; i < cards; i++) {
        table.push_back(hand[0]);
        hand.erase(hand.begin());
    }


}

void invalid_move(int& move, const vector<Card> player_hand) {
    while (move < 1 || move > player_hand.size()) {
        std::cout << "\nPlease insert valid card number\n";
        std::cin >> move;
    }
}

void play_game(Deck my_deck) {

    vector<Card> player_hand;
    vector<Card> computer_player_hand;
    vector<Card> rest_of_deck;
    vector<Card> card_on_table_player_1;
    vector<Card> card_on_table_computer;
    vector<Card> player1_stack;
    vector<Card> computer_player_stack;
    string turn = "player";

    deal_cards(my_deck, player_hand, computer_player_hand, 5);
    deck_on_table(my_deck, rest_of_deck, 10);

    int move{};

    while (rest_of_deck.size() > 0) {

        if (turn == "player") {
            std::cout << "\nYour hand is: \n";
            print_player_hand(player_hand);
            std::cout << "\n\n";
            std::cout << "Your turn!\n";
            std::cin >> move;
            std::cout << "------------------------------------------------------------\n\n";
            invalid_move(move, player_hand);
            card_on_table_player_1.insert(card_on_table_player_1.begin(), player_hand.at(move - 1));
            player_hand.erase(player_hand.begin() + (move - 1));

            card_on_table_computer.insert(card_on_table_computer.begin(), computer_player_hand.at(0));
            computer_player_hand.erase(computer_player_hand.begin());
        }
        else if (turn == "computer") {
            card_on_table_computer.insert(card_on_table_computer.begin(), computer_player_hand.at(0));
            computer_player_hand.erase(computer_player_hand.begin());
            std::cout << "\nComputer has ";
            print_hand(card_on_table_computer);

            std::cout << "\nYour hand is: \n";
            print_player_hand(player_hand);
            std::cout << "\n\n";
            std::cout << "Your turn!\n";
            std::cin >> move;
            std::cout << "------------------------------------------------------------\n\n";
            invalid_move(move, player_hand);
            card_on_table_player_1.insert(card_on_table_player_1.begin(), player_hand.at(move - 1));
            player_hand.erase(player_hand.begin() + (move - 1));
        }


        std::cout << "\nPlayer has: \n";
        print_hand(card_on_table_player_1);

        std::cout << "\n\nComputer has: \n";
        print_hand(card_on_table_computer);


        if (card_on_table_player_1[0].rank > card_on_table_computer[0].rank) {
            std::cout << "------------------------------------------------------------\n\n";
            std::cout << "\n\nPlayer has bigger hand and wins this round!\n\n";
            std::cout << "------------------------------------------------------------\n\n";
            for (int i = 0; i < card_on_table_player_1.size(); i++) {
                player1_stack.push_back(card_on_table_player_1.at(0));
                player1_stack.push_back(card_on_table_computer.at(0));
            }

            card_on_table_computer.clear();
            card_on_table_player_1.clear();


            player_hand.push_back(rest_of_deck.at(0));
            rest_of_deck.erase(rest_of_deck.begin());
            computer_player_hand.push_back(rest_of_deck.at(0));
            rest_of_deck.erase(rest_of_deck.begin());

            turn = "player";

        }
        else if (card_on_table_computer[0].rank > card_on_table_player_1[0].rank) {
            std::cout << "------------------------------------------------------------\n\n";
            std::cout << "\n\nComputer has bigger hand and wins this round!\n\n";
            std::cout << "------------------------------------------------------------\n\n";
            for (int i = 0; i < card_on_table_player_1.size(); i++) {
                computer_player_stack.push_back(card_on_table_player_1.at(0));
                computer_player_stack.push_back(card_on_table_computer.at(0));
            }

            card_on_table_computer.clear();
            card_on_table_player_1.clear();


            computer_player_hand.push_back(rest_of_deck.at(0));
            rest_of_deck.erase(rest_of_deck.begin());
            player_hand.push_back(rest_of_deck.at(0));
            rest_of_deck.erase(rest_of_deck.begin());

            turn = "computer";

        }
        else if (card_on_table_computer[0].rank == card_on_table_player_1[0].rank) {
            std::cout << "------------------------------------------------------------\n\n";
            std::cout << "\n\nIt's a draw! Play one more round!\n";
            std::cout << "------------------------------------------------------------\n\n";
            player_hand.push_back(rest_of_deck.at(0));
            rest_of_deck.erase(rest_of_deck.begin());
            computer_player_hand.push_back(rest_of_deck.at(0));
            rest_of_deck.erase(rest_of_deck.begin());
        }

    }

    while (player_hand.size() > 1) {

        if (turn == "player") {
            std::cout << "\nYour hand is: \n";
            print_player_hand(player_hand);
            std::cout << "\n\n";
            std::cout << "Your turn!\n";
            std::cin >> move;
            std::cout << "------------------------------------------------------------\n\n";
            invalid_move(move, player_hand);
            card_on_table_player_1.insert(card_on_table_player_1.begin(), player_hand.at(move - 1));
            player_hand.erase(player_hand.begin() + (move - 1));

            card_on_table_computer.insert(card_on_table_computer.begin(), computer_player_hand.at(0));
            computer_player_hand.erase(computer_player_hand.begin());
        }
        else if (turn == "computer") {
            card_on_table_computer.insert(card_on_table_computer.begin(), computer_player_hand.at(0));
            computer_player_hand.erase(computer_player_hand.begin());
            std::cout << "\nComputer has ";
            print_hand(card_on_table_computer);

            std::cout << "\n\nYour hand is: \n";
            print_player_hand(player_hand);
            std::cout << "\n\n";
            std::cout << "Your turn!\n";
            std::cin >> move;
            std::cout << "------------------------------------------------------------\n\n";
            invalid_move(move, player_hand);
            card_on_table_player_1.insert(card_on_table_player_1.begin(), player_hand.at(move - 1));
            player_hand.erase(player_hand.begin() + (move - 1));
        }

        std::cout << "\n\nPlayer has: \n";
        print_hand(card_on_table_player_1);

        std::cout << "\n\nComputer has: \n";
        print_hand(card_on_table_computer);


        if (card_on_table_player_1[0].rank > card_on_table_computer[0].rank) {
            std::cout << "------------------------------------------------------------\n\n";
            std::cout << "\n\nPlayer has bigger hand and wins this round!\n\n";
            std::cout << "------------------------------------------------------------\n\n";
            for (int i = 0; i < card_on_table_player_1.size(); i++) {
                player1_stack.push_back(card_on_table_player_1.at(0));
                player1_stack.push_back(card_on_table_computer.at(0));
            }

            card_on_table_computer.clear();
            card_on_table_player_1.clear();

            turn = "player";
        }
        else if (card_on_table_computer[0].rank > card_on_table_player_1[0].rank) {
            std::cout << "------------------------------------------------------------\n\n";
            std::cout << "\n\nComputer has bigger hand and wins this round!\n\n";
            std::cout << "------------------------------------------------------------\n\n";
            for (int i = 0; i < card_on_table_player_1.size(); i++) {
                computer_player_stack.push_back(card_on_table_player_1.at(0));
                computer_player_stack.push_back(card_on_table_computer.at(0));
            }

            card_on_table_computer.clear();
            card_on_table_player_1.clear();

            turn = "computer";
        }
        else if (card_on_table_computer[0].rank == card_on_table_player_1[0].rank) {
            std::cout << "------------------------------------------------------------\n\n";
            std::cout << "\n\nIt's a draw! Play one more round!\n";
            std::cout << "------------------------------------------------------------\n\n";
        }
    }

    while (player_hand.size() == 1)
    {
        if (turn == "player") {
            std::cout << "\nYour hand is: \n";
            print_player_hand(player_hand);
            std::cout << "\n\n";
            std::cout << "Your turn!\n";
            std::cin >> move;
            std::cout << "------------------------------------------------------------\n\n";
            invalid_move(move, player_hand);
            card_on_table_player_1.insert(card_on_table_player_1.begin(), player_hand.at(move - 1));
            player_hand.erase(player_hand.begin() + (move - 1));

            card_on_table_computer.insert(card_on_table_computer.begin(), computer_player_hand.at(0));
            computer_player_hand.erase(computer_player_hand.begin());
        }
        else if (turn == "computer") {
            card_on_table_computer.insert(card_on_table_computer.begin(), computer_player_hand.at(0));
            computer_player_hand.erase(computer_player_hand.begin());
            std::cout << "\nComputer has ";
            print_hand(card_on_table_computer);

            std::cout << "\nYour hand is: \n";
            print_player_hand(player_hand);
            std::cout << "\n\n";
            std::cout << "Your turn!\n";
            std::cin >> move;
            std::cout << "------------------------------------------------------------\n\n";
            invalid_move(move, player_hand);
            card_on_table_player_1.insert(card_on_table_player_1.begin(), player_hand.at(move - 1));
            player_hand.erase(player_hand.begin() + (move - 1));
        }

        std::cout << "\nPlayer has: \n";
        print_hand(card_on_table_player_1);

        std::cout << "\n\nComputer has: \n";
        print_hand(card_on_table_computer);


        if (card_on_table_player_1[0].rank > card_on_table_computer[0].rank) {
            std::cout << "------------------------------------------------------------\n\n";
            std::cout << "\n\nPlayer has bigger hand and wins this round!\n\n";
            std::cout << "------------------------------------------------------------\n\n";
            for (int i = 0; i < card_on_table_player_1.size(); i++) {
                player1_stack.push_back(card_on_table_player_1.at(0));
                player1_stack.push_back(card_on_table_computer.at(0));
            }

            card_on_table_computer.clear();
            card_on_table_player_1.clear();
        }
        else if (card_on_table_computer[0].rank > card_on_table_player_1[0].rank) {
            std::cout << "------------------------------------------------------------\n\n";
            std::cout << "\n\nComputer has bigger hand and wins this round!\n\n";
            std::cout << "------------------------------------------------------------\n\n";
            for (int i = 0; i < card_on_table_player_1.size(); i++) {
                computer_player_stack.push_back(card_on_table_player_1.at(0));
                computer_player_stack.push_back(card_on_table_computer.at(0));
            }

            card_on_table_computer.clear();
            card_on_table_player_1.clear();
        }
        else if (card_on_table_computer[0].rank == card_on_table_player_1[0].rank) {
            std::cout << "\n\nIt's a draw! Each player takes it's own card and put it in his stack.\n";
            computer_player_stack.push_back(card_on_table_computer.at(0));
            player1_stack.push_back(card_on_table_player_1.at(0));
        }
    }

    int points_player{};
    int points_computer{};

    for (int i = 0; i < player1_stack.size(); i++) {
        points_player += player1_stack[i].rank;
    }

    for (int i = 0; i < computer_player_stack.size(); i++) {
        points_computer += computer_player_stack[i].rank;
    }

    std::cout << "\n\nPlayer has " << points_player << " points\n";
    std::cout << "\n\nComputer has " << points_computer << " points\n";

    if (points_player > points_computer) {
        std::cout << "\nCongratulations you are a winner!\n";
    }
    else if (points_player < points_computer) {
        std::cout << "\nYou lose! Computer is a winner! Better luck next time!\n";
    }
    else {
        std::cout << "\nIt's a draw!";
    }


}



// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file
