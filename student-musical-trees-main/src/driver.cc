#include "musical_tree.hpp"
#include "utilities.hpp"

int main() {
  // Create MelodyGenerator object
  MusicalTree mt(true);
  GenerateMP3(mt.GenerateMelody(), "starting.mp3");

  // Evolve the tree structure for a fixed number of generations
  mt.GeneticAlgorithm(150);

  // Generate melody by traversing the evolved tree structure
  std::vector<Note> melody = mt.GenerateMelody();

  // Generage MP3 based on melody vector
  GenerateMP3(melody, "output.mp3");
}
