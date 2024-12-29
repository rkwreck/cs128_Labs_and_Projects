#include <algorithm>
#include <cmath>
#include <iostream>
#include <stdexcept>
#include <vector>

#include "motif_node.hpp"

// using namespace std;

// REQUIRES: motif is not empty
// MODIFIES:
// EFFECTS : Returns a score [0, 100] evaluating how melodic the motif is
//           by taking the result of CalculateHarmonicScore and normalizing it.
//           Normalizing = (harmonic_score - worst_score_possible) /
//           (best_score_possible - worst_score_possible) * 100;
// Optional extension: Also evaluate the rhythmic score
double CalculateFitnessScore(const vector<Note>& motif){
  double harmonic_score = CalculateHarmonicScore(motif);

  //min (worst score possible), every place you subtract: -147      
  int worst_score_possible = -147; 

  //max (best score possible), every place you add: 99
  int best_score_possible = 99; 

  double normalizing = ((harmonic_score - (worst_score_possible)) /
  (best_score_possible - worst_score_possible)) * 100;
  return normalizing; 
}


// REQUIRES: motif is not empty
// MODIFIES:
// EFFECTS : Returns a score evaluating how good of a motif it
//           is based on harmonic attributes.
// This function is written for you. I recommend not changing it until 
// you are done with the MP. 
double CalculateHarmonicScore(const vector<Note>& motif) {
  double harmonic_score = 0.0;

  for (int i = 0; i < motif.size(); ++i) {
    int note_ = motif[i].pitch % 12;  // Modulo 12 for octave equivalence
    // C major notes
    if (note_ == 0 || note_ == 2 || note_ == 4 || note_ == 5 || note_ == 7 ||
        note_ == 9 || note_ == 11) {
      harmonic_score += rand() % 10;
    }
    // other notes 
    else {
      harmonic_score -= rand() % 10;
    }
  }

  for (int i = 1; i < motif.size(); ++i) {
    int interval = abs(motif[i].pitch - motif[i - 1].pitch) %
                   12;  // Modulo 12 for octave equivalence
    // bad sounding intervals
    if (interval == 1 || interval == 6 || interval == 10) {
      harmonic_score -= rand() % 10;
    } 
    // good sounding intervals
    else if (interval == 7 || interval == 5 || interval == 4) {
      harmonic_score += rand() % 10;
    }
  }

  // Incentive motifs have nice pitches
  for (const auto& note : motif) {
    if (note.pitch < kMinAcceptablePitch || note.pitch > kMaxAcceptablePitch) {
      harmonic_score -=
          rand() %
          5;  // Penalize motifs with pitches outside the acceptable range
    }
    if (note.pitch < kExtrMinAcceptablePitch ||
        note.pitch > kExtrMaxAcceptablePitch) {
      harmonic_score -=
          rand() %
          5;  // Penalize motifs with pitches outside the acceptable range
    }
  }
  return harmonic_score;
}


// REQUIRES:
// MODIFIES: MotifNode
// EFFECTS : Initializes this MotifNode with a given motif and calculates
//           and stores its fitness score.
MotifNode::MotifNode(const vector<Note>& motif){
  //This is the constructor 
  parent_ = nullptr; //default is technically nullptr 
  motif_ = motif; 
  fitness_score_ = CalculateFitnessScore(motif); 
}

// REQUIRES: new_child points to a valid non null MotifNode
// MODIFIES: MotifNode and new_child
// EFFECTS : Adds the new_child to this MotifNode's children.
void MotifNode::AddChildNode(MotifNode* new_child){
  //edge case 
  if (new_child == nullptr){
    return;  //do nothing 
  }
  //add the new child to the children_ vector
  children_.push_back(new_child); 

  //set the new_child parent's node as this 
  new_child->parent_ = this;
}

// REQUIRES: new_child points to a valid non null MotifNode that is NOT
//           currently a child of this MotifNode and old_child points to a
//           valid non null MotifNode that IS currently a child of this
//           MotifNode.
// MODIFIES: MotifNode, new_child, and old_child
// EFFECTS : Replaces the old_child with the new_child.
bool MotifNode::ReplaceChildNode(MotifNode* new_child, MotifNode* old_child){
  //edge case 
  if (new_child == nullptr){
    return true;  //do nothing 
  }
  
  //this is all correct BUT it assumes old_child is in children vector
  //so we have to move it to a for loop first
  // //set the new_child's parent to be this
  // new_child->parent_ = old_child->parent_;

  // //get the index of the old_child
  // //this assumes that old child is in children_vector
  
  // int index = 0; 
  // while (children_[index] != old_child){
  //   index++; 
  // } 

  // //replace old_child with new_child BY INDEX
  // children_[index] = new_child;

  // delete old_child; 

  // return true; 

  //use a for loop instead to make sure that old_child is actually in the children vector
  for (int i = 0; i < children_.size(); i++){
    if (children_[i] == old_child){
      new_child->parent_ = old_child->parent_; 
      children_[i] = new_child; 

      delete old_child; 
      return true; 
    }
  }

  //default
  return false; 


}

// REQUIRES: node points to a valid non null MotifNode that IS currently
//           a child of this MotifNode
// MODIFIES: This MotifNode, node
// EFFECTS : Removes node from the MotifNode's children.
bool MotifNode::RemoveChildNode(MotifNode* node){
  //same thing here, make it a for loop
  for (int index = 0; index < children_.size(); index++){
    if (children_[index] == node){
      children_.erase(children_.begin() + index); 
      delete node;
      return true; 
    }
    //index++; 
  }
  return false; 
}


  //find the index of node
//   int index = 0; 
//   while (children_[index] != node){
//     index++; 
//   }
//   //remove the index
//   children_.erase(children_.begin() + index); 
//   return true; 
// }

// REQUIRES:
// MODIFIES: MotifNode
// EFFECTS : Sets the parent of this MotifNode to nullptr.
void MotifNode::SetNullParent(){
  parent_ = nullptr; 

}

// REQUIRES:
// MODIFIES:
// EFFECTS : Returns the parent of this MotifNode.
MotifNode* MotifNode::GetParentNode() const{
  return parent_; 

}

// REQUIRES:
// MODIFIES:
// EFFECTS : Returns the motif of this MotifNode.
const vector<Note>& MotifNode::GetMotif() const{
  return motif_; 

}

// REQUIRES:
// MODIFIES:
// EFFECTS : Returns the children of this MotifNode
const vector<MotifNode*>& MotifNode::GetChildren() const{
  return children_; 
}

// REQUIRES:
// MODIFIES:
// EFFECTS : Returns a the fitness score of this MotifNode
double MotifNode::GetFitnessScore() const{
  return this->fitness_score_; 

}

// REQUIRES:
// MODIFIES:s
// EFFECTS : Sets the fitness score of this MotifNode
//           USED ONLY FOR TESTING. DO NOT CHANGE THE FITNESS
//           SCORE IN YOUR MUSICAL TREE ALGORITHM
void MotifNode::SetFitnessScore(double val){
  fitness_score_ = val; 
}







///////  IGNORE THIS


/*

// REQUIRES: new_child points to a valid non null MotifNode
// MODIFIES: MotifNode and new_child
// EFFECTS : Adds the new_child to this MotifNode's children.
void MotifNode::AddChildNode(MotifNode* new_child){
  //edge case 
  if (new_child == nullptr){
    return;  //do nothing 
  }

  //set the parent 
  MotifNode* parental = children_[children_.size() - 1]; 
  new_child->parent_ = parental; 

  //do we need to change the previous child's pointer to point to new child??
  //and if so, how?? 

  children_.push_back(new_child); 
}

// REQUIRES: new_child points to a valid non null MotifNode that is NOT
//           currently a child of this MotifNode and old_child points to a
//           valid non null MotifNode that IS currently a child of this
//           MotifNode.
// MODIFIES: MotifNode, new_child, and old_child
// EFFECTS : Replaces the old_child with the new_child.
bool MotifNode::ReplaceChildNode(MotifNode* new_child, MotifNode* old_child){
  //grab the parent of the old_child
  //first figure out what index old_child is at
  int index = 0; 
  while (children_[index] != old_child){
    index++; 
  } 

  //set that to be the parent of the new_child
  MotifNode* parental = children_[index - 1]; 
  new_child->parent_ = parental; 

  //replace old_child with new_child BY INDEX
  children_[index] = new_child; 
  
  //delete old_child; 
  delete old_child; 

}


*/