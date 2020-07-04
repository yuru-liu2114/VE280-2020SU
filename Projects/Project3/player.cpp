#include "player.h"

// implement SimplePlayer
class SimplePlayer : public Player {
public:
    virtual int bet(unsigned bankroll, unsigned minimum) { //TODO: unsigned int!
        return (int) minimum;
    }

    bool draw(Card dealer, const Hand &player) {
        int total = player.handValue().count;
        if (player.handValue().soft) { //soft field
            if (total <= 17) return true;
            else if (total >= 19) return false;
            else {
                return !(dealer.spot == 0 || dealer.spot == 5 || dealer.spot == 6);
            }
        }
        else { //hard field
            if (total <= 11) return true;
            else if (total >= 17) return false;
            else if (total == 12) {
                return !(dealer.spot == 2 || dealer.spot == 3 || dealer.spot == 4);
            }
            else {
                return !(dealer.spot <= 4);
            }
        }
    }

    virtual void expose(Card c) {}

    virtual void shuffled() {}
};

// implement CountingPlayer
class CountingPlayer : public SimplePlayer {
    int count = 0;
public:

    int bet(unsigned bankroll, unsigned minimum) {
        if (bankroll >= 2 * minimum && count >= 2) {
            return (int) (2 * minimum);
        } else return (int) minimum;
    }

    void expose(Card c) {
        if (c.spot >= 8) {
            count--;
            return;
        } else if (c.spot <= 4) {
            count++;
            return;
        }
    }

    void shuffled() {
        count = 0;
    }
};

static SimplePlayer simpleplayer;
extern Player *get_Simple() {
    return &simpleplayer;
}
static CountingPlayer countingplayer;
extern Player *get_Counting() {
    return &countingplayer;
}

