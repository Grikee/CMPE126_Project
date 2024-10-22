#ifndef Game_h
#define Game_h

#include <string>
#include <vector>
#include <stack>
#include <queue>
#include "Player.h"
using namespace std;

class Game {
public:
    string name;
    stack<string> playerMoves;
    vector<Player> players;

    Game(const string& n) : name(n) {}
    //Add player to vector
    void addPlayer(const Player& player) {
        players.push_back(player);
    }
    //Remove Player from vector
    void removeLastplayer() {
        players.pop_back();
    }
    //adds to the stack
    void addMove(const string& move){
      playerMoves.push(move);
    }
    //removes from the stack
    void undoMove(){
      playerMoves.pop();
    }
    void displayScores() const {
        cout << "Scores for Game '" << name << "':" << endl;
        for (const auto& player : players) {
            cout << player.name << ": " << player.score << endl;
        }
        cout << endl;
    }
};

#endif