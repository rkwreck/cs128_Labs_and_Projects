#ifndef BBT_HPP
#define BBT_HPP

// Node used to represent a Binary Tree
template <typename T>
struct Node {
  T data;
  Node* left;
  Node* right;
  Node(T input): data(input), left(nullptr), right(nullptr) {}
};

//Assume T allows the < and > operations. 
template <typename T>
class BalancedBinaryTree {
public:
  // REQUIRES: 
  // MODIFIES: BalancedBinaryTree
  // EFFECTS: Initializes a BalancedBinaryTree
  BalancedBinaryTree();

  // REQUIRES: 
  // MODIFIES:
  // EFFECTS: Returns the height of the tree 
  int GetHeight() const;

  // REQUIRES: 
  // MODIFIES:
  // EFFECTS: Returns the size of the tree 
  int GetSize() const;

  // REQUIRES: element is not currently in the tree
  // MODIFIES: BalancedBinaryTree
  // EFFECTS: adds element to the tree in a way that minimizes 
  //          a growth in height as much as possible. Start by 
  //          adding new elements on the left and move right. 
  void BalanceInsert(T element);

  // REQUIRES: 
  // MODIFIES:
  // EFFECTS: Returns if the tree is a BST 
  bool IsBST() const; 

  // REQUIRES: 
  // MODIFIES:
  // EFFECTS: Returns how many nodes it had to check to find or not find
  //.         the element in the tree (NOT including the one with the element)
  int Search(T element) const;

  // REQUIRES: 
  // MODIFIES: BalancedBinaryTree
  // EFFECTS: Deletes all nodes on the tree
  ~BalancedBinaryTree();
  
   //--------OPTIONAL but a fun challenge -------------
  // REQUIRES: 
  // MODIFIES: BalancedBinaryTree
  // EFFECTS: Re-organizes the tree so that it is a BST
  //          where the height is as small as possible given
  //          the size. Feel free to use other data structures 
  //          to help with this. 
  void BSTify();
  //--------------------------------

private:
  // Helper functions

  // REQUIRES: 
  // MODIFIES:
  // EFFECTS: A recursive, helper function for finding the
  //          height of the tree. 
  int HeightHelper(Node<T>* tree) const;

  //TODO Add more helper functions and member variables as 
  //you wish. 

  bool isBSTHelper(Node<T>* node_, int min, int max) const; 

  int GetSizeHelper(Node* tree) const; 

  int SearchHelper(T element, Node<T>* node); 

  // Member variable
  Node<T>* root_;
};

#endif

// EFFECTS: Initializes a BalancedBinaryTree
BalancedBinaryTree::BalancedBinaryTree(){
  root_ == nullptr; 
}

// REQUIRES: 
// MODIFIES:
// EFFECTS: Returns the height of the tree 
int GetHeight() const{

}

int HeightHelper(Node<T>* tree) const{
  int counter = 0; 
  if (tree == nullptr){
    return 0; 
  }
  if (tree->left == nullptr && tree->right != nullptr){

  }

  if (tree -> )
}


// REQUIRES: 
// MODIFIES:
// EFFECTS: Returns the size of the tree 
int GetSize() const{
  return GetSizeHelper(); 
}

int GetSizeHelper(Node* tree) const{
  if(tree == nullptr) return 0; 
  return GetSizeHelper(tree->left) + GetSize(tree->right) + 1; 
}



// EFFECTS: Returns if the tree is a BST 
bool BalancedBinaryTree::IsBST() const{
  if (isBSTHelper(root_, -10000000, +10000000)){
    return true; 
  }
  return false; 
}

// HELPER FUNCTION for IsBST()
bool BalancedBinaryTree::isBSTHelper(Node<T>* node_, int min, int max) const{
  if (node_ == nullptr){
    return false; 
  }
  if (node_->left->data < min){
    min = node_->data; //update
    return isBSTHelper(node_->left, min, max);
  } else { 
    return false; 
  }
  if (node_->right->data > max){
    max = node_->data; //udpate
    return isBSTHelper(node_->right, min, max);
  } else {
    return false; 
  }
  return true; 
}

// REQUIRES: element is not currently in the tree
// MODIFIES: BalancedBinaryTree
// EFFECTS: adds element to the tree in a way that minimizes 
//          a growth in height as much as possible. Start by 
//          adding new elements on the left and move right. 
void BalanceInsert(T element);

// REQUIRES: 
// MODIFIES:
// EFFECTS: Returns how many nodes it had to check to find or not find
//          the element in the tree (NOT including the one with the element)
int BalancedBinaryTree::Search(T element) const{
  // int counter = 0
  // Node<T>* current = root_; 
  return SearchHelper(root_);

}

int BalancedBinaryTree::SearchHelper(T element, Node<T>* node){
  if(node == nullptr){ //base case
    return 0; 
  }
  if (node->data != element){
    return 1 + SearchHelper(element, current->left) + SearchHelper(element, current->right);
  }
  return 1; 
} 

// REQUIRES: 
// MODIFIES: BalancedBinaryTree
// EFFECTS: Deletes all nodes on the tree
~BalancedBinaryTree();

 






// // my helper functions to check if it's a binary tree
// bool BalancedBinaryTree::SearchBST_left(Node<T>* node_) const{
//   if (node_ == nullptr) return false; 
//   if (node_->left < node_){
//     return (SearchBST(node_->left)); 
//   } else {
//     return false; 
//   }
// } 

// bool BalancedBinaryTree::SearchBST_right(Node<T>* node_) const{
//   if (node_ == nullptr) return false; 
//   if (node_->right < node_){
//     return (SearchBST(node_->left)); 
//   } else {
//     return false; 
//   }
// }
