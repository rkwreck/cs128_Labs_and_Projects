#include <algorithm>
#include <cmath>
#include <iostream>
#include <stdexcept>
#include <vector>
#include <map>

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
  //double harmonic_score = CalculateHarmonicScore(motif);
  double harmonic_score = CalculateHarmonicScore_A_MINOR_DURATION_PITCH(motif); 

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


///// MY EXTRA CREDIT ADJUSTMENT
// changes scale + uses different method 
double CalculateHarmonicScore_A_MINOR_DURATION_PITCH(const vector<Note>& motif) {
  double harmonic_score = 0.0;

  // No changes 
  for (int i = 0; i < motif.size(); ++i) {
    int note_ = motif[i].pitch % 12;  // Modulo 12 for octave equivalence
    // A minor notes (same as C major)
    if (note_ == 0 || note_ == 2 || note_ == 4 || note_ == 5 || note_ == 7 ||
        note_ == 9 || note_ == 11) {
      harmonic_score += rand() % 10; 
    }
    // other notes 
    else {
      harmonic_score -= rand() % 10;
    }
  }

  // Kept the same, just changed the intervals 
  for (int i = 1; i < motif.size(); ++i) {
    int interval = abs(motif[i].pitch - motif[i - 1].pitch) % 12;  // Modulo 12 for octave equivalence
    // bad sounding intervals (DIFFERENT FOR A MINOR SCALE)
    if (interval == 1 || interval == 2 || interval == 6 || interval == 10 || interval == 11) {
      harmonic_score -= rand() % 10;   
    } 
    // good sounding intervals (DIFFERENT FOR A MINOR SCALE)
    else if (interval == 0 || interval == 7 || interval == 12 || interval == 4 || interval == 3 || interval == 9 || interval == 8 || interval == 5) {
      harmonic_score += rand() % 10;    
    }
  }

  // We will use this vector later
  vector<int> pitches_count; 

  // I ADDED THIS -- We penalize notes with the wrong pitches much more if they have a longer duration. Long duration is defined as greater than 0.5 seconds
  for (const auto& note: motif){

    //add the pitch to the vector, we'll need this later -- I ADDED THIS PART
    pitches_count.push_back(note.pitch); 

    //so first we check if a note has a long duration or not -- I ADDED THIS PART
    bool long_duration_flag = false; 
    if (note.duration > 0.5){
      long_duration_flag = true; 
    }

    if (note.pitch < kMinAcceptablePitch || note.pitch > kMaxAcceptablePitch) { // Penalize motifs with pitches outside the acceptable range
      if (long_duration_flag == true){  // CHECK FOR DURATION -- I ADDED THIS PART 
        harmonic_score -= rand() % 10; 
      } else {
        harmonic_score -= rand() % 5;   //short duration 
      }
    }
    if (note.pitch < kExtrMinAcceptablePitch || note.pitch > kExtrMaxAcceptablePitch) {
      if (long_duration_flag == true){  // CHECK FOR DURATION -- I ADDED THIS PART 
        harmonic_score -= rand() % 10; 
      } else {
        harmonic_score -= rand() % 5;   //short duration 
      }
    }
  }

  // I ADDED THIS -- We penalize motifs that are too repetitive with their pitch
  for (int i = 0; i < pitches_count.size(); i++){
    int count = 0; 
    for (int j = 0; j < pitches_count.size(); j++){
      if (i != j){ //make sure we don't double count the same pitch
        if (pitches_count[i] == pitches_count[j]){
          count++; 
        }
      }
    }
    if (count > 2){
      harmonic_score -= rand() % 1; 
    } else {
      harmonic_score += rand() % 1; 
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


// A Minor scale & Entropy Calculation (FAILED)
/* 
double CalculateHarmonicScore_ENTROPY_A_MINOR_SCALE(const vector<Note>& motif) {
  double harmonic_score = 0.0;

  for (int i = 0; i < motif.size(); ++i) {
    int note_ = motif[i].pitch % 12;  // Modulo 12 for octave equivalence
    // A minor notes (same as C major)
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
    if (interval == 1 || interval == 2 || interval == 6 || interval == 10 || interval == 11) {
      harmonic_score -= rand() % 10;   
    } 
    // good sounding intervals
    else if (interval == 0 || interval == 7 || interval == 12 || interval == 4 || interval == 3 || interval == 9 || interval == 8 || interval == 5) {
      harmonic_score += rand() % 10;    
    }
  }

  //go through each Note in the motif
  //grab that Note's pitch 
  //see if it's already in the map, update the map accordingly
  //once we're done iterating through the list of notes, calculate the probability 
  
    
  // PENALIZE PITCHES THAT DON'T SOUND NICE, USING ENTROPY ALGORITHM 

  //store each pitch and its count 
  map<int, int> pitches_count; 
  for (const auto& note : motif){ //go through each note in our motif 
    pitches_count[note.pitch]++;  //see how many times each pitch appears 
  }

  //now we need to calculate the probabilities and calculate the sum/entropy
  int entropy = 0; 
  for (auto start = pitches_count.begin(); start != pitches_count.end(); start++){
    int prob = (start->second) / pitches_count.size(); 
    entropy += (prob) * log2(prob); 
  }

  //penalize a high entropy score 
  if (entropy > )

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
*/ 


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




/* ARCHIVE (old code)

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