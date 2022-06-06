//
//  State.h
//  specker2
//
//  Created by Argyro on 21/3/21.
//

#ifndef STATE
#define STATE
#include "Move.h"
#include <stdexcept>
//using namespace std;

class State {
public:
    //State with h heaps, where the i-th heap starts with c[i] coins.
    // A total of n players are in the game, numbered from 0 to n-1,
    // and player 0 is the first to play.

    State(int h, const int c[], int n);
    ~State();

    /*This declares a function called next, which takes one argument of type Move and
    returns no value.If this function throws an exception of some type other
    than int, the function calls std::unexpected instead of looking for a handler or calling
    std::terminate.

    If this throw specifier is left empty with no type, this means that std::unexpected is
    called for any exception.Functions with no throw specifier(regular functions) never call
    std::unexpected, but follow the normal path of looking for their exception handler.*/
    //https://docs.microsoft.com/en-us/cpp/cpp/exception-specifications-throw-cpp?view=msvc-160

    void next(const Move& move) throw(logic_error);
    bool winning() const;

    int getHeaps() const;
    int getCoins(int h) const throw(logic_error);

    int getPlayers() const;
    int getPlaying() const;

    friend ostream& operator << (ostream& out, const State& state);

private:
    int* heap;
    int maxHeaps;
    int numberOfPlayers;
    int currentPlayer = 0;
};


//o constructor
//gia kathe i-th heap na vazei to coin i
State::State(int h, const int c[], int n) {
    maxHeaps = h;
    heap = new int[maxHeaps];
    for (int i = 0; i < maxHeaps; i++) {
        heap[i] = c[i];
    }
    numberOfPlayers = n;
}

//o destructor
State::~State() {
    delete[] heap;
    return;
}

//check is next move is valid, if so, make next move
void State::next(const Move& move) throw(logic_error) {
    if ((move.getSource() < 0) || (move.getSource() >= maxHeaps) || (move.getTarget() < 0) || (move.getTarget() >= maxHeaps)) throw logic_error("invalid heap");
    else if ((move.getSourceCoins() <= 0) || (move.getTargetCoins() < 0) || (heap[move.getSource()]) < (move.getSourceCoins()) || (move.getTargetCoins() >= move.getSourceCoins())) throw logic_error("error - coins");
    else {
        heap[move.getSource()] -= move.getSourceCoins();
        heap[move.getTarget()] += move.getTargetCoins();

        if ((currentPlayer) == numberOfPlayers - 1) {
            currentPlayer = 0;
        }
        else (currentPlayer)++;
    }
    return;
}

//check who is winning
bool State::winning() const {
    for (int i = 0; i < maxHeaps; i++) {
        if (heap[i] != 0)
            return false;
    }
    return true;
}

//get maxHeaps
int State::getHeaps() const {
    return maxHeaps;
}

//get coins of h heap == heap[h] == c[h]
int State::getCoins(int h) const throw(logic_error) {
    if ((h < 0) || (h >= maxHeaps)) throw logic_error("invlaid heaps");
    else return heap[h];
}

//get the number of players
int State::getPlayers() const {
    return numberOfPlayers;
}

//whose turn it is
int State::getPlaying() const {
    return currentPlayer;
}

//cout
ostream& operator << (ostream& out, const State& state) {
    out << state.heap[0];
    for (int i = 1; i < state.maxHeaps; i++) {
        out << ", " << state.heap[i];
    }
    out << " with " << state.getPlaying() << "/" << state.getPlayers() << " playing next" << flush;
    return out;
}

#endif /* State_h */
