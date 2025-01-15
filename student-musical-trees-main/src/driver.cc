#include "musical_tree.hpp"
#include <vector>
//#include "utilities.hpp"

using namespace std;

void Test_DeleteRootWithTwoNodeTree(){
  vector<Note> root_motif = {{50, 0.1}, {78, 0.7}, {84, 0.7}, {61, 0.4}, {67, 0.1}, {78, 0.1}};
  MotifNode* node_50 = new MotifNode(root_motif);
  node_50->SetFitnessScore(50.0);

  //node 100
  Note note_100 = Note(10, 10); 
  vector<Note> motif_100; 
  motif_100.push_back(note_100); 
  MotifNode* node_100 = new MotifNode(motif_100);
  node_100->SetFitnessScore(100.0); 
  node_50->AddChildNode(node_100); 

  MusicalTree test_tree(true); 

  test_tree.setRoot(node_50);
  //test_tree.setRoot(root); 
  test_tree.PrintTree(test_tree.GetRoot()); 
  test_tree.CheckInvariants();

  // //continuously prune
  cout << "starting prune" << endl; 
  test_tree.PruneNodes(test_tree.GetRoot(), 51); //threshold 11
  cout << "finished pruning, now printing: " << endl; 
  test_tree.PrintTree(test_tree.GetRoot());
  test_tree.CheckInvariants();
}

//TREE IS SIX NODES 
void Test_DeleteNode_DeleteRoot_DeleteNode(){
  //deletes a node, then the root, then another node 

  vector<Note> root_motif = {{50, 0.1}, {78, 0.7}, {84, 0.7}, {61, 0.4}, {67, 0.1}, {78, 0.1}};
  MotifNode* node_100 = new MotifNode(root_motif);
  node_100->SetFitnessScore(51.0); //ROOT IS 100

  //node 90 is root's child 
  Note note_90 = Note(10, 10); 
  vector<Note> motif_90; 
  motif_90.push_back(note_90); 
  MotifNode* node_90 = new MotifNode(motif_90);
  node_90->SetFitnessScore(90.0); 
  node_100->AddChildNode(node_90);

  //make 90's children, <80, 70>
  Note note_80 = Note(10, 10); 
  vector<Note> motif_80; 
  motif_80.push_back(note_80); 
  MotifNode* node_80 = new MotifNode(motif_80);
  node_80->SetFitnessScore(80.0); 
  node_90->AddChildNode(node_80);

  Note note_70 = Note(10, 10); 
  vector<Note> motif_70; 
  motif_70.push_back(note_70); 
  MotifNode* node_70 = new MotifNode(motif_70);
  node_70->SetFitnessScore(93.0); // now this is 93
  node_90->AddChildNode(node_70);

  //make 80's children, <60>
  Note note_60 = Note(10, 10); 
  vector<Note> motif_60; 
  motif_60.push_back(note_60); 
  MotifNode* node_60 = new MotifNode(motif_60);
  node_60->SetFitnessScore(95.0); 
  node_80->AddChildNode(node_60);

  //make 70's children, <50>
  Note note_50 = Note(10, 10); 
  vector<Note> motif_50; 
  motif_50.push_back(note_50); 
  MotifNode* node_50 = new MotifNode(motif_50);
  node_50->SetFitnessScore(50.0); 
  node_70->AddChildNode(node_50);

  // MAKE THE TREE
  MusicalTree test_tree(true); 
  test_tree.setRoot(node_100); 
  cout << "this is the tree: " << endl; 
  test_tree.PrintTree(test_tree.GetRoot()); 
  test_tree.CheckInvariants();

  
  //prune node 50
  cout << "prune node 50" << endl; 
  test_tree.PruneNodes(test_tree.GetRoot(), 51); //threshold 11
  cout << "finished pruning, now printing: " << endl; 
  //test_tree.PrintTree(test_tree.GetRoot());
  test_tree.CheckInvariants();

  //prune the root
  cout << "prune root" << endl; 
  test_tree.PruneNodes(test_tree.GetRoot(), 52); //threshold 11
  cout << "finished pruning, now printing: " << endl; 
  //test_tree.PrintTree(test_tree.GetRoot());
  test_tree.CheckInvariants();

  //prune another node 
  cout << "prune 80" << endl; 
  test_tree.PruneNodes(test_tree.GetRoot(), 81); //threshold 11
  cout << "finished pruning, now printing: " << endl; 
  test_tree.PrintTree(test_tree.GetRoot());
  test_tree.CheckInvariants();

  //prune another node 
  cout << "prune 90" << endl; 
  test_tree.PruneNodes(test_tree.GetRoot(), 91); //threshold 11
  cout << "finished pruning, now printing: " << endl; 
  test_tree.PrintTree(test_tree.GetRoot());
  test_tree.CheckInvariants();

  //prune another node 
  cout << "prune 93" << endl; 
  test_tree.PruneNodes(test_tree.GetRoot(), 94); //threshold 11
  cout << "finished pruning, now printing: " << endl; 
  test_tree.PrintTree(test_tree.GetRoot());
  test_tree.CheckInvariants();

}

//SINGLE GENERATION -- 1 Selection, 1 Reproduction
void Test_One_Generation(){

  vector<Note> root_motif = {{50, 0.1}, {78, 0.7}, {84, 0.7}, {61, 0.4}, {67, 0.1}, {78, 0.1}};
  MotifNode* root_node = new MotifNode(root_motif);
  root_node->SetFitnessScore(51.0); //ROOT IS 100

  //NODE 1 IS 90 
  Note note_1 = Note(10, 10); 
  vector<Note> motif_1; 
  motif_1.push_back(note_1); 
  MotifNode* node_1 = new MotifNode(motif_1);
  node_1->SetFitnessScore(90.0); 
  root_node->AddChildNode(node_1);

  //NODE 1'S CHILD, NODE 2 IS 80
  Note note_2 = Note(10, 10); 
  vector<Note> motif_2; 
  motif_2.push_back(note_2); 
  MotifNode* node_2 = new MotifNode(motif_2);
  node_2->SetFitnessScore(80.0); 
  node_1->AddChildNode(node_2);

  //NODE 1'S CHILD, NODE 3 IS 93
  Note note_3 = Note(10, 10); 
  vector<Note> motif_3; 
  motif_3.push_back(note_3); 
  MotifNode* node_3 = new MotifNode(motif_3);
  node_3->SetFitnessScore(93.0); // now this is 93
  node_1->AddChildNode(node_3);

  //NODE 2's CHILD, NODE 4 IS 95 
  Note note_4 = Note(10, 10); 
  vector<Note> motif_4; 
  motif_4.push_back(note_4); 
  MotifNode* node_4 = new MotifNode(motif_4);
  node_4->SetFitnessScore(95.0); 
  node_2->AddChildNode(node_4);

  //NODE 3'S CHILD, NODE 5 IS 50 
  Note note_5 = Note(10, 10); 
  vector<Note> motif_5; 
  motif_5.push_back(note_5); 
  MotifNode* node_5 = new MotifNode(motif_5);
  node_5->SetFitnessScore(50.0); 
  node_3->AddChildNode(node_5);

  // MAKE THE TREE
  MusicalTree test_tree(true); 
  test_tree.setRoot(root_node); 
  cout << "this is the tree: " << endl; 
  test_tree.PrintTree(test_tree.GetRoot()); 
  test_tree.CheckInvariants();

  //select one time
  vector<MotifNode*> selections = test_tree.SelectionPhase(); 
  cout << "these are the selected nodes:" << endl; 
  for (MotifNode* selectedNode : selections){
    cout << to_string(selectedNode->GetFitnessScore()) << endl; 
  }
  test_tree.CheckInvariants(); 

  //reproduce one time 
  test_tree.ReproductionPhase(selections);
  cout << "reproduced, here is the tree:" << endl; 
  test_tree.PrintTree(test_tree.GetRoot()); 
  test_tree.CheckInvariants(); 

  //continuously prune
  cout << "starting prune" << endl; 
  test_tree.PruneNodes(test_tree.GetRoot(), 51); //threshold 11
  cout << "finished pruning, now printing: " << endl; 
  test_tree.PrintTree(test_tree.GetRoot());
  test_tree.CheckInvariants();

  //continuously prune
  //newRoot->SetFitnessScore(85);
  test_tree.PruneNodes(test_tree.GetRoot(), 60); //threshold 11
  test_tree.PrintTree(test_tree.GetRoot());
  test_tree.CheckInvariants(); 

}


//ACTUAL GENERATION
void Test_Actual_Test_With_Genetic_Algo(){
  // Create MelodyGenerator object

  // vector<Note> root_motif = {{50, 0.1}, {78, 0.7}, {84, 0.7}, {61, 0.4}, {67, 0.1}, {78, 0.1}};
  // MotifNode* node_1 = new MotifNode(root_motif);

  MusicalTree mt(true);
  //mt.setRoot(node_1); 

  // cout << "this is the tree: " << endl; 
  // mt.PrintTree(mt.GetRoot()); 

  mt.GeneticAlgorithm(3); 
  mt.CheckInvariants(); 

}

void Test_Genetic_Algo_in_Main(){
  vector<Note> root_motif = {{50, 0.1}, {78, 0.7}, {84, 0.7}, {61, 0.4}, {67, 0.1}, {78, 0.1}};
  MotifNode* node_1 = new MotifNode(root_motif);

  srand(time(0)); 

  MusicalTree mt(true);
  mt.setRoot(node_1); 

  cout << "this is the tree: " << endl; 
  mt.PrintTree(mt.GetRoot());

  //pre-evolve 
  vector<MotifNode*> pre_evolve; 
  while (pre_evolve.size() < 4){
    for (int i = 0; i < 4; i++){
      vector<MotifNode*> pre_evolve = mt.SelectionPhase(); 
      mt.CheckInvariants(); 
      mt.ReproductionPhase(pre_evolve);
      mt.CheckInvariants(); 
    }
  }

  double threshold = 10; 
  //build generations
  for (int i = 0; i < 1; i++){
    for (int i = 0; i < 1; i++){
      vector<MotifNode*> selections = mt.SelectionPhase(); 
      mt.CheckInvariants(); 
      mt.ReproductionPhase(selections);
      mt.CheckInvariants(); 
    }
    while (mt.GetSize() > 200){
      mt.PruneNodes(mt.GetRoot(), threshold);
      mt.CheckInvariants(); 
      threshold++; 
    }
  }

  cout << "Final Prune " << mt.GetSize() << endl;

  //final prune
  while (mt.GetSize() > 2){
    mt.PruneNodes(mt.GetRoot(), threshold);
    mt.CheckInvariants(); 
    //threshold += 0.01; 
    threshold += 5; 
  }
}

void Test_Genetic_Algo_in_Main_with_Manual_Pre_Evolve(){
  vector<Note> root_motif = {{50, 0.1}, {78, 0.7}, {84, 0.7}, {61, 0.4}, {67, 0.1}, {78, 0.1}};
  MotifNode* root_node = new MotifNode(root_motif);
  root_node->SetFitnessScore(51.0); 

  // MAKE THE TREE
  MusicalTree mt(true); 

  //MANUAL PRE-EVOLVE: 
  vector<MotifNode*> pre_evolve; 
  pre_evolve.push_back(root_node); 

    //NODE 1 IS 90 
    Note note_1 = Note(10, 10); 
    vector<Note> motif_1; 
    motif_1.push_back(note_1); 
    MotifNode* node_1 = new MotifNode(motif_1);
    node_1->SetFitnessScore(90.0); 
    root_node->AddChildNode(node_1);
    pre_evolve.push_back(node_1);

    //NODE 1'S CHILD, NODE 2 IS 80
    Note note_2 = Note(10, 10); 
    vector<Note> motif_2; 
    motif_2.push_back(note_2); 
    MotifNode* node_2 = new MotifNode(motif_2);
    node_2->SetFitnessScore(80.0); 
    node_1->AddChildNode(node_2);
    pre_evolve.push_back(node_2);


    //NODE 1'S CHILD, NODE 3 IS 93
    Note note_3 = Note(10, 10); 
    vector<Note> motif_3; 
    motif_3.push_back(note_3); 
    MotifNode* node_3 = new MotifNode(motif_3);
    node_3->SetFitnessScore(93.0); // now this is 93
    node_1->AddChildNode(node_3);
    pre_evolve.push_back(node_3);


    //NODE 2's CHILD, NODE 4 IS 95 
    Note note_4 = Note(10, 10); 
    vector<Note> motif_4; 
    motif_4.push_back(note_4); 
    MotifNode* node_4 = new MotifNode(motif_4);
    node_4->SetFitnessScore(95.0); 
    node_2->AddChildNode(node_4);
    pre_evolve.push_back(node_4);


    //NODE 3'S CHILD, NODE 5 IS 50 
    Note note_5 = Note(10, 10); 
    vector<Note> motif_5; 
    motif_5.push_back(note_5); 
    MotifNode* node_5 = new MotifNode(motif_5);
    node_5->SetFitnessScore(50.0); 
    node_3->AddChildNode(node_5);
    pre_evolve.push_back(node_5);

  mt.setRoot(root_node);

  //now run the genetic algorithm 
  double threshold = 10; 
  //build generations
  for (int i = 0; i < 5; i++){ //5 GENERATIONS
    for (int i = 0; i < 3; i++){
      vector<MotifNode*> selections = mt.SelectionPhase(); 
      mt.CheckInvariants(); 
      mt.ReproductionPhase(selections);
      mt.CheckInvariants(); 
    }
    while (mt.GetSize() > 200){
      mt.PruneNodes(mt.GetRoot(), threshold);
      mt.CheckInvariants(); 
      threshold++; 
    }
  }

  cout << "Final Prune " << mt.GetSize() << endl;

  //final prune
  while (mt.GetSize() > 2){
    mt.PruneNodes(mt.GetRoot(), threshold);
    mt.CheckInvariants(); 
    threshold += 0.01; 
    //threshold += 5; 
  }

  cout << "this is the tree: " << endl; 
  mt.PrintTree(mt.GetRoot());

 
}


int main() {

  //Test_Genetic_Algo_in_Main_with_Manual_Pre_Evolve();  
  Test_Actual_Test_With_Genetic_Algo(); 


  // /* ALL OTHER NODES
  // //node 10
  // Note note_10 = Note(10, 10); 
  // vector<Note> motif_10; 
  // motif_10.push_back(note_10); 
  // MotifNode* node_10 = new MotifNode(motif_10);
  // node_10->SetFitnessScore(100.0); 
  // node_50->AddChildNode(node_10); 

  


  






  //test_tree.GeneticAlgorithm(1);

  
  // cout << "checking invariants" << endl; 
  // test_tree.CheckInvariants(); 
  // int size = 0; 
  // test_tree.CheckSize(root, size); 
  // cout << "the size is: " << to_string(size) << endl; 

  //cout << test_tree.CheckParent(root) << endl; //should return 1 



  // vector<MotifNode*> selectedNodes; 

  

  // selectedNodes.push_back(node_80); 


  // ////// MAKE THE TREE
  // MusicalTree test_tree(false, node_10, 3); 
  // test_tree.PrintTree(node_10);


  // vector<Note> all_motifs = test_tree.GenerateMelody(); 
  // cout << "these are all_motifs: " << endl; 
  // for (Note note : all_motifs){
  //   cout << note.pitch << "-" << note.duration << " " << endl; 
  // }



  

  //TEST SELECTION PHASE
    // vector<MotifNode*> selectedNodes = test_tree.SelectionPhase(); 
    // cout << "these are the selected nodes: " << endl; 
    // for (MotifNode* node : selectedNodes){
    //   cout << to_string(node->GetFitnessScore()) << endl; 
    // }

  /* GIVEN DRIVER CODE 
    // Create MelodyGenerator object
    MusicalTree mt(true);
    //GenerateMP3(mt.GenerateMelody(), "starting.mp3");

    // Evolve the tree structure for a fixed number of generations
    mt.GeneticAlgorithm(150);

    // Generate melody by traversing the evolved tree structure
    std::vector<Note> melody = mt.GenerateMelody();

    // Generage MP3 based on melody vector
    //GenerateMP3(melody, "output.mp3");
  */ 
}


/* TEST CASE 8 

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


// SPEC TREE
/* 
  
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
  */ 