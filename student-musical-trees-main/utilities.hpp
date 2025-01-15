
#ifndef UTILITIES_HPP
#define UTILITIES_HPP

#include <lame/lame.h>

#include <cmath>
#include <iostream>
#include <stdexcept>
#include <vector>

#include "motif_node.hpp"
#include "musical_tree.hpp"

double PitchToFrequency(int pitch);

void GenerateMP3(vector<Note> melody, const string& file_name);

#endif