#include "card.h"
#include "hand.h"
#include "deck.h"
#include "player.h"
#include "rand.h"
#include <iostream>
#include <cstdlib>

using namespace std;
int bankroll, num_hands, wager, nth_hand;
const int minimum = 5;
Card hole_card, dealer_up;
Deck driver_deck;
static Player *driver_player;
static Hand player_hand, dealer_hand;
bool bust, hit;

void driver_shuffle();
// REQUIRES: driver_deck is not an empty array
// MODIFIES: driver_deck array & driver_player
// EFFECTS: shuffle driver_deck and set count=0 (in driver_player)

void deal_four_cards();
// REQUIRES: driver_deck is not empty, dealer and player are just initialized
// MODIFIES: player_hand & dealer_hand & driver_deck & driver_player
// EFFECTS: draw cards from driver_deck, expose in driver_player, add card in player_hand and dealer_hand

bool is_natural21();
// REQUIRES: player_hand is not empty, player's count is 21
// MODIFIES: player_hand and bankroll
// EFFECTS: return true if player_hand's count is exactly 21

void player_draw();
// REQUIRES: driver_deck is not empty, player doesn't bust
// MODIFIES: player_hand & driver_deck
// EFFECTS: draw cards from driver_deck, add cards in player_hand

void dealer_draw();
// REQUIRES: driver_deck is not empty, dealer doesn't bust
// MODIFIES: dealer_hand & driver_deck
// EFFECTS: draw cards from driver_deck, add cards in dealer_hand

void if_win();
// REQUIRES: dealer and player both doesn't bust
// MODIFIES: increment nth_hand
// EFFECTS: print different messages according to comparison, and increment nth_hand

int main(int argc,char* argv[]) {
    string player_type;
    bankroll = atoi(argv[1]);
    num_hands = atoi(argv[2]);
    player_type = argv[3];
    if (player_type == "simple") {
        driver_player = get_Simple();
    } else if (player_type == "counting") {
        driver_player = get_Counting();
    }
    // first: shuffle
    driver_deck.reset();
    driver_shuffle();
    // enter hand loop
    if (bankroll < minimum) nth_hand = 0;
    else nth_hand = 1;
    while (nth_hand <= num_hands && bankroll >= minimum) {
        int tmp_bankroll = bankroll; //avoid direct modification of bankroll
        player_hand.discardAll();
        dealer_hand.discardAll();
        wager = 0;
        cout << "Hand " << nth_hand << " bankroll " << bankroll << endl;
        if (driver_deck.cardsLeft() < 20) {
            driver_deck.reset();
            driver_shuffle();
        }
        wager = driver_player->bet(tmp_bankroll, minimum);
        cout << "Player bets " << wager << endl;
        deal_four_cards();
        if (is_natural21()) {
            nth_hand++;
            continue;
        }
        player_draw();
        if (bust) {
            cout << "Player busts\n";
            bankroll -= wager;
            nth_hand++;
            continue;
        }
        dealer_draw();
        bust = dealer_hand.handValue().count > 21;
        if (bust) {
            cout << "Dealer busts\n";
            bankroll += wager;
            nth_hand++;
            continue;
        }
        if_win();
    }
    if (nth_hand == 0) { nth_hand++; }
    cout << "Player has " << bankroll << " after " << nth_hand - 1 << " hands\n";
    return 0;
}

void driver_shuffle() {
    cout << "Shuffling the deck\n";
    for (int i = 0; i < 7; ++i) {
        driver_deck.shuffle(get_cut());
    }
    driver_player->shuffled();
}

void deal_four_cards() {
    Card currcard{};
    // 1: face-up to player
    currcard = driver_deck.deal();
    player_hand.addCard(currcard);
    driver_player->expose(currcard);
    //debug code:
    cout << "Player dealt " << SpotNames[currcard.spot] << " of " << SuitNames[currcard.suit] << endl;
    // 2: face-up to dealer
    currcard = driver_deck.deal();
    dealer_up = currcard;
    dealer_hand.addCard(currcard);
    driver_player->expose(currcard);
    cout << "Dealer dealt " << SpotNames[currcard.spot] << " of " << SuitNames[currcard.suit] << endl;
    // 3: face-up to player
    currcard = driver_deck.deal();
    player_hand.addCard(currcard);
    driver_player->expose(currcard);
    cout << "Player dealt " << SpotNames[currcard.spot] << " of " << SuitNames[currcard.suit] << endl;
    // 4: face-down to dealer
    hole_card = driver_deck.deal();
    dealer_hand.addCard(hole_card);
}

bool is_natural21() {
    if (player_hand.handValue().count == 21) {
        cout << "Player dealt natural 21\n";
        bankroll += 3 * wager / 2;
        return true;
    } else return false;
}

void player_draw() {
    bust = (player_hand.handValue().count > 21);
    hit = driver_player->draw(dealer_up, player_hand);
    while (!bust && hit) {
        Card currcard = driver_deck.deal();
        player_hand.addCard(currcard);
        driver_player->expose(currcard);
        cout << "Player dealt " << SpotNames[currcard.spot] << " of " << SuitNames[currcard.suit] << endl;
        bust = (player_hand.handValue().count > 21);
        hit = driver_player->draw(dealer_up, player_hand);
    }
    cout << "Player's total is " << player_hand.handValue().count << endl;
}

void dealer_draw() {
    driver_player->expose(hole_card);
    cout << "Dealer's hole card is " << SpotNames[hole_card.spot] << " of " << SuitNames[hole_card.suit] << endl;
    // dealer begins to draw
    while (dealer_hand.handValue().count < 17) {
        Card currcard = driver_deck.deal();
        dealer_hand.addCard(currcard);
        driver_player->expose(currcard);
        cout << "Dealer dealt " << SpotNames[currcard.spot] << " of " << SuitNames[currcard.suit] << endl;
    }
    cout << "Dealer's total is " << dealer_hand.handValue().count << endl;
}

void if_win() {
    if (dealer_hand.handValue().count < player_hand.handValue().count) {
        cout << "Player wins\n";
        bankroll += wager;
    } else if (dealer_hand.handValue().count > player_hand.handValue().count) {
        cout << "Dealer wins\n";
        bankroll -= wager;
    } else if (dealer_hand.handValue().count == player_hand.handValue().count) {
        cout << "Push\n";
    }
    nth_hand++;
}

