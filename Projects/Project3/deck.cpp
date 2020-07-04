#include "deck.h"
#include <cassert>
#include <iostream>

using namespace std;

Deck::Deck() {
    next = 0;
    for (int cindex = 0; cindex < DeckSize; ++cindex) {
        deck[cindex].spot = (Spot) (cindex % 13);
        deck[cindex].suit = (Suit) (cindex / 13);
    }
}

void Deck::reset() {
    next = 0;
    for (int cindex = 0; cindex < DeckSize; ++cindex) {
        deck[cindex].spot = (Spot) (cindex % 13);
        deck[cindex].suit = (Suit) (cindex / 13);
    }
}

void Deck::shuffle(int n) { //take n=15 as example //consider empty sets
    cout << "cut at " << n << endl;
    next = 0;
    Card newdeck[DeckSize];
    //left: 0 - n-1(0~14), right: n - DeckSize-1(15~51)
    const int left_size = n; //15
    const int right_size = DeckSize - n; //37
    const int min_size = min(left_size, right_size); //15
    int total_index = -1;
    for (int i = 0; i < min_size; i++) {
        // left: 0~min_size-1(0~14); right: n~n+min_size-1(15~29);
        // remain: minsize~n-1(rightsize smaller),remain:n+minsize~DeckSize-1(leftsize smaller)
        int right_index = n + i;
        int left_index = i;
        newdeck[++total_index] = deck[right_index];
        newdeck[++total_index] = deck[left_index];
    }
    if (min_size == left_size) {
        for (int i = n + min_size; i < DeckSize; i++) {
            newdeck[++total_index] = deck[i];
        }
    } else {
        for (int i = min_size; i < n; i++) {
            newdeck[++total_index] = deck[i];
        }
    }
    for (int i = 0; i < DeckSize; i++) {
        deck[i] = newdeck[i];
    }
}

int Deck::cardsLeft(){
    return DeckSize - next;
}

Card Deck::deal() {
    if (cardsLeft() > 0) {
        return deck[next++];
    } else {
        DeckEmpty deck_empty;
        throw deck_empty;
    }
}
