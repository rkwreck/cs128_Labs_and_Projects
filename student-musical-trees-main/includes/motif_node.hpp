#ifndef MOTIF_NODE_HPP
#define MOTIF_NODE_HPP

#include <algorithm>
#include <cmath>
#include <ctime>
#include <iostream>
#include <stdexcept>
#include <vector>

using namespace std;

constexpr int kMinAcceptablePitch = 60;
constexpr int kMaxAcceptablePitch = 72;

constexpr int kExtrMinAcceptablePitch = 50;
constexpr int kExtrMaxAcceptablePitch = 80;

struct Note {
  int pitch;
  double duration;
  Note(int p, double d): pitch(p), duration(d) {}
};

// REQUIRES: motif is not empty
// MODIFIES:
// EFFECTS : Returns a score [0, 100] evaluating how melodic the motif is
//           by taking the result of CalculateHarmonicScore and normalizing it.
//           Normalizing = (harmonic_score - worst_score_possible) /
//           (best_score_possible - worst_score_possible) * 100;
// Optional extension: Also evaluate the rhythmic score
double CalculateFitnessScore(const vector<Note>& motif);

// REQUIRES: motif is not empty
// MODIFIES:
// EFFECTS : Returns a score evaluating how good of a motif it
//           is based on harmonic attributes.
double CalculateHarmonicScore(const vector<Note>& motif);

class MotifNode {
public:
  // REQUIRES:
  // MODIFIES: MotifNode
  // EFFECTS : Initializes this MotifNode with a given motif and calculates
  //           and stores its fitness score.
  MotifNode(const vector<Note>& motif);

  // REQUIRES: new_child points to a valid non null MotifNode
  // MODIFIES: MotifNode and new_child
  // EFFECTS : Adds the new_child to this MotifNode's children.
  void AddChildNode(MotifNode* new_child);

  // REQUIRES: new_child points to a valid non null MotifNode that is NOT
  //           currently a child of this MotifNode and old_child points to a
  //           valid non null MotifNode that IS currently a child of this
  //           MotifNode.
  // MODIFIES: MotifNode, new_child, and old_child
  // EFFECTS : Replaces the old_child with the new_child.
  bool ReplaceChildNode(MotifNode* new_child, MotifNode* old_child);

  // REQUIRES: node points to a valid non null MotifNode that IS currently
  //           a child of this MotifNode
  // MODIFIES: This MotifNode, node
  // EFFECTS : Removes node from the MotifNode's children.
  bool RemoveChildNode(MotifNode* node);

  // REQUIRES:
  // MODIFIES: MotifNode
  // EFFECTS : Sets the parent of this MotifNode to nullptr.
  void SetNullParent();

  // REQUIRES:
  // MODIFIES:
  // EFFECTS : Returns the parent of this MotifNode.
  MotifNode* GetParentNode() const;

  // REQUIRES:
  // MODIFIES:
  // EFFECTS : Returns the motif of this MotifNode.
  const vector<Note>& GetMotif() const;

  // REQUIRES:
  // MODIFIES:
  // EFFECTS : Returns the children of this MotifNode
  const vector<MotifNode*>& GetChildren() const;

  // REQUIRES:
  // MODIFIES:
  // EFFECTS : Returns a the fitness score of this MotifNode
  double GetFitnessScore() const;

  // REQUIRES:
  // MODIFIES:
  // EFFECTS : Sets the fitness score of this MotifNode
  //           USED ONLY FOR TESTING. DO NOT CHANGE THE FITNESS
  //           SCORE IN YOUR MUSICAL TREE ALGORITHM
  void SetFitnessScore(double val);

private:
  vector<Note> motif_;

  double fitness_score_;

  vector<MotifNode*> children_;

  MotifNode* parent_;
};

#endif
