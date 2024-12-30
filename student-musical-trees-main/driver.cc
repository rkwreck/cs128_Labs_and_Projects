#include "musical_tree.hpp"
#include <vector>
//#include "utilities.hpp"

using namespace std;


int main() {

  // MusicalTree test_tree(true);
  // vector<Note> root_motif = {{50, 0.1}, {78, 0.7}, {84, 0.7}, {61, 0.4}, {67, 0.1}, {78, 0.1}};
  // MotifNode* root = new MotifNode(root_motif);

  // MusicalTree test_tree(true, root); 
  // test_tree.PrintTree(root); 

  vector<MotifNode*> selectedNodes; 

  //make the root, 10
  Note note_10 = Note(10, 10); 
  Note note_11 = Note(10, 11); 
  Note note_12 = Note(10, 12); 
  vector<Note> root_motif; 
  root_motif.push_back(note_10); 
  root_motif.push_back(note_11); 
  root_motif.push_back(note_12);
  MotifNode* node_10 = new MotifNode(root_motif);
  node_10->SetFitnessScore(10.0); 

  selectedNodes.push_back(node_10); 

  //add 10's children, <90, 80> 
  Note note_90 = Note(10, 10);
  Note note_91 = Note(90, 91); 
  Note note_92 = Note(90, 92);     
  vector<Note> motif_90;  
  motif_90.push_back(note_90); 
  motif_90.push_back(note_91); 
  motif_90.push_back(note_92); 
  MotifNode* node_90 = new MotifNode(motif_90);
  node_90->SetFitnessScore(90.0); 

  node_10->AddChildNode(node_90); 

  selectedNodes.push_back(node_90); 


  Note note_80 = Note(10, 10);    
  vector<Note> motif_80;  
  motif_80.push_back(note_80); 
  MotifNode* node_80 = new MotifNode(motif_80);
  node_80->SetFitnessScore(80.0); 

  node_10->AddChildNode(node_80); 

  selectedNodes.push_back(node_80); 


  ////// MAKE THE TREE
  MusicalTree test_tree(false, node_10, 3); 
  test_tree.PrintTree(node_10);


  vector<Note> all_motifs = test_tree.GenerateMelody(); 
  cout << "these are all_motifs: " << endl; 
  for (Note note : all_motifs){
    cout << note.pitch << "-" << note.duration << " " << endl; 
  }



  //test_tree.SelectionPhase(); 
  //test_tree.PrintTree(node_10);

  // int size = 0;
  // test_tree.CheckSize(node_10,size); 
  // cout << "original size is: " << to_string(size) << endl; 

  // test_tree.CheckInvariants();


  //test_tree.ReproductionPhase(selectedNodes); 

  //test_tree.PruneNodes(node_10, 9); 
  //test_tree.PrintTree(node_10); 

  // size = 0;
  // test_tree.CheckSize(node_10,size); 
  // cout << "new size is: " << to_string(size) << endl; 

  // test_tree.CheckInvariants();
  

  //TEST SELECTION PHASE
  // vector<MotifNode*> selectedNodes = test_tree.SelectionPhase(); 
  // cout << "these are the selected nodes: " << endl; 
  // for (MotifNode* node : selectedNodes){
  //   cout << to_string(node->GetFitnessScore()) << endl; 
  // }

  // //TEST INVARIANT FUNCTION
  

  //cout << test_tree.CheckParent(node_10) << endl;  

  //double maxFitnessScore = -1; 
  //test_tree.FindMaxFitness(root, maxFitnessScore); 
  //cout << "The max fitness in this tree is : " << to_string(maxFitnessScore) << endl; 



  // test_tree.PruneNodes(node_10, 30);  //threshold 30 
  // cout << "completed pruning" << endl; 
  // test_tree.PrintTree(node_90); 
  



  // // Create MelodyGenerator object
  // MusicalTree mt(true);
  // //GenerateMP3(mt.GenerateMelody(), "starting.mp3");

  // // Evolve the tree structure for a fixed number of generations
  // mt.GeneticAlgorithm(150);

  // // Generate melody by traversing the evolved tree structure
  // std::vector<Note> melody = mt.GenerateMelody();

  // // Generage MP3 based on melody vector
  // //GenerateMP3(melody, "output.mp3");
}


/*

//TEST CASE 8

 //make the root, 10
  Note note_10 = Note(10, 10); 
  vector<Note> root_motif; 
  root_motif.push_back(note_10); 
  MotifNode* node_10 = new MotifNode(root_motif);
  node_10->SetFitnessScore(10.0); 

  //add 10's child, <90> 
  Note note_90 = Note(10, 10);    
  vector<Note> motif_90;  
  motif_90.push_back(note_90); 
  MotifNode* node_90 = new MotifNode(motif_90);
  node_90->SetFitnessScore(90.0); 

  node_10->AddChildNode(node_90); 

  //add 90's children, <80, 68> 
  Note note_80 = Note(10, 10);    
  vector<Note> motif_80;  
  motif_80.push_back(note_80); 
  MotifNode* node_80 = new MotifNode(motif_80);
  node_80->SetFitnessScore(80.0); 
  node_90->AddChildNode(node_80); 

  Note note_68 = Note(10, 10);    
  vector<Note> motif_68;  
  motif_68.push_back(note_68); 
  MotifNode* node_68 = new MotifNode(motif_68);
  node_68->SetFitnessScore(68.0); 
  node_90->AddChildNode(node_68);

  //add 80's children, <20, 20> 
  Note note_20 = Note(10, 10);    
  vector<Note> motif_20;  
  motif_20.push_back(note_20); 
  MotifNode* node_20 = new MotifNode(motif_20);
  node_20->SetFitnessScore(20.0); 
  node_80->AddChildNode(node_20); 

  Note note_20_2 = Note(10, 10);    
  vector<Note> motif_20_2;  
  motif_20_2.push_back(note_20_2); 
  MotifNode* node_20_2 = new MotifNode(motif_20_2);
  node_20_2->SetFitnessScore(20.0); 
  node_80->AddChildNode(node_20_2);
  

  ////// MAKE THE TREE
  MusicalTree test_tree(true, node_10, 6); 
  test_tree.PrintTree(node_10); 
  double maxFitnessScore = -1; 
  test_tree.FindMaxFitness(node_10, maxFitnessScore); 
  cout << "The max fitness in this tree is : " << to_string(maxFitnessScore) << endl; 


*/








//TEST CASE 6
/*

//make the root, 10
  Note note_10 = Note(10, 10); 
  vector<Note> root_motif; 
  root_motif.push_back(note_10); 
  MotifNode* node_10 = new MotifNode(root_motif);
  node_10->SetFitnessScore(10.0); 

  //add 10's child, <90> 
  Note note_90 = Note(10, 10);    
  vector<Note> motif_90;  
  motif_90.push_back(note_90); 
  MotifNode* node_90 = new MotifNode(motif_90);
  node_90->SetFitnessScore(90.0); 

  node_10->AddChildNode(node_90); 

  //add 90's children, <80, 68> 
  Note note_80 = Note(10, 10);    
  vector<Note> motif_80;  
  motif_80.push_back(note_80); 
  MotifNode* node_80 = new MotifNode(motif_80);
  node_80->SetFitnessScore(80.0); 
  node_90->AddChildNode(node_80); 

  Note note_68 = Note(10, 10);    
  vector<Note> motif_68;  
  motif_68.push_back(note_68); 
  MotifNode* node_68 = new MotifNode(motif_68);
  node_68->SetFitnessScore(68.0); 
  node_90->AddChildNode(node_68);

  //add 80's children, <20, 20> 
  Note note_20 = Note(10, 10);    
  vector<Note> motif_20;  
  motif_20.push_back(note_20); 
  MotifNode* node_20 = new MotifNode(motif_20);
  node_20->SetFitnessScore(20.0); 
  node_80->AddChildNode(node_20); 

  Note note_20_2 = Note(10, 10);    
  vector<Note> motif_20_2;  
  motif_20_2.push_back(note_20_2); 
  MotifNode* node_20_2 = new MotifNode(motif_20_2);
  node_20_2->SetFitnessScore(20.0); 
  node_80->AddChildNode(node_20_2);
  

  ////// MAKE THE TREE
  MusicalTree test_tree(true, node_10, 6); 
  test_tree.PrintTree(node_10); 
  test_tree.PruneNodes(node_10, 100); 
  cout << "completed pruning" << endl; 
  test_tree.PrintTree(node_10); 

*/


//TEST CASE 5 
//make the root, 90
/*
  Note note_90 = Note(10, 10); 
  vector<Note> root_motif; 
  root_motif.push_back(note_90); 

  MotifNode* node_90 = new MotifNode(root_motif);
  node_90->SetFitnessScore(90.0); 

  //add 90's child, <10> 
  Note note_10 = Note(10, 10);    //make child 10
  vector<Note> motif_10;  
  motif_10.push_back(note_10); 
  MotifNode* node_10 = new MotifNode(motif_10);
  node_10->SetFitnessScore(10.0); 

  node_90->AddChildNode(node_10); 


  //add 10's children, <80, 68> 
  Note note_80 = Note(10, 10);    //make child 10
  vector<Note> motif_80;  
  motif_80.push_back(note_80); 
  MotifNode* node_80 = new MotifNode(motif_80);
  node_80->SetFitnessScore(80.0); 

  Note note_68 = Note(10, 10);    //make child 10
  vector<Note> motif_68;  
  motif_68.push_back(note_68); 
  MotifNode* node_68 = new MotifNode(motif_68);
  node_68->SetFitnessScore(68.0); 

  node_10->AddChildNode(node_80); 
  node_10->AddChildNode(node_68);

  //add 80's children, <20, 20> 
  Note note_20 = Note(10, 10);    //make child 10
  vector<Note> motif_20;  
  motif_20.push_back(note_20); 
  MotifNode* node_20 = new MotifNode(motif_20);
  node_20->SetFitnessScore(20.0);  

  Note note_20_2 = Note(10, 10);    //make child 10
  vector<Note> motif_20_2;  
  motif_20_2.push_back(note_20_2); 
  MotifNode* node_20_2 = new MotifNode(motif_20_2);
  node_20_2->SetFitnessScore(20.0); 

  node_80->AddChildNode(node_20); 
  node_80->AddChildNode(node_20_2);

  //add 68's children, <35, 36> 
  Note note_35 = Note(10, 10);    //make child 10
  vector<Note> motif_35;  
  motif_35.push_back(note_35); 
  MotifNode* node_35 = new MotifNode(motif_35);
  node_35->SetFitnessScore(35.0); 

  Note note_36 = Note(10, 10);    //make child 10
  vector<Note> motif_36;  
  motif_36.push_back(note_36); 
  MotifNode* node_36 = new MotifNode(motif_36);
  node_36->SetFitnessScore(36.0); 

  node_68->AddChildNode(node_35); 
  node_68->AddChildNode(node_36);

  

  ////// MAKE THE TREE
  MusicalTree test_tree(true, node_90, 8); 
  test_tree.PrintTree(node_90); 
  test_tree.PruneNodes(node_90, 15); 
  cout << "completed pruning" << endl; 
  test_tree.PrintTree(node_90); 
*/ 


////////////// SPEC TREE
  
  // //make the root, 89
  // Note note_89 = Note(10, 10); 
  // vector<Note> root_motif; 
  // root_motif.push_back(note_89); 

  // MotifNode* node_89 = new MotifNode(root_motif);
  // node_89->SetFitnessScore(89.0); 


  // //add 89's children, <12, 99>
  // Note note_12 = Note(10, 10);    //make child 12
  // vector<Note> motif_12;  ///// FIX THIS
  // motif_12.push_back(note_12); 
  // MotifNode* node_12 = new MotifNode(motif_12);
  // node_12->SetFitnessScore(12.0); 

  // Note note_99 = Note(10, 10);    //make child 99
  // vector<Note> motif_99; 
  // motif_99.push_back(note_99); 
  // MotifNode* node_99 = new MotifNode(motif_99);
  // node_99->SetFitnessScore(99.0); 

  // node_89->AddChildNode(node_12); 
  // node_89->AddChildNode(node_99); 

  // // //add 12's children
  // Note note_78 = Note(10, 10);    //make child 78
  // vector<Note> motif_78; 
  // motif_78.push_back(note_78); 
  // MotifNode* node_78 = new MotifNode(motif_78);
  // node_78->SetFitnessScore(78.0); 

  // Note note_77 = Note(10, 10);    //make child 77
  // vector<Note> motif_77; 
  // motif_77.push_back(note_77); 
  // MotifNode* node_77 = new MotifNode(motif_77);
  // node_77->SetFitnessScore(77.0); 

  // node_12->AddChildNode(node_78); 
  // node_12->AddChildNode(node_77);


  // //add 78's children
  // Note note_64 = Note(10, 10);    //make child 64
  // vector<Note> motif_64; 
  // motif_64.push_back(note_64); 
  // MotifNode* node_64 = new MotifNode(motif_64);
  // node_64->SetFitnessScore(64.0); 

  // node_78->AddChildNode(node_64); 

  // //add 77's children
  // Note note_22 = Note(10, 10);    //make child 22
  // vector<Note> motif_22; 
  // motif_22.push_back(note_22); 
  // MotifNode* node_22 = new MotifNode(motif_22);
  // node_22->SetFitnessScore(22.0);  

  // Note note_81 = Note(10, 10);    //make child 81
  // vector<Note> motif_81; 
  // motif_81.push_back(note_81); 
  // MotifNode* node_81 = new MotifNode(motif_81);
  // node_81->SetFitnessScore(81.0); 

  // node_77->AddChildNode(node_22); 
  // node_77->AddChildNode(node_81); 


  // //add 99's children
  // Note note_87 = Note(10, 10);    //make child 87
  // vector<Note> motif_87; 
  // motif_87.push_back(note_87); 
  // MotifNode* node_87 = new MotifNode(motif_87);
  // node_87->SetFitnessScore(87.0);  

  // node_99->AddChildNode(node_87); 