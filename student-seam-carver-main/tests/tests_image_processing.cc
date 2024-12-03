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

TEST_CASE("ImageProcessing Flip Left", "[ImageProcessing-FlipLeft]") {
  Image img_proc1("tests/test_images/test4x3.ppm");
  RotateLeft(img_proc1);

  Image img1_rotate_left("tests/test_images/test4x3_left.ppm");
  REQUIRE(CompareImages(img1_rotate_left, img_proc1));
}

// Add more tests below!
// Look inside the tests/test_images folder for sample small images.
// Feel free to also make your own!
// Use the helper functions in tests_helpers.hpp and tests_helpers.cc to compare images.