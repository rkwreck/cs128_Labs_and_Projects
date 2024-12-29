#include <algorithm>
#include <cmath>
#include <iostream>
#include <stdexcept>
#include <vector>

#include "motif_node.hpp"

using namespace std;

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