#ifndef ScoreTracker_h
#define ScoreTracker_h

#define PLAYER_POOL 30

#include "BinaryTree.h"
#include "Game.h"
#include "Player.h"
#include <algorithm>
#include <iostream>
#include <map>
#include <queue>
#include <stack>
#include <vector>
#include <set>
#include <unordered_set>
using namespace std;

typedef enum {
  In_Game = 0,
  In_Queue
} player_status;


// template <typename T>
struct ListNode
{
  pair<Player, player_status> *value;
  ListNode *next;
};  

int compute_hash(Player &p){
  return p.hashFunction() % PLAYER_POOL;
}

class ScoreTracker {
private:
  vector<Game> games;
  stack<Game> gameStack; // undo/redo stack
  queue<Game> gameQueue;
  BinaryTree<int> scoreBT;
  
  ListNode *status[PLAYER_POOL];
  
  // unordered_map<Player, *player_status> status;
  // Using Player's Hash, mod it by PLAYER_POOL to get an index
  // Store the Player Status Pointer into this index 

  
   //structure to pair name and score in game vector
  struct PlayerScorePair {
    string name;
    int score;
  };

  //partitioning for quicksort
  int partition(vector<PlayerScorePair> &arr, int low, int high) {
    int pivot = arr[high].score;
    int i = (low - 1);

    for (int j = low; j <= high - 1; j++) {
      if (arr[j].score > pivot) {
        i++;
        swap(arr[i], arr[j]);
      }
    }

    swap(arr[i + 1], arr[high]);
    return (i + 1);
  }

  //quicksort
  //called in public function quickSortGameScores
  void quickSort(vector<PlayerScorePair> &arr, int low, int high) {
    if (low < high) {
      int pivot = partition(arr, low, high);
      quickSort(arr, low, pivot - 1);
      quickSort(arr, pivot + 1, high);
    }
  }

  void populateScoreBT() {
    for (const auto& game : games) {
        for (const auto& player : game.players) {
          // PlayerScorePair pair;
          // pair.name = player.name;
          // pair.score = player.score;
          // scoreBT.insert(pair.score, pair.name);
          scoreBT.insert(player.score);
        }
    }
  }


public:
  // void addgame(const Game& game);

  //Constructor
  
  ScoreTracker(){
    for (int i = 0; i < PLAYER_POOL; i++){
      status[i] = nullptr;
    }
  }

//Avoid using multiple times? Updates the status of a player in the map
  void update_player_status()
  {
    int index;
    ListNode *bucket;
    // In Game Loop, for each player currently playing
    for (Player p : games[0].players)
    {
      index = compute_hash(p);  //Get the Index
      bucket = status[index]; //Set bucket = array where index should be stored
  
      //No Collision, first case
      if (bucket == nullptr) 
      {
        status[index] = new ListNode;
        bucket = status[index]; //Reset after declaring a new head listnode at hash index 
        bucket->value = new pair<Player, player_status>(p, In_Game);
        bucket->next = nullptr;
        continue;
      }
  
      //Collision, search for next available spot within the bucket
      while (bucket->next != nullptr)
      {
        bucket = bucket->next;
      }
      bucket->next = new ListNode;
      bucket->next->value = new pair<Player, player_status>(p, In_Game);
      bucket->next->next = nullptr;
    }
  
    //Hash for all players in queue
      for (Player p : gameQueue.front().players)
      {
        index = compute_hash(p);
        bucket = status[index];
        if (bucket == nullptr)
        {
          status[index] = new ListNode;
          bucket = status[index];
          bucket->value = new pair<Player, player_status>(p, In_Queue);
          bucket->next = nullptr;
          continue;
        }
  
        while (bucket->next != nullptr)
        {
          bucket = bucket->next;
        }
        bucket->next = new ListNode;
        bucket->next->value = new pair<Player, player_status>(p, In_Queue);
        bucket->next->next = nullptr;
      }
  
  }

  //Prints a given player's mapped status
void print_player_status(Player &p){
  // update_player_status();

  int index = compute_hash(p);
  ListNode *bucket = status[index];
  if(bucket == nullptr){
    cout << "Player does not exist" << endl;
    return;
  }

  cout << "Player: " << p.getName() << " is currently: ";
  switch(bucket->value->second){
    case In_Game:
      cout << "In Game." << endl;
      break;
    case In_Queue:
      cout << "In Queue." << endl;
      break;
    default:
      cout << "Error, Player Status:" << bucket->value->second;
      break;
    break;
  }
}

  // Initiate Game Phase
  void startNewGame(const string &gameName) {
    Game newGame(gameName);
    games.push_back(newGame);
    gameStack.push(newGame);
  }

  // Print
  void DisplayCurrentScore() {
    if (!games.empty()) { // Check if players vector is not empty
      games.back().displayScores();
    } else {
      cout << "Empty";
    }
  }

  // Add players to list of already played
  void addPlayerToGame(const Player &player) {

    games.back().addPlayer(player);
    //scoreBT.insert(player.score);
  }

  // Create a new game, add the player into it and add it into queue
  void addtoQueue(const Player &player) {
    // cout << "added to queue" << endl;
    Game newGame("Game Queue: ");
    newGame.addPlayer(player);
    gameQueue.push(newGame);
  }

  // Adds a player into the most recently created game
  void add_recent_queue(const Player &player) {
    gameQueue.back().addPlayer(player);
  }

  // Add players from queue into list of players who have alr played
  void addfromQueue(int score) {
    // Initialize incoming player with score
    gameQueue.front().players.front().setScore(score);

    // Add player at front of queue into current game
    games.back().addPlayer(gameQueue.front().players.front());

    // Remove player that was previously in the queue

    gameQueue.front().players.erase(gameQueue.front().players.begin());

    if(gameQueue.front().players.empty()){
      gameQueue.pop();
    }
  }

  // displays users in the queue
  void displayQueue() {
    queue<Game> copyQueue = gameQueue;

    if (!copyQueue.empty()) {
      while (!copyQueue.empty()) {
        copyQueue.front().displayScores();
        copyQueue.pop();
      }
    } else {
      cout << "Empty";
    }
  }
  // Remove recently added player
  void removeRecentPlayer() {
    if (!games.empty()) {
      games.back().removeLastplayer();
    }
  }
  // add list of moves
  void addListofMoves() {
    string move;

    cout << "Enter 5 moves" << endl;
    for (int i = 0; i < 5; i++) {
      cin >> move;
      games.back().addMove(move);
    }
  }
  // removing a number of moves
  void removeMoves(int num) {
    if (!games.empty()) {
      for (int i = 0; i < num; i++) {
        games.back().undoMove();
      }
    }
  }
  void displayMoves() {
    stack<string> copyof = games.front().playerMoves;
    stack<string> tempstack;
    string hold;
    cout << "Moves:" << endl;
    if (!copyof.empty()) {
      while (!copyof.empty()) {
        hold = copyof.top();
        copyof.pop();
        tempstack.push(hold);
      }
      copyof = tempstack;
      while (!copyof.empty()) {
        cout << copyof.top() << endl;
        copyof.pop();
      }
      cout << endl;
    } else {
      cout << "Empty" << endl;
    }
  }

  // Sorting scores using quick sort function(greatest to least)
  void quickSortGameScores() {
    vector<PlayerScorePair> scores;
    for (const auto &game : games) {
      for (const auto &player : game.players) {
        PlayerScorePair pair;
        pair.name = player.name;
        pair.score = player.score;
        scores.push_back(pair);
      }
    }

    quickSort(scores, 0, scores.size() - 1);

    cout << "Sorted Scores(from highest): " << endl;
    
    auto It = scores.begin();
    for (auto &game : games) {
      for (auto &player : game.players) {
        player.name = It->name;
        player.score = It->score;
        It++;
        cout << player.name << ": " << player.score << endl;
      }
    }
  }

  //binary tree implementation
  //sort scores(least to greatest using in-order traversal)
void printSortedScoresBT() {
    populateScoreBT();
    vector<int> sortedScores = scoreBT.inOrderTraversal();

    cout << "Sorted Scores(from lowest):" << endl;
    set<pair<string, int>> uniquePlayerScores;  // To store unique player-score pairs

    for (int score : sortedScores) {
        // Find all players with the current score
        for (const auto& game : games) {
            for (const auto& player : game.players) {
                if (player.score == score) {
                    // Store the player-score pair in the set
                    uniquePlayerScores.insert({player.name, player.score});
                }
            }
        }
    }

    // Convert the set to a vector for sorting
    vector<pair<string, int>> sortedPlayerScores(uniquePlayerScores.begin(), uniquePlayerScores.end());

    // Sort the vector based on scores in ascending order
    sort(sortedPlayerScores.begin(), sortedPlayerScores.end(), [](const auto& a, const auto& b) {
        return a.second < b.second;
    });

    // Print the sorted player-score pairs
    for (const auto& playerScore : sortedPlayerScores) {
        cout << playerScore.first << ": " << playerScore.second << endl;
    }
}


};

#endif