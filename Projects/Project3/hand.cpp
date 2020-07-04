#include "hand.h"

Hand::Hand() {
    curValue.count = 0;
    curValue.soft = false;
}

void Hand::discardAll() {
    curValue.count = 0;
    curValue.soft = false;
}

void Hand::addCard(Card c) {
    if (c.spot < 8) {
        //TWO~NINE(0~7)
        curValue.count += c.spot + 2;
    }
    if (c.spot < 12 && c.spot > 7) {
        //TEN~KING(8~11)
        curValue.count += 10;
    }
    if (c.spot == 12) {
        //ACE
        if (curValue.count <= 10) {
            curValue.count += 11;
            curValue.soft = true;
        } else {
            curValue.count += 1;
        }
    }
    if (curValue.count > 21 && curValue.soft) {
        curValue.soft = false;
        curValue.count -= 10;
    }
}

HandValue Hand::handValue() const {
    return curValue;
}
