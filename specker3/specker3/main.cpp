//
//  main.cpp
//  specker3
//
//  Created by Argyro on 28/3/21.
//

#include <iostream>
using namespace std;

class Game {
 public:
     Game(int heaps, int players);
     ~Game();
    
     void addHeap(int coins) throw(logic_error);
     void addPlayer(Player * player) throw(logic_error);
     void play(ostream & out) throw(logic_error);
     int getPlayers() const;
    const Player * getPlayer(int p) const throw(logic_error);

private:
    int* pointer;
    int initialCount1 = 0;
    Player** playerArray;
    int initialCount2 = 0;
    int heapNumber;
    int playerNumber;
    int* c;
    
 };
Game::Game(int heaps, int players)
{
    //int* coins = new int[heaps];
    //state = new State(heaps, new int[heaps] , players);
    pointer = new int[heaps];
    heapNumber = heaps;
    playerNumber = players;
    playerArray = new Player*[players];
}
Game::~Game()
{
    delete pointer;
    delete[] playerArray;
}

void Game::addHeap(int coins) throw(logic_error)
{
    if (coins >= 0) {
        pointer[initialCount1] = coins;
        initialCount1++;
    }
    else
        throw logic_error("invalid coins");
}

void Game::addPlayer(Player* player) throw(logic_error)
{
    if (player != nullptr) {
        playerArray[initialCount2] = player;
        initialCount2++;
    }
    else throw logic_error("invalid player");
}

void Game::play(ostream& out) throw(logic_error)
{
    if(initialCount2!=playerNumber || initialCount1!= heapNumber) throw logic_error("invalid");
    else{
        
    State state(heapNumber,pointer,playerNumber);
        int temp = 0;
    while (!state.winning()) {
        out << "State: " << state << endl;
        out << *playerArray[temp%playerNumber]<< " " << playerArray[temp%playerNumber]->play(state) << endl;
        state.next(playerArray[temp%playerNumber]->play(state));
        temp++;
        
    }
        //Move mm = playerArray[state->getPlaying()]->play(*state);
       // state->next(mm);
        //out << mm << endl;
       // state.next(playerArraytemp%pl)

    out << "State: " << state << endl;
        out << *playerArray[(temp-1)%playerNumber] << " wins" << endl;
        //(state->getPlaying()-1)<< "wins";
        }
}

int Game::getPlayers() const
{
    return playerNumber;
}

const Player* Game::getPlayer(int p) const throw(logic_error)
{
    if (p>=0) {
        return playerArray[p];
    }
    else throw logic_error("invalid player number") ;
}

