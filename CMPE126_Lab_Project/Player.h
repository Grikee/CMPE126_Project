#ifndef Player_h
#define Player_h

#include <string>
#include <stack>
#include <queue>
using namespace std;

class Player {
public:
    string name;
    int score;

    Player(const string& n, int s) : name(n), score(s) {}

  Player& operator=(const Player& other) {
      return *this;
  }
  void setScore(int score){
    this->score = score;
  }

  int getScore(){
    return score;
  }

  string getName(){
    return name;
  }
  
  size_t hashFunction() {
    return hash<string>{}(name);
  }

  bool operator!=(const Player& other) const {
      return (this->name != other.name) || (this->score != other.score);
  }
  
};


#endif