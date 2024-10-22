
#include <iostream>
#include "BinaryTree.h"
#include "Player.h"
#include "Game.h"
#include "ScoreTracker.h"

using namespace std;

// TODO:
// -HASHING

int main() {
  ScoreTracker st;
  BinaryTree<int> bt;
  string gameName = "Tetris";
  
  st.startNewGame(gameName);
  
  //Active Players
  Player p1("Billy", 20);
  Player p2("John", 50);
  Player p3("Kam", 40);
  Player p4("Steve", 80);
  Player p5("Eric", 10);

  //Queued Players
  Player q1("Tim", 0);
  Player q2("Kim", 0);
  Player q3("Test", 30);
  

  st.addPlayerToGame(p1);
  st.addPlayerToGame(p2);
  st.addPlayerToGame(p3);
  st.addPlayerToGame(p4);
  st.addPlayerToGame(p5);
  st.DisplayCurrentScore(); 

  st.addtoQueue(q1);
  st.add_recent_queue(q2);
  st.add_recent_queue(q3);

  st.displayQueue();
  
  cout << "Adding Tim into Game..." << endl;
  st.addfromQueue(50);
  cout << "New Player List: " << endl;
  st.DisplayCurrentScore();
  cout << endl;
  st.displayQueue();
  //Sort Game scores through quicksort
  st.quickSortGameScores();

  st.update_player_status();
  st.print_player_status(p1);
  st.print_player_status(q2);


  //Sort Game scores through using inOrderTravesal in binary tree
  st.printSortedScoresBT();
  
  // //Allows user to add moves into the stack
  // st.addListofMoves();
  // st.displayMoves();
  // //removes the 3 most recent moves
  // st.removeMoves(3);
  // st.displayMoves();


  bt.insert(p1.getScore());
  bt.insert(p2.getScore());
  bt.insert(p3.getScore());
  bt.insert(p4.getScore());
  bt.insert(p5.getScore());
  bt.insert(q1.getScore());
  bt.insert(q2.getScore());

  


  cout<< "Searching for Score: " << endl; 
  if(bt.search(bt.root, 80) != nullptr){
    TreeNode<int>* result = bt.search(bt.root, 80);
    cout << "Number Found: " << result->data << endl;
  }
  else {
    cout << "Not found" << endl;
  }
}