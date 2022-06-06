//
//  main.cpp
//  specker2
//
//  Created by Argyro on 21/3/21.
//
#include "Move.h"
#include "State.h"
#include <iostream>
using namespace std;


/*A pure virtual function implicitly makes the class it is defined for abstract
(unlike in Java where you have a keyword to explicitly declare the class abstract).
Abstract classes cannot be instantiated.Derived classes need to override / implement
all inherited pure virtual functions.If they do not, they too will become abstract.

##### A class is abstract if it has at least one pure virtual function.  ######*/

class Player {
 public:
     Player(const string & n);
     virtual ~Player();
     /*Both of the below functions are pure virtual functions
    A pure virtual function is a virtual function whose declaration ends in =0

    #### NOTICE IF BOTH FUNCTIONS ARE NOT IMPLEMENTED BY A CHILD CLASS THEN
    CHILD CLASS IS ABSTRUCT #####*/

     //https://stackoverflow.com/questions/19808667/c-abstract-class-constructor-yes-or-no
     virtual const string & getType() const = 0;
     virtual Move play(const State & s) = 0;
     
     friend ostream & operator << (ostream & out, const Player & player);
private:
    string name;
};

Player::Player(const string & n) {
    name = n;
}

Player::~Player()
{
}

ostream& operator<<(ostream& out, const Player& player)
{
    out << player.getType() << " player " << player.name << flush;
        return out;
}

class GreedyPlayer: public Player {
public:
    GreedyPlayer(string name) : Player(name) {
        type = "Greedy";
    };
    
    const string& getType() const {
        return type;
    }
    
    Move play(const State& s) {
        
        int maxcoins = 0;
        int heaps = 0;
        for(int i=0; i<s.getHeaps(); i++){
            if(maxcoins < s.getCoins(i)){
                maxcoins = s.getCoins(i);
            
                heaps = i;
            }
        }

        Move moveByGreedy(heaps, maxcoins, 0, 0);
        return moveByGreedy;
    }
private: string type;
};

class SpartanPlayer: public Player{
public:
    SpartanPlayer(string name):Player(name){
        type = "Spartan";
    };
    
    const string& getType() const{
        return type;
    }
    Move play(const State& s){
        int heaps = 0;
        int maxcoins = 0;

        for(int i=0; i<s.getHeaps(); i++){
           
            
            if(maxcoins < s.getCoins(i)){
                maxcoins = s.getCoins(i);
                heaps=i;
            }
        }
        
        Move moveBySpartan(heaps,1,0,0);
        return moveBySpartan;
    }
private: string type;
};

class SneakyPlayer: public Player{
public:
    SneakyPlayer(string name):Player(name){
        type = "Sneaky";
    };
    
    const string& getType() const{
        return type;
    }
    Move play(const State& s){
        int mincoins = 0;
        int heaps = 0;
        for(int i=0; i<s.getHeaps();i++){
            if(mincoins > s.getCoins(i)){
                mincoins = s.getCoins(i);
                heaps = i;
            }
            
        }
        
        Move moveBySneaky(heaps,mincoins,0,0);
        return moveBySneaky;
    }
private: string type;
};

class RighteousPlayer: public Player{
public:
    
    RighteousPlayer(string name):Player(name){
        type = "Righteous";
    };
    
    const string& getType() const{
        return type;
    }
    
    Move play(const State& s){
        int heaps = 0;
        int maxcoins = 0;
        int heap = 0;
        int mincoins = 0;

        for(int i=0; i<s.getHeaps(); i++){
            if(maxcoins < s.getCoins(i)){
                maxcoins = s.getCoins(i);
                heaps = i;
            }
            
            if(mincoins > s.getCoins(i)){
                mincoins = s.getCoins(i);
                heap = i;
            }
        }
            
            
        
        
        Move moveByRighteous(heaps,(maxcoins+1)/2,heap,(mincoins+1)/2 -1);
        return moveByRighteous;
    }
protected: string type;
};

