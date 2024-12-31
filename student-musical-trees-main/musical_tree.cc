#include "musical_tree.hpp"
#include <cassert>

#include <cstdlib> 
#include <ctime> 
#include <vector> 

#include <sstream> 

#define PRE_EVOLVE_LOOP 4
#define EVOLVE_LOOP     1
#define THRESHOLD_STEP  5
#define DEBUGGING 1
// using namespace std;

//MY OWN FUNCTION
void MusicalTree::CheckInvariants(){
  cout << "starting CHECK INVARIANTS call" << endl; 
  #if DEBUGGING
  // 1. Size is never less than 1, root node is always valid
  assert (size_ >= 1 && "size is less than 1"); 

  // 2. The root node's parent pointer is equal to nullptr
  assert ((root_->GetParentNode() == nullptr) && "root's parent node is not nullptr"); 

  //3 & 4. Every node, except the root, has exactly 1 parent and is inside of the children vector of that parent.
  assert (CheckParent(root_)); 

  // 5. The size of the tree is the number of valid MotifNodes connected through the root.
  int size = 0;
  CalculateSize(root_, size); 
  cout << "in INVARIANTS, root_: " << to_string(root_->GetFitnessScore()) << ", size_: " << to_string(size_) << endl; 
  cout << "in INVARIANTS, this is output of CalculateSize: " << to_string(size) << endl; 
  assert (size_ == size); 
  #endif
}

bool MusicalTree::CheckParent(MotifNode* tree){
  //get thru the tree 
  for (MotifNode* child : tree->GetChildren()){
    return CheckParent(child); 
  }
  if (tree != root_){
    //are you in your parent's children vector? 
    MotifNode* trees_parent = tree->GetParentNode(); 
    for (MotifNode* kid : trees_parent->GetChildren()){
      if (kid == tree){
        return true; 
      }
    } 
    return false;
  }
  return true; 
}

// int MusicalTree::CheckSize_old(MotifNode* tree){
  //   cout << "starting call, this is the node: " << to_string(tree->GetFitnessScore()) << endl; 
  //   if (tree->GetChildren().size() == 0){ 
  //     return 1;
  //   }
  //   for (MotifNode* kid : tree->GetChildren()){
  //     cout << __LINE__ << " this is kid: " << to_string(kid->GetFitnessScore()) << endl; 
  //     return 1 + CheckSize(kid); 
  //   }
  //   return 0; 
  // }

void MusicalTree::CalculateSize(MotifNode* tree, int& size){
  size++;
  //cout << "starting CALCULATE SIZE call, root_ : " << to_string(root_->GetFitnessScore()) << endl;
  //cout << "starting CHECK SIZE call, this is tree: " << to_string(tree->GetFitnessScore()) << endl; 

  //cout << "this is how many children " << to_string(tree->GetFitnessScore()) << " has: " << to_string(tree->GetChildren().size()) << endl; 
  for (MotifNode* kid : tree->GetChildren()){
    //cout << "inside CHECK SIZE for loop, this is kid: " << to_string(kid->GetFitnessScore()) << " of " << to_string(tree->GetFitnessScore())<< endl; 
    // cout << "this is the current size: " << to_string(size) << endl; 
    CalculateSize(kid,size); 
  }

  //cout << "finished call, this is size: " << to_string(size) << endl; 
}

//------------------REQUIRED------------------------

// REQUIRES:
// MODIFIES: This MusicalTree
// EFFECTS : Initializes the MusicalTree with a root node
// Part 1
MusicalTree::MusicalTree(bool verbose){  
  //root_ = nullptr;

  Note note_0 = Note(0, 0); 
  vector<Note> root_motif; 
  root_motif.push_back(note_0); 

  MotifNode* node_0 = new MotifNode(root_motif);
  root_ = node_0; 

  verbose_ = verbose; 
  size_ = 1; 
}

MusicalTree::MusicalTree(bool verbose, MotifNode* node_){  
  root_ = node_;
  verbose_ = verbose; 
  size_ = 1; 
}

MusicalTree::MusicalTree(bool verbose, MotifNode* node_, int size){  
  root_ = node_;
  verbose_ = verbose; 
  size_ = size; 
}

// REQUIRES: This MusicalTree is valid
// MODIFIES: This MusicalTree
// EFFECTS : Runs the entire genetic algorithm by evolving and pruning the
//           tree per the number of generations passed in
void MusicalTree::GeneticAlgorithm(int numGenerations){
  stringstream ss; 

  //pre-evolve 
  for (int i = 0; i < PRE_EVOLVE_LOOP; i++){
    vector<MotifNode*> pre_evolve = SelectionPhase(); 
    CheckInvariants(); 
    ReproductionPhase(pre_evolve);
    CheckInvariants(); 
  }

  double threshold = 10; 
  //build generations
  for (int i = 0; i < numGenerations; i++){
    for (int i = 0; i < EVOLVE_LOOP; i++){
      vector<MotifNode*> selections = SelectionPhase(); 
      CheckInvariants(); 
      ReproductionPhase(selections);
      CheckInvariants(); 
    }
    while (size_ > 200){
      PruneNodes(root_, threshold);
      CheckInvariants(); 
      threshold++; 
    }
  }

  ss << "Final Prune " << size_ << endl;
  PrintFunction(ss); 

  //final prune
  while (size_ > 2){
    PruneNodes(root_, threshold);
    CheckInvariants(); 
    //threshold += 0.01; 
    threshold += THRESHOLD_STEP; 
  }
}

// CONTROLS VERBOSE 
void MusicalTree::PrintFunction(stringstream& output){
  if (verbose_){
    cout << output.str(); 
  }
  output.str(string()); //clears the stream 
}

// I ADDED THIS FUNCTION
vector<MotifNode*> MusicalTree::SelectionPhase(){
  //create a stream for verbose print functions 
  stringstream ss; 
  ss << "SelectNodes: " << endl; 
  PrintFunction(ss); 
 
  //find the max fitness score of the tree
  double maxFitnessScore = -1; 
  FindMaxFitness(root_, maxFitnessScore);

  //now select 
  vector<MotifNode*> selectedNodes; 
  SelectionHelper(root_, maxFitnessScore / 100, selectedNodes, ss); 

  return selectedNodes; 
}

// ALSO ADDED THIS, helper function for selection
void MusicalTree::SelectionHelper(MotifNode* node_, double maxFitness, vector<MotifNode*>& selectedNodes, stringstream& ss){
  //get the selection probability, between 0 & 1
  srand(time(0)); //seed for random later
  double selectionProb = ((double)rand()) / RAND_MAX;

  ss << "node: "; 

  //printing requirement
  for (unsigned int i = 0; i < node_->GetMotif().size(); i++) {
    ss << node_->GetMotif()[i].pitch << "-" << node_->GetMotif()[i].duration << " "; 
    //PrintFunction(ss); 
  }
  ss << endl; 
  //PrintFunction(ss); 
  ss << "  Fitness_Score: " << node_->GetFitnessScore() << endl;
  ss << "  Selection Prob: " << selectionProb << endl;

  if (selectionProb < maxFitness || selectionProb < 0.10){
    //node has been selected
    //PrintFunction(ss); 
    selectedNodes.push_back(node_);
    ss << "  Selected" << endl;
  } else {
    ss << "  Not Selected" << endl; 
  }

  PrintFunction(ss); 

  for (MotifNode* child : node_->GetChildren()){ //check all children
    SelectionHelper(child, maxFitness, selectedNodes, ss);
  }
}

// I ADDED THIS FUNCTION TOO
void MusicalTree::FindMaxFitness(MotifNode* node_, double& max){ 
  //if node_ fitness score > max --> max = fitness score 
  if (node_->GetFitnessScore() > max){
    max = node_->GetFitnessScore(); 
  }
  for (MotifNode* child : node_->GetChildren()){
    FindMaxFitness(child, max);
  }
}

void MusicalTree::ReproductionPhase(vector<MotifNode*> selectedNodes){ 
  stringstream ss; 
  for (MotifNode* node_ : selectedNodes){ //for each selected node

    //printing requirements
    ss << "Reproduce: ";
    for (unsigned int i = 0; i < node_->GetMotif().size(); i++) {
      ss << node_->GetMotif()[i].pitch << "-" << node_->GetMotif()[i].duration << " ";
    }
    ss << endl;

    vector<Note> childMotif; //to store the child's notes
    for (Note parent_note : node_->GetMotif()){ //for each note in the parent's note vector 
      //generate a new pitch
      int parent_pitch = parent_note.pitch; 
      int newPitch = parent_pitch + (-2 + (rand() % 2)); //randomly select number from -2 to 2 
      if (newPitch < 0){
        newPitch = 0; 
      } 
      if (newPitch > 127){
        newPitch = 127; 
      }

      //generate a new duration
      double parent_duration = parent_note.duration; 
      double newDuration = parent_duration + ((-10 + (rand() % 10)) / 100);  //randomly select number from -0.1 to 0.1 
      if (newDuration < 0.1){
        newDuration = 0.1; 
      } 
      if (newDuration > 0.7){
        newDuration = 0.7; 
      }

      //generate a new note for the child
      Note child_note = Note(newPitch, newDuration); 
      childMotif.push_back(child_note); //add each note to the child's Motif vector
    }
    //create a new child 
    MotifNode* child_node = new MotifNode(childMotif); 
    node_->AddChildNode(child_node); 
    size_++; 

    //printing requirements
    ss << " Child: ";
    for (unsigned int i = 0; i < childMotif.size(); i++) {
      ss << childMotif[i].pitch << "-" << childMotif[i].duration << " ";
    }
    ss << endl;
  }

  PrintFunction(ss); 
}

// REQUIRES: This MusicalTree is valid
// MODIFIES:
// EFFECTS : Returns a single vector of all the motifs in the tree
std::vector<Note> MusicalTree::GenerateMelody(){
  vector<Note> all_motifs; 
  GenerateMelody_Helper(all_motifs, root_);
  return all_motifs;  
}

void MusicalTree::GenerateMelody_Helper(vector<Note>& all_motifs, MotifNode* tree){
  for (MotifNode* child: tree->GetChildren()){
    GenerateMelody_Helper(all_motifs, child); 
  }
  for (Note note_ : tree->GetMotif()){
    all_motifs.push_back(note_);
  }
}

// REQUIRES: This MusicalTree is valid
// MODIFIES: This MusicalTree
// EFFECTS : Removes all nodes from the tree that have a motif with a fitness
// level below the threshold. See specifications for exact algorithm required.
// If tree is the root and tree has no children, do nothing. 
// DO NOT check the size_ in this function (it will break the autograder)
// However, you may and should update the size_ in this function.
// Part 1
void MusicalTree::PruneNodes(MotifNode* tree, double threshold){
  vector<MotifNode*> tree_children = tree->GetChildren(); //grab the original child vector

  stringstream ss; 
  ss << "PRUNE " << endl;
  ss << " size: " << size_ << endl;
  Prune_Helper(threshold, tree_children, tree); 

  //printing requirements
  ss << "  prune cutoff: " << threshold << endl;
  ss << "  size: " << size_ << endl;
  PrintFunction(ss); 
  
}

void MusicalTree::Prune_Helper(double threshold, vector<MotifNode*> children, MotifNode* current_node){
  //cout << "starting call, in PRUNE HELPER" << endl; 
  //if it's the last node, don't do anything 
  if (current_node->GetParentNode() == nullptr && children.size() == 0){
    return; 
  }

  //base case: if you have no children, just delete the node
  if ((children.size() == 0) && current_node->GetFitnessScore() < threshold){
    //before we delete, remove the node from whatever children vector it's in 
    //cout << __LINE__ << " removing node: " << to_string(current_node->GetFitnessScore()) << endl; 
    current_node->GetParentNode()->RemoveChildNode(current_node);
     
    size_--; 
    //cout << __LINE__ << " now the size_ is: " << to_string(size_) << endl;
  } else {
    for (MotifNode* child : children){
      //cout << __LINE__ << " going into recursive call, size = " << to_string(size_) << endl; 
      Prune_Helper(threshold, child->GetChildren(), child); //check the children
      //cout << __LINE__ << " after  recursive call, size = " << to_string(size_) << endl; 
    }
    if (current_node->GetFitnessScore() < threshold){
      //cout << __LINE__ << " removing node: " << to_string(current_node->GetFitnessScore()) << endl; 
      RotationHelper(current_node->GetChildren(), current_node); //rotate & delete current_node
      //cout << __LINE__ << " now the size_ is: " << to_string(size_) << endl;
      //size_--; 
      //cout << __LINE__ << " now the size_ is: " << to_string(size_) << endl;
    }
  }
}

void MusicalTree::RotationHelper(vector<MotifNode*> parents_children, MotifNode* parent_node){
  //if we have a leaf and it needs to be pruned, just delete it 
  if (parents_children.size() == 0){
    if (parent_node->GetParentNode() == nullptr){ //if it's the root, DON'T delete it 
    } else{ 
      parent_node->GetParentNode()->RemoveChildNode(parent_node); 
      //cout << __LINE__ << " entered this line " << endl; 
      size_--; 
    }
    return; 
  } 

  //cout << __LINE__ << "   size = " << to_string(size_) << endl; 
  //the last child in the parents' children vector, D in sibling list <A, B, C, D> 
  MotifNode* last_child = parents_children[parents_children.size() - 1]; 

  //adopt all your siblings, make sure not to add yourself
  for (int i = 0; i < parents_children.size() - 1; i++){
    last_child->AddChildNode(parents_children[i]); 
  }
 
  //cout << __LINE__ << "   size = " << to_string(size_) << endl; 
  //set the last_child's grandparent as its new parent
  MotifNode* last_childs_grandparent = last_child->GetParentNode()->GetParentNode(); 

  //if your parent is root
  if (last_childs_grandparent == nullptr){
    last_child->SetNullParent(); //then you're done
    setRoot(last_child); 
    delete parent_node;
    //size_--;  
    //cout << __LINE__ << "   size = " << to_string(size_) << endl; 
  } else {
    last_childs_grandparent->ReplaceChildNode(last_child, parent_node); 
    size_--;
    //cout << __LINE__ << "   size = " << to_string(size_) << endl; 
  }
  //cout << __LINE__ << "   size = " << to_string(size_) << endl; 
}


// Part 1
MusicalTree::~MusicalTree(){
  //it's a tree --> delete recursively
  //we need to delete the node's chldren too
  DestructHelper(root_); 
}

void MusicalTree::DestructHelper(MotifNode* node_){
  //delete the node's children recursively 
  vector<MotifNode*> child_units = node_->GetChildren();
  for (MotifNode* child : child_units){
    DestructHelper(child); 
  }
  delete node_;
}

/// I ADDED THIS, print function to help with testing
void MusicalTree::PrintTree(MotifNode* current){
  cout << "The node is : " << to_string(current->GetFitnessScore()) << endl;
  cout << "Number of children: " << to_string(current->GetChildren().size()) << endl; 
  cout << "The children are: " << endl;
  for (MotifNode* child : current->GetChildren()){
    cout << to_string(child->GetFitnessScore()) << endl;
  }
  for (MotifNode* child : current->GetChildren()){
    cout << "node: " << to_string(child->GetFitnessScore()) << endl;
    if (child->GetChildren().size() != 0){ //base case 
      PrintTree(child); 
    }
  }
}
  
  



/* ARCHIVE (old code)

///////// MY CODE


//base case from prune helper
//base case: if you have no children, just delete the node
  if ((children.size() == 0) && current_node->GetFitnessScore() < threshold){
    //before we delete, remove the node from whatever children vector it's in 
    vector<MotifNode*>& parents_children = current_node->GetParentNode()->GetChildren(); 
    cout << "these are the parents' children: " << endl; 
    for (MotifNode* kid : parents_children){
      cout << to_string(kid->GetFitnessScore()) << endl; 
    }
    //find its index 
    int index = 0; 
    for (MotifNode* kid : parents_children){
      if (kid == current_node){
        break; 
      } else {
        index++; 
      }
    }
    cout << "index : " << to_string(index) << endl; 
    parents_children.erase(parents_children.begin() + index);  //remove

    delete current_node; 
    size_--; 

    //just to make sure we have removed properly:
    cout << "Number of children in parent after PRUNE: " << to_string(parents_children.size()) << endl; 
    cout << "these are the children: " << endl; 
    for (MotifNode* kid : parents_children){
      cout << to_string(kid->GetFitnessScore()) << endl; 
    }






//with the wrong interpretation of last nodes 
void MusicalTree::Prune_Helper(double threshold, vector<MotifNode*> children, MotifNode* current_node, bool switch_){
  //we have no children
  if (children.size() == 0){  
    //just remove the node if we need to 
    if (current_node->GetFitnessScore() < threshold){
      delete current_node; 
      size_--;
    }
    return; 
  }
  //we do have children, and we need to iterate through them
  for (int i = 0; i < children.size(); i++){ 
    //first, we need to check if we rotated and need to restart 
    if (switch_ == true){
      i = 0; //restart iterating through the children vector
      switch_ = false; //so we don't get stuck in a loop
      children = current_node->GetChildren(); //get the most updated version of children 
    }
    else if (i == children.size() - 1){ //on the last child
      //we only rotate if we need to prune current_node_
      if (current_node->GetFitnessScore() < threshold){
        RotationHelper(children, current_node);
        switch_ = true; //we rotated 
        size_--; 
      }
    } else {  //we're on any other child
      Prune_Helper(threshold, children[i]->children_, children[i], switch_); //yes, so check its children
      delete children[i]; //delete the child once we're done with its children
      size_--;
    }
  }
} 


//AFTER ADDING THE SWITCH, STILL DOES NOT PRUNE FULLY
void MusicalTree::Prune_Helper(double threshold, vector<MotifNode*> children, MotifNode* current_node, bool switch_){
  //we have no children
  if (children.size() == 0){  
    //just remove the node if we need to 
    if (current_node->GetFitnessScore() < threshold){
      delete current_node; 
      size_--;
    }
    return; 
  }
  //we do have children, and we need to iterate through them
  for (int i = 0; i < children.size(); i++){ 
    //first, we need to check if we rotated and need to restart 
    if (switch_ == true){
      i = 0; //restart iterating through the children vector
      switch_ = false; //so we don't get stuck in a loop
      children = current_node->GetChildren(); //get the most updated version of children 
    }
    else if (i == children.size() - 1){ //on the last child
      //we only rotate if we need to prune current_node_
      if (current_node->GetFitnessScore() < threshold){
        RotationHelper(children, current_node);
        switch_ = true; //we rotated 
        size_--; 
      }
    } else {  //we're on any other child
      //does this child need to be pruned?
        if (children[i]->GetFitnessScore() < threshold){ 
          Prune_Helper(threshold, children[i]->children_, children[i], switch_); //yes, so check its children
          delete children[i]; //delete the child once we're done with its children
          size_--;
        }
    }
  }
} 

*/