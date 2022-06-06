//
//  main.cpp
//  specker1
//
//  Created by Argyro on 16/3/21.
//

#include <iostream>
#include <exception>
#include <stdexcept>
using namespace std;

class Move {
public:
    //Take sc coins from heap sh and put tc coins to heap th.
    Move(int sh, int sc, int th, int tc);
    int SourceHeap, SourceCoins;
    int TargetHeap, TargetCoins;
    
    int getSource() const;
    int getSourceCoins() const;
    int getTarget() const;
    int getTargetCoins() const;
    
    friend ostream & operator << (ostream &out, const Move &move);
    
};

Move::Move(int sh, int sc, int th, int tc){
    SourceHeap = sh;
    SourceCoins = sc;
    TargetHeap = th;
    TargetCoins = tc;
}
int Move::getSource() const{
    return SourceHeap;
}

int Move::getSourceCoins() const{
    return SourceCoins;
}

int Move::getTarget() const{
    return TargetHeap;
}

int Move::getTargetCoins() const{
    return TargetCoins;
}

ostream & operator << (ostream &out, const Move &move){
    out << "takes " << move.SourceCoins << " coins from heap " << move.SourceHeap << " and puts " << flush;
    if(move.TargetCoins == 0)
        out << "nothing" << flush;
    else
        out << move.TargetCoins << " coins to heap " << move.TargetHeap << flush;
    return out;
}

class State{
public:
    //State with h heaps, where the i-th heap starts with c[i] coins.
    // A total of n players are in the game, numbered from 0 to n-1,
    // and player 0 is the first to play.
    
    State(int h, const int c[], int n);
    ~State();
    
    void next(const Move &move) throw(logic_error);
    bool winning() const;
    
    int getHeaps() const;
    int getCoins(int h) const throw(logic_error);
    
    int getPlayers() const;
    int getPlaying() const;
    
    friend ostream & operator << (ostream &out, const State &state);
    
private:
    int* heap;
    int maxHeaps;
    int numberOfPlayers;
    int player = 0;
  
};


State::State(int h, const int c[], int n){
    maxHeaps = h;
    heap = new int[maxHeaps];
    for(int i = 0; i < maxHeaps; i++){
        heap[i] = c[i];
    }
        numberOfPlayers = n;
    
}

State::~State(){
    delete[] heap;
    return;
}

void State::next(const Move &move) throw(logic_error){
    if((move.SourceHeap<0) || (move.SourceHeap>=maxHeaps) || (move.TargetHeap<0) || (move.TargetHeap>=maxHeaps)) throw logic_error("invalid heap");
    else if((move.SourceCoins<=0) || (move.TargetCoins<0) || (heap[move.SourceHeap])<(move.SourceCoins)  || (move.TargetCoins >= move.SourceCoins)) throw logic_error("error - coins");
    else {
        heap[move.SourceHeap] -= move.SourceCoins;
        heap[move.TargetHeap] += move.TargetCoins;
        
        if((player) == numberOfPlayers-1){
            player = 0;
        }
        else (player)++;
        
    }
    return;
}

bool State::winning() const{
    for(int i=0; i<maxHeaps; i++){
        if(heap[i] != 0)
            return false;
    }
    return true;
}

int State::getHeaps() const{
    return maxHeaps;
}

int State::getCoins(int h) const throw(logic_error){
    if((h<0) || (h>=maxHeaps)) throw logic_error("invlaid heaps");
    else return heap[h];
}

int State::getPlayers() const{
    return numberOfPlayers;
}

int State::getPlaying() const{
    return player;
}

ostream & operator << (ostream &out, const State &state){
    out << state.heap[0];
    for(int i=1; i<state.maxHeaps; i++){
        out << ", " << state.heap[i];
    }
    out << " with " << state.getPlaying() << "/" << state.getPlayers() <<" playing next" << flush;
    return out;
}

