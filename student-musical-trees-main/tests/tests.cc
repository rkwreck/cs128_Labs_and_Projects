// clang-format off
/////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////
//  Written By : Jule Schatz                    Environment : ubuntu:bionic               //
//  Date ......: 2023/12/29                      Compiler ...: clang-10                    //
/////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////
// clang-format on
/////////////////////////////////////////////////////////////////////////////////////////////
//                             Framework Set-up //
/////////////////////////////////////////////////////////////////////////////////////////////
#ifndef CATCH_CONFIG_MAIN
#  define CATCH_CONFIG_MAIN
#endif
#include <catch.hpp>
#include <vector>

/////////////////////////////////////////////////////////////////////////////////////////////
//                                 Includes //
/////////////////////////////////////////////////////////////////////////////////////////////
#include <stdexcept>

#include "motif_node.hpp"
#include "musical_tree.hpp"

/////////////////////////////////////////////////////////////////////////////////////////////
//                             Helpers/Constants //
/////////////////////////////////////////////////////////////////////////////////////////////
bool ValidateTree(MotifNode* node, MotifNode* root, int& size) {
  size++;
  if (node == nullptr) {
    return false;
  }
  vector<MotifNode*> children = node->GetChildren();

  for (int i = 0; i < children.size(); i++) {
    if (!ValidateTree(children[i], root, size)) return false;
  }

  if (node == root) {
    return node->GetParentNode() == nullptr;
  }
  // if it's not the root it has a parent
  if (node->GetParentNode() == nullptr) return false;

  // make sure the node is in its parents children vector
  vector<MotifNode*> children_test = node->GetParentNode()->GetChildren();
  bool found = false;
  for (int i = 0; i < children_test.size(); i++) {
    if (children_test[i] == node) found = true;
  }
  return found;
}

bool AreTreesEqual(const MotifNode* node1, const MotifNode* node2) {
  // Check if both nodes are null (end of branch)
  if (node1 == nullptr && node2 == nullptr) {
    return true;
  }

  // If only one of them is null, the trees are different
  if (node1 == nullptr || node2 == nullptr) {
    return false;
  }

  // Checks motif
  if (node1->GetMotif()[0].pitch != node2->GetMotif()[0].pitch) {
    return false;
  }

  // Check if the number of children is the same
  const auto& children1 = node1->GetChildren();
  const auto& children2 = node2->GetChildren();
  if (children1.size() != children2.size()) {
    return false;
  }

  // Recursively check each child node for equality
  for (size_t i = 0; i < children1.size(); ++i) {
    if (!AreTreesEqual(children1[i], children2[i])) {
      return false;
    }
  }
  return true;
}

bool VectorCompare(const vector<Note>& vec1, const vector<Note>& vec2) {
  // Check if sizes are different
  if (vec1.size() != vec2.size()) {
    return false;
  }

  // Compare each Note element in the vectors
  for (size_t i = 0; i < vec1.size(); ++i) {
    if (vec1[i].pitch != vec2[i].pitch ||
        vec1[i].duration != vec2[i].duration) {
      return false;
    }
  }

  // If all elements are the same, the vectors are equal
  return true;
}

// /////////////////////////////////////////////////////////////////////////////////////////////
// //                                Test Cases //
// /////////////////////////////////////////////////////////////////////////////////////////////
TEST_CASE("MotifNode Constructor", "[motifNode-con]") {
  vector<Note> nts1 = {Note(100, 1), Note(200, 2)};
  MotifNode con(nts1);

  // motif matches
  REQUIRE(VectorCompare(con.GetMotif(), nts1));
  REQUIRE(con.GetChildren().empty());
  REQUIRE(con.GetParentNode() == nullptr);
}

// Add more test cases for MotifNode here

//--------- Big three tests ---------------
TEST_CASE("MusicalTree assignment", "[musicalTree-assignment]") {
  MusicalTree tr(false);
  MotifNode* rt = tr.GetRoot();

  vector<Note> mot1 = {{1, 2}, {2, 3}, {2, 3}, {2, 3}, {2, 3}, {2, 3}};
  MotifNode* md1 = new MotifNode(mot1);
  rt->AddChildNode(md1);

  vector<Note> mot2 = {{2, 2}, {2, 3}, {2, 3}, {2, 3}, {2, 3}, {2, 3}};
  MotifNode* md2 = new MotifNode(mot2);
  rt->AddChildNode(md2);

  vector<Note> mot3 = {{3, 2}, {2, 3}, {2, 3}, {2, 3}, {2, 3}, {2, 3}};
  MotifNode* md3 = new MotifNode(mot3);
  rt->AddChildNode(md3);

  vector<Note> mot4 = {{4, 2}, {2, 3}, {2, 3}, {2, 3}, {2, 3}, {2, 3}};
  MotifNode* md4 = new MotifNode(mot4);
  md1->AddChildNode(md4);

  vector<Note> mot5 = {{5, 2}, {2, 3}, {2, 3}, {2, 3}, {2, 3}, {2, 3}};
  MotifNode* md5 = new MotifNode(mot5);
  md1->AddChildNode(md5);

  vector<Note> mot6 = {{6, 2}, {2, 3}, {2, 3}, {2, 3}, {2, 3}, {2, 3}};
  MotifNode* md6 = new MotifNode(mot6);
  md4->AddChildNode(md6);

  vector<Note> mot7 = {{57, 2}, {2, 3}, {2, 3}, {2, 3}, {2, 3}, {2, 3}};
  MotifNode* md7 = new MotifNode(mot7);
  md4->AddChildNode(md7);

  vector<Note> mot8 = {{8, 2}, {2, 3}, {2, 3}, {2, 3}, {2, 3}, {2, 3}};
  MotifNode* md8 = new MotifNode(mot8);
  md3->AddChildNode(md8);

  MusicalTree tr2(true);

  tr2 = tr;

  int size = 0;
  REQUIRE(ValidateTree(tr2.GetRoot(), tr2.GetRoot(), size));
  REQUIRE(size == 9);
  REQUIRE(AreTreesEqual(tr2.GetRoot(), tr.GetRoot()));
}

TEST_CASE("MusicalTree copy", "[musicalTree-copy]") {
  MusicalTree tr(false);
  MotifNode* rt = tr.GetRoot();

  vector<Note> mot1 = {{1, 2}, {2, 3}, {2, 3}, {2, 3}, {2, 3}, {2, 3}};
  MotifNode* md1 = new MotifNode(mot1);
  rt->AddChildNode(md1);

  vector<Note> mot2 = {{2, 2}, {2, 3}, {2, 3}, {2, 3}, {2, 3}, {2, 3}};
  MotifNode* md2 = new MotifNode(mot2);
  rt->AddChildNode(md2);

  vector<Note> mot3 = {{3, 2}, {2, 3}, {2, 3}, {2, 3}, {2, 3}, {2, 3}};
  MotifNode* md3 = new MotifNode(mot3);
  rt->AddChildNode(md3);

  vector<Note> mot4 = {{4, 2}, {2, 3}, {2, 3}, {2, 3}, {2, 3}, {2, 3}};
  MotifNode* md4 = new MotifNode(mot4);
  md1->AddChildNode(md4);

  vector<Note> mot5 = {{5, 2}, {2, 3}, {2, 3}, {2, 3}, {2, 3}, {2, 3}};
  MotifNode* md5 = new MotifNode(mot5);
  md1->AddChildNode(md5);

  vector<Note> mot6 = {{6, 2}, {2, 3}, {2, 3}, {2, 3}, {2, 3}, {2, 3}};
  MotifNode* md6 = new MotifNode(mot6);
  md4->AddChildNode(md6);

  vector<Note> mot7 = {{57, 2}, {2, 3}, {2, 3}, {2, 3}, {2, 3}, {2, 3}};
  MotifNode* md7 = new MotifNode(mot7);
  md4->AddChildNode(md7);

  vector<Note> mot8 = {{8, 2}, {2, 3}, {2, 3}, {2, 3}, {2, 3}, {2, 3}};
  MotifNode* md8 = new MotifNode(mot8);
  md3->AddChildNode(md8);

  MusicalTree tr2 = tr;

  int size = 0;
  REQUIRE(ValidateTree(tr2.GetRoot(), tr2.GetRoot(), size));
  REQUIRE(size == 9);
  REQUIRE(AreTreesEqual(tr2.GetRoot(), tr.GetRoot()));
}

//--------- MusicalTree Prune tests ---------------
TEST_CASE("MusicalTree Prune 1", "[musicalTree-prune-1]") {
  MusicalTree tr(false);
  vector<Note> mot = {{1, 2}, {2, 3}, {2, 3}, {2, 3}, {2, 3}, {2, 3}};
  MotifNode md1(mot);
  md1.SetFitnessScore(50);
  tr.PruneNodes(&md1, 70);
  int size = 0;
  REQUIRE(ValidateTree(&md1, &md1, size));
  REQUIRE(size == 1);
}

// prune a node with no children
TEST_CASE("MusicalTree Prune 2", "[musicalTree-prune-2]") {
  MusicalTree tr(false);
  MotifNode* root = tr.GetRoot();

  vector<Note> mot = {{1, 2}, {2, 3}, {2, 3}, {2, 3}, {2, 3}, {2, 3}};
  root->SetFitnessScore(50);

  MotifNode* md2 = new MotifNode(mot);
  md2->SetFitnessScore(40);
  root->AddChildNode(md2);

  tr.PruneNodes(root, 45);
  int size = 0;
  REQUIRE(ValidateTree(root, root, size));
  REQUIRE(size == 1);
}

// prune multiple nodes, each don't have children
TEST_CASE("MusicalTree Prune 3", "[musicalTree-prune-3]") {
  MusicalTree tr(false);
  MotifNode* root = tr.GetRoot();

  vector<Note> mot = {{1, 2}, {2, 3}, {2, 3}, {2, 3}, {2, 3}, {2, 3}};
  root->SetFitnessScore(90);

  MotifNode* md2 = new MotifNode(mot);
  md2->SetFitnessScore(90);
  root->AddChildNode(md2);

  MotifNode* md3 = new MotifNode(mot);
  md3->SetFitnessScore(80);
  md2->AddChildNode(md3);

  MotifNode* md5 = new MotifNode(mot);
  md5->SetFitnessScore(20);
  md3->AddChildNode(md5);

  MotifNode* md6 = new MotifNode(mot);
  md6->SetFitnessScore(20);
  md3->AddChildNode(md6);

  MotifNode* md4 = new MotifNode(mot);
  md4->SetFitnessScore(40);
  md2->AddChildNode(md4);

  tr.PruneNodes(root, 45);
  int size = 0;
  REQUIRE(ValidateTree(root, root, size));
  REQUIRE(size == 3);
}

// prune but has children (that aren't pruned)
TEST_CASE("MusicalTree Prune 4", "[musicalTree-prune-4]") {
  MusicalTree tr(false);
  MotifNode* root = tr.GetRoot();

  vector<Note> mot = {{1, 2}, {2, 3}, {2, 3}, {2, 3}, {2, 3}, {2, 3}};
  root->SetFitnessScore(90);

  MotifNode* md2 = new MotifNode(mot);
  md2->SetFitnessScore(10);
  root->AddChildNode(md2);

  MotifNode* md3 = new MotifNode(mot);
  md3->SetFitnessScore(80);
  md2->AddChildNode(md3);

  MotifNode* md5 = new MotifNode(mot);
  md5->SetFitnessScore(20);
  md3->AddChildNode(md5);

  MotifNode* md6 = new MotifNode(mot);
  md6->SetFitnessScore(20);
  md3->AddChildNode(md6);

  MotifNode* md4 = new MotifNode(mot);
  md4->SetFitnessScore(68);
  md2->AddChildNode(md4);

  tr.PruneNodes(root, 15);
  int size = 0;
  REQUIRE(ValidateTree(root, root, size));

  vector<MotifNode*> md1_c = root->GetChildren();
  REQUIRE(size == 5);

  REQUIRE(md1_c.size() == 1);
  REQUIRE(md1_c[0]->GetChildren().size() == 1);
  REQUIRE(md1_c[0]->GetFitnessScore() == 68);

  // 68's children
  vector<MotifNode*> md2_c = md1_c[0]->GetChildren();

  REQUIRE(md2_c[0]->GetFitnessScore() == 80);
  REQUIRE(md2_c[0]->GetChildren().size() == 2);
  REQUIRE(md2_c[0]->GetChildren()[0]->GetFitnessScore() == 20);
  REQUIRE(md2_c[0]->GetChildren()[1]->GetFitnessScore() == 20);
}

// prune but has children (that aren't pruned)
TEST_CASE("MusicalTree Prune 5", "[musicalTree-prune-5]") {
  MusicalTree tr(false);
  MotifNode* root = tr.GetRoot();

  vector<Note> mot = {{1, 2}, {2, 3}, {2, 3}, {2, 3}, {2, 3}, {2, 3}};
  root->SetFitnessScore(90);

  MotifNode* md2 = new MotifNode(mot);
  md2->SetFitnessScore(10);
  root->AddChildNode(md2);

  MotifNode* md3 = new MotifNode(mot);
  md3->SetFitnessScore(80);
  md2->AddChildNode(md3);

  MotifNode* md5 = new MotifNode(mot);
  md5->SetFitnessScore(20);
  md3->AddChildNode(md5);

  MotifNode* md6 = new MotifNode(mot);
  md6->SetFitnessScore(20);
  md3->AddChildNode(md6);

  MotifNode* md4 = new MotifNode(mot);
  md4->SetFitnessScore(68);
  md2->AddChildNode(md4);

  MotifNode* md7 = new MotifNode(mot);
  md7->SetFitnessScore(35);
  md4->AddChildNode(md7);

  MotifNode* md8 = new MotifNode(mot);
  md8->SetFitnessScore(36);
  md4->AddChildNode(md8);

  tr.PruneNodes(root, 15);
  int size = 0;
  REQUIRE(ValidateTree(root, root, size));
  REQUIRE(size == 7);

  // 90's children
  vector<MotifNode*> md1_c = root->GetChildren();

  REQUIRE(md1_c.size() == 1);
  REQUIRE(md1_c[0]->GetFitnessScore() == 68);

  // 68's children
  vector<MotifNode*> md2_c = md1_c[0]->GetChildren();

  REQUIRE(md2_c.size() == 3);
  REQUIRE((md2_c[0]->GetFitnessScore() == 80 ||
           md2_c[1]->GetFitnessScore() == 80 ||
           md2_c[2]->GetFitnessScore() == 80));
  REQUIRE((md2_c[0]->GetFitnessScore() == 35 ||
           md2_c[1]->GetFitnessScore() == 35 ||
           md2_c[2]->GetFitnessScore() == 35));
}

// prune everything but root
TEST_CASE("MusicalTree Prune 6", "[musicalTree-prune-6]") {
  MusicalTree tr(false);
  MotifNode* root = tr.GetRoot();

  vector<Note> mot = {{1, 2}, {2, 3}, {2, 3}, {2, 3}, {2, 3}, {2, 3}};
  root->SetFitnessScore(10);

  MotifNode* md2 = new MotifNode(mot);
  md2->SetFitnessScore(90);
  root->AddChildNode(md2);

  MotifNode* md3 = new MotifNode(mot);
  md3->SetFitnessScore(80);
  md2->AddChildNode(md3);

  MotifNode* md5 = new MotifNode(mot);
  md5->SetFitnessScore(20);
  md3->AddChildNode(md5);

  MotifNode* md6 = new MotifNode(mot);
  md6->SetFitnessScore(20);
  md3->AddChildNode(md6);

  MotifNode* md4 = new MotifNode(mot);
  md4->SetFitnessScore(68);
  md2->AddChildNode(md4);

  tr.PruneNodes(root, 100);
  int size = 0;
  REQUIRE(ValidateTree(root, root, size));
  REQUIRE(size == 1);
}

// prune but has children (that aren't pruned)
TEST_CASE("MusicalTree Prune 7", "[musicalTree-prune-7]") {
  MusicalTree tr(false);
  MotifNode* root = tr.GetRoot();

  vector<Note> mot = {{1, 2}, {2, 3}, {2, 3}, {2, 3}, {2, 3}, {2, 3}};
  root->SetFitnessScore(90);

  MotifNode* md2 = new MotifNode(mot);
  md2->SetFitnessScore(10);
  root->AddChildNode(md2);

  MotifNode* md3 = new MotifNode(mot);
  md3->SetFitnessScore(80);
  md2->AddChildNode(md3);

  MotifNode* md4 = new MotifNode(mot);
  md4->SetFitnessScore(68);
  md2->AddChildNode(md4);

  MotifNode* md7 = new MotifNode(mot);
  md7->SetFitnessScore(35);
  md4->AddChildNode(md7);

  MotifNode* md8 = new MotifNode(mot);
  md8->SetFitnessScore(36);
  md4->AddChildNode(md8);

  tr.PruneNodes(root, 15);
  int size = 0;
  REQUIRE(ValidateTree(root, root, size));
  REQUIRE(size == 5);

  // 90's children
  vector<MotifNode*> md1_c = root->GetChildren();

  REQUIRE(md1_c.size() == 1);
  REQUIRE(md1_c[0]->GetFitnessScore() == 68);

  // 68's children
  vector<MotifNode*> md2_c = md1_c[0]->GetChildren();

  REQUIRE(md2_c.size() == 3);
  REQUIRE((md2_c[0]->GetFitnessScore() == 80 ||
           md2_c[1]->GetFitnessScore() == 80 ||
           md2_c[2]->GetFitnessScore() == 80));
  REQUIRE((md2_c[0]->GetFitnessScore() == 35 ||
           md2_c[1]->GetFitnessScore() == 35 ||
           md2_c[2]->GetFitnessScore() == 35));
}

// replace root
TEST_CASE("MusicalTree Prune 8", "[musicalTree-prune-8]") {
  MusicalTree tr(false);
  MotifNode* root = tr.GetRoot();

  vector<Note> mot = {{1, 2}, {2, 3}, {2, 3}, {2, 3}, {2, 3}, {2, 3}};
  root->SetFitnessScore(10);

  MotifNode* md2 = new MotifNode(mot);
  md2->SetFitnessScore(90);
  root->AddChildNode(md2);

  MotifNode* md3 = new MotifNode(mot);
  md3->SetFitnessScore(80);
  md2->AddChildNode(md3);

  MotifNode* md5 = new MotifNode(mot);
  md5->SetFitnessScore(20);
  md3->AddChildNode(md5);

  MotifNode* md6 = new MotifNode(mot);
  md6->SetFitnessScore(20);
  md3->AddChildNode(md6);

  MotifNode* md4 = new MotifNode(mot);
  md4->SetFitnessScore(68);
  md2->AddChildNode(md4);

  tr.PruneNodes(root, 30);
  int size = 0;
  REQUIRE(ValidateTree(tr.GetRoot(), tr.GetRoot(), size));
  REQUIRE(size == 3);
}