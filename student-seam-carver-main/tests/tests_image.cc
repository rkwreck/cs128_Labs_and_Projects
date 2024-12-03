/////////////////////////////////////////////////////////////////////////////////////////////
//                             Framework Set-up //
/////////////////////////////////////////////////////////////////////////////////////////////
#ifndef CATCH_CONFIG_MAIN
#  define CATCH_CONFIG_MAIN
#endif
#include <catch/catch.hpp>

/////////////////////////////////////////////////////////////////////////////////////////////
//                                 Includes //
/////////////////////////////////////////////////////////////////////////////////////////////
#include <algorithm>
#include <fstream>
#include <string>
#include <vector>

#include "image.hpp"
#include "image_processing.hpp"
#include "tests_helpers.hpp"

using namespace std;

///////////////////////////////////////////////////////////////////////////////////////////
// Test Cases //
///////////////////////////////////////////////////////////////////////////////////////////

// Feel free to add or remove testcases. Below are just a few to help you get
// started.

TEST_CASE("Empty Image constructor", "[Image-constructor]") {
  Image img(2, 40);

  REQUIRE(img.Height() == 2);
  REQUIRE(img.Width() == 40);
}

// Look inside the tests/test_images folder for sample small images.
// Feel free to also make your own!
// Use the helper functions in tests_helpers.hpp and tests_helpers.cc to compare images.
TEST_CASE("Image constructor with images", "[Image-constructor]") {}

TEST_CASE("Image Set Pixel and Get Pixel", "[Image-SetPixel][Image-GetPixel]") {
}

TEST_CASE("Image Remove Pixel", "[Image-RemovePixel]") {}
