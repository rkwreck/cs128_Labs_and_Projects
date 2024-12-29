#ifndef MUSICAL_TREE_HPP
#define MUSICAL_TREE_HPP

#include <algorithm>
#include <cmath>
#include <ctime>
#include <iostream>
#include <stdexcept>
#include <vector>

#include "motif_node.hpp"

using namespace std;

class MusicalTree {
public:
  //------------------REQUIRED------------------------
  // REQUIRES:
  // MODIFIES: This MusicalTree
  // EFFECTS : Initializes the MusicalTree with a root node
  // Part 1
  MusicalTree(bool verbose);

  // REQUIRES: This MusicalTree is valid
  // MODIFIES: This MusicalTree
  // EFFECTS : Runs the entire genetic algorithm by evolving and pruning the
  //           tree per the number of generations passed in
  void GeneticAlgorithm(int numGenerations);

  // REQUIRES: This MusicalTree is valid
  // MODIFIES:
  // EFFECTS : Returns a single vector of all the motifs in the tree
  std::vector<Note> GenerateMelody();

  // REQUIRES: This MusicalTree is valid
  // MODIFIES: This MusicalTree
  // EFFECTS : Removes all nodes from the tree that have a motif with a fitness
  // level below the threshold. See specifications for exact algorithm required.
  // If tree is the root and tree has no children, do nothing. 
  // DO NOT check the size_ in this function (it will break the autograder)
  // However, you may and should update the size_ in this function.
  // Part 1
  void PruneNodes(MotifNode* tree, double threshold);

  // Part 1
  ~MusicalTree();

  // USED FOR TESTING, already implemented
  MotifNode* GetRoot() const {return root_;}
  int GetSize() const { return size_; }

  //----------------------------------------------------
  // Add more functions here

private:
  //--------A few recommended functions below-----------

  // REQUIRES: This MusicalTree is valid
  // MODIFIES:
  // EFFECTS : This function validates that the tree starting at root is valid.
  //           I recommend using this function to debug your code.
  void ValidateTree(MotifNode* node);

  // REQUIRES: This MusicalTree is valid
  // MODIFIES: melody
  // EFFECTS : Traverses the tree and adds motifs to the melody
  //           hint: This is a helper function for implementing
  //                 GenerateMelody()
  void TraverseTree(MotifNode* node, vector<Note>& melody);

  //-------------- REQUIRED -------------------------
  MotifNode* root_;
  int size_;
  bool verbose_;
  //----------------------------------------------------
};

#endif
