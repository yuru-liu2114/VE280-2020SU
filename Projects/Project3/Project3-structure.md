# Project 3

## card.h

### enum Suit{}

### extern const char *SuitNames[DIAMONDS+1]

### enum Spot{}

### extern const char *SpotNames[ACE+1]

### struct Card{Spot, Suit}

## deck.h

### class Deck (Card deck[DeckSize], int next);

## deck.cpp

### Deck::Deck()

initialize next & every element in deck array

### void Deck::reset()

reset next & every element in deck array

### void Deck::shuffle(int n)

modify deck array

### int Deck::cardsLeft() const

return DeckSize-next; (也就是还剩的牌数)

### 

### Card Deck::deal()

return the "next" card in deck

## hand.h

### struct HandValue{int count, bool soft}

### class Hand: private HandValue curValue

## hand.cpp

### Hand::Hand()

initialize curValue.count & curValue.soft

### void Hand::discardAll()

reset curValue.count & curValue.soft

### void Hand::addCard(Card c)

add curValue.count according to c.spot

### HandValue Hand::handValue() const

return curValue

























































































































and

