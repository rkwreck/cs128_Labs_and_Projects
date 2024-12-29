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

  MusicalTree(bool verbose, MotifNode* node_);

  MusicalTree(bool verbose, MotifNode* node_, int size);


  //to assist us in deep copying in the assignment & copy constructors
  MotifNode* DeepCopy(MotifNode* tree){
    if (tree == nullptr){
      return nullptr; 
    }
    MotifNode* current = new MotifNode(tree->GetMotif()); 
    vector<MotifNode*> children = tree->GetChildren();
    for (MotifNode* child : children){
      current->AddChildNode(DeepCopy(child)); 
    }
    return current; 
  }

  //assignment operator -- BIG THREE, I ADDED
  MusicalTree& operator=(const MusicalTree& other){
    //check for self-assignment
    if (this == &other){
      return *this; 
    }
    //delete lhs 
    DestructHelper(root_);

    //shallow & deep copy 
    root_ = DeepCopy(other.GetRoot()); 

    //return *this 
    return *this; 
  }

  //copy constructor -- BIG THREE, I ADDED
  MusicalTree(MusicalTree& other){
    //shallow copy everything
    size_ = other.size_; 
    verbose_ = other.verbose_; 
    //deep copy 
    root_ = DeepCopy(other.GetRoot()); 
  }

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

  void Prune_Helper(double threshold, vector<MotifNode*> children, MotifNode* current_node); 

  void RotationHelper(vector<MotifNode*> children, MotifNode* parent_node);


  // Part 1
  ~MusicalTree();

  // USED FOR TESTING, already implemented
  MotifNode* GetRoot() const {return root_;}
  int GetSize() const { return size_; }

  // MY FUNCTIONS
  void DestructHelper(MotifNode* node_);  //this is basically a pop-all function

  void setRoot(MotifNode* node) {root_ = node; }

  void PrintTree(MotifNode* current_);


private:

  //MY OWN FUNCTION
 //bool CheckInvariants(); 


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
