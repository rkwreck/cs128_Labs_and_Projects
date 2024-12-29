#include "musical_tree.hpp"

#include <cstdlib> 
#include <ctime>


// using namespace std;


//------------------REQUIRED------------------------

// REQUIRES:
// MODIFIES: This MusicalTree
// EFFECTS : Initializes the MusicalTree with a root node
// Part 1
MusicalTree::MusicalTree(bool verbose){  
  root_ = nullptr;
  verbose_ = verbose; 
  size_ = 0; 
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

// // REQUIRES: This MusicalTree is valid
// // MODIFIES: This MusicalTree
// // EFFECTS : Runs the entire genetic algorithm by evolving and pruning the
// //           tree per the number of generations passed in
// void MusicalTree::GeneticAlgorithm(int numGenerations){

// }

// void MusicalTree::SelectionPhase(){

  
// }

// void MusicalTree::ReproductionPhase(MotifNode* parentNode){
//   int  = parentNode

//   //calculate & check the mutated pitch
//   pitch += ( -2 + (rand() % 2) )
//   if (pitch < 0){
//     pitch = 0; 
//   } else if (pitch > 127){
//     pitch = 127; 
//   }
  
//   //calculate & check the mutated duration
//   duration += ( -2 + (rand() % 2) )
//   if (duration < 0.1){
//     duration = 0.1
//   } else if (duration > 0.7){
//     duration = 0.7;  
//   }
  
//   MotifNode* newChild = new MotifNode*; 
  

//   //seed the rng 
//   srand(time(0)); 

  
// }


// REQUIRES: This MusicalTree is valid
// MODIFIES:
// EFFECTS : Returns a single vector of all the motifs in the tree
std::vector<Note> MusicalTree::GenerateMelody(){
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
  Prune_Helper(threshold, tree_children, tree); 
}

void MusicalTree::Prune_Helper(double threshold, vector<MotifNode*> children, MotifNode* current_node){
  //if it's the last node, don't do anything 
  if (current_node->GetParentNode() == nullptr && children.size() == 0){
    return; 
  }

  //base case: if you have no children, just delete the node
  if ((children.size() == 0) && current_node->GetFitnessScore() < threshold){
    //before we delete, remove the node from whatever children vector it's in 
    current_node->GetParentNode()->RemoveChildNode(current_node); 
    size_--; 
  } else {
    for (MotifNode* child : children){
      Prune_Helper(threshold, child->GetChildren(), child); //check the children
    }
    if (current_node->GetFitnessScore() < threshold){
      RotationHelper(current_node->GetChildren(), current_node); //rotate & delete current_node
      size_--; 
    }
  }
}


void MusicalTree::RotationHelper(vector<MotifNode*> parents_children, MotifNode* parent_node){
  //we only rotate if the node has children, confirm this
  if (parents_children.size() == 0){
    return; 
  }
  MotifNode* last_child = parents_children[parents_children.size() - 1];

  //adjust last_child's children, maintain order
  vector<MotifNode*> new_children; 
  //adopt siblings
  for (int i = 0; i < parents_children.size() - 1; i++){ 
    new_children.push_back(parents_children[i]); 
  }
  for (MotifNode* kid : last_child->GetChildren()){ //then add the original children
    new_children.push_back(kid); 
  }
  last_child->children_.clear(); //empty children vector for last_child
  //so finally we can update last_child's children
  for (MotifNode* kid_ : new_children){
    last_child->AddChildNode(kid_);
  }

  //set the last_child's grandparent as its new parent
  last_child->parent_ = parent_node->GetParentNode(); 
  if (last_child->parent_ != nullptr){
    //add last_child to its (former) grandparent's children, maintain order 
    last_child->parent_->ReplaceChildNode(last_child, parent_node); 
  }
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
  
  

//----------------------------------------------------
// Add more functions here

// bool CheckInvariants(){
//   bool check = true; 
//   if (size_ < 1){
//     check = false; 
//   } 
//   if (root_->parent_ != nullptr){
//     check = false; 
//   }
//   //how in the world do you check for the other three invariants

//   return check; 
// }



/* 

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