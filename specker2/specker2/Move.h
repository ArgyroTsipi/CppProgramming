//
//  Move.h
//  specker2
//
//  Created by Argyro on 21/3/21.
//

#ifndef MOVE
#define MOVE
#include <ostream>
using namespace std;

class Move {
public:
    //Take sc coins from heap sh and put tc coins to heap th.
    Move(int sh, int sc, int th, int tc);

    /*When you add the const keyword to a method the this pointer will essentially become a
    pointer to const object, and you cannot therefore change any member data.

    Putting const after a member function indicates that the code inside it will not modify
    the containing object

    The const keyword is part of the functions signature which means that you can implement
    two similar methods, one which is called when the object is const, and one that isn't.*/

    int getSource() const;
    int getSourceCoins() const;
    int getTarget() const;
    int getTargetCoins() const;

    friend ostream& operator << (ostream& out, const Move& move);
private:
    int SourceHeap, SourceCoins;
    int TargetHeap, TargetCoins;
};

//o constructor
Move::Move(int sh, int sc, int th, int tc) {
    SourceHeap = sh;
    SourceCoins = sc;
    TargetHeap = th;
    TargetCoins = tc;
}
//dinei to source heap
int Move::getSource() const {
    return SourceHeap;
}

//dinei ta source coins
int Move::getSourceCoins() const {
    return SourceCoins;
}

//dinei to target heap
int Move::getTarget() const {
    return TargetHeap;
}

//dinei ta target coins
int Move::getTargetCoins() const {
    return TargetCoins;
}

//kanei cout auto pou leei h askhsh + ta 2 cases
ostream& operator << (ostream& out, const Move& move) {
    out << "takes " << move.SourceCoins << " coins from heap " << move.SourceHeap << " and puts " << flush;
    if (move.TargetCoins == 0)
        out << "nothing" << flush;
    else
        out << move.TargetCoins << " coins to heap " << move.TargetHeap << flush;
    return out;
}
#endif /* Move_h */
