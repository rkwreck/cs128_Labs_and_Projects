#include "image_processing.hpp"
using namespace std;

// Write the functions from image_processing below.


// MP PART: 1

void RotateLeft(Image& image_){
    //cout << "Entered rotate left" << endl; 
    //get the dimensions of the vector
    int n = image_.Height(); 
    int m = image_.Width(); 

    Image temp(m, n); 

    //vector<vector<Pixel>> temp(m, vector<Pixel>(n)); //we want the type to stay the same, we're just changing the locations

    for (int i = 0; i < n; i++){
        //int counter = 0;
        for (int j = 0; j < m; j++){
            //temp.SetPixel(i, j)
            //row, col, new_pixel

            //so we want to switch row & column
            //so our row is width - 1 - j 
            //bc counting starts at index 0 
            //j is what we had with counter earlier

            temp.SetPixel(image_.Width() - 1 - j, i, image_.GetPixel(i, j));

            //temp[i][counter] = image_[counter][m - counter];
            // temp[i][counter] = image_.GetPixel(counter, m-counter); 
            // counter++; 
        }
    }

    //rewrite temp into image bc this function is void
    image_ = temp; 
}


// MP PART: 1
void RotateRight(Image& image_){
    //cout << "Entered rotate right" << endl; 
    RotateLeft(image_); 
    RotateLeft(image_);
    RotateLeft(image_);
}

// REQUIRES: image_ is a rectangle of pixels.
// MODIFIES:
// EFFECTS: Returns the energy matrix for image_. See spec for algorithm.
//          hint: use SquaredPixelEnergy() from pixel.hpp
//          hint: use kHighEnergy


// MP PART: 2
vector<vector<int>> CalculateEnergy(const Image& image_){
    //cout << "Entered calculate energy" << endl; 
    assert(image_.Height() > 0 && image_.Width() > 0);

    vector<vector<int>> energies; //our energy matrix 

    vector<int> temp; //to push back later

    for (int i = 0; i < image_.Height(); i++){
        for (int j = 0; j < image_.Width(); j++){
            int energy = 0; 
            //check if the pixel is a border pixel
            if (i == image_.Height() - 1 || i == 0 || j == image_.Width() - 1 || j == 0){
                energy = kHighEnergy; 
            } else {
                Pixel north = image_.GetPixel(i-1, j);
                Pixel south = image_.GetPixel(i+1, j);
                Pixel east = image_.GetPixel(i, j + 1);
                Pixel west = image_.GetPixel(i, j-1);
                // Pixel north = image_[i-1][j];
                // Pixel south = image_[i+1][j];
                // Pixel east = image_[i][j + 1];
                // Pixel west = image_[i][j - 1];

                energy = SquaredPixelEnergy(north, south) + SquaredPixelEnergy(east, west);
            }

            temp.push_back(energy); //energy is an int 
            // if (temp.size() == image_.Width){
            //     pixels.push_back(temp);
            //     temp.clear(); 
            // } 
        }

        //after every row (width), add all the energies of that row
        energies.push_back(temp);  
        temp.clear();

    //do a for loop through the image_ vector 
    //first check if the pixel's a border pixel
        //if it is --> 
        // the energy is kHighEnergy
    //if not --> 
        //grab the pixel's north buddy and store it
        //grab the pixel's south buddy and store it
        //input them into SquaredPixelEnergy
        //grab the pixel's east buddy and store it
        //grab the pixel's west buddy and store it
        //input them into SquaredPixelEnergy and add it to the SPEnergy above
        //store that into energy variable
    //store that value in the same location that the original pixel was in


    //to find the location of the pixel:
        //use [i][j]
        //west: [i][j - 1]
        //east: [i][j + 1];
        //south: [i + 1][j]
        //north: [i - 1][j]

    //and also when to clear the vector: 
        //clear when the vector temp size is equal to width 
        //then push back into the larger vector 
        //and clear temp 

    }
    return energies; 
}



// REQUIRES: energy is a rectangle.
// MODIFIES:
// EFFECTS: Returns the vertical cost matrix for energy. See spec for the algorithm.
// MP PART: 2
vector<vector<int>> CalculateCostVertical(const vector<vector<int>>& energy){
    //cout << "calculate cost vertical" << endl; 
    //assert(image_.Height() > 0 && image_.Width() > 0);
    assert(energy[0].size() > 0 && energy.size() > 0);

    vector<vector<int>> costs; //vertical cost matrix for energy that we will be returning
  
    int cost = 0; 
    vector<int> temp; //we want to push back vectors into costs

    //for (int j = 0; j < image_.Width(); j++){
    for (int j = 0; j < energy[0].size(); j++){
        cost = energy[0][j];
        temp.push_back(cost); //we want to push back a vector into costs 
    }
    costs.push_back(temp); 


    temp.clear(); 
    //now do the rest of the pixels
    //for (int i = 1; i < image_.Height(); i++){
    for (int i = 1; i < energy.size(); i++){
        //cost = 0; 
        for (int j = 0; j < energy[i].size(); j++){
             //ifstatement version 
            if (j == 0){ //leftmost side 
                // cost = energy[i][j] + min(energy[i - 1][j], energy[i][j + 1]); 
                cost = energy[i][j] + min(costs[i - 1][j], costs[i-1][j + 1]); 
                //cost = energy[i][j] + min(costs[i - 1][j], temp[j + 1]); 
            } else if (j == energy[i].size() - 1){  //rightmost side 
                // cost = energy[i][j] + min(energy[i - 1][j], energy[i][j - 1]); 
                cost = energy[i][j] + min(costs[i - 1][j], costs[i-1][j - 1]); 
                //cost = energy[i][j] + min(costs[i - 1][j], temp[j - 1]); 
            } else {  //not a border pixel 
                // cost = energy[i][j] + min(energy[i-1][j-1], min(energy[i-1][j], energy[i-1][j+1]));
                cost = energy[i][j] + min(costs[i-1][j-1], min(costs[i-1][j], costs[i-1][j+1]));
            }
            temp.push_back(cost); 
        }

        //after every row (width), add all the costs of that row
        costs.push_back(temp);
        temp.clear();
    }

  
    return costs; 
}


// REQUIRES: image_ is a rectangle of pixels.
// MODIFIES:
// EFFECTS: Returns the lowest energy vertical seam in the image. The returned
//          vector's size is image_ height. Each element in the vector is
//          between [0, image_ width). The value at the 0th index indicates the
//          column value of the seam at row 0 and so forth. See spec for the
//          algorithm. hint: You will need to call CalculateEnergy, and
//          CalculateCostVertical.
// MP PART: 2
//vector<int> FindVerticalSeam(const Image& image_){
    //return FindVerticalSeam_Original(image_); 

    // assert(image_.Height() > 0 && image_.Width() > 0);
    // vector<vector<int>> cost_matrix = CalculateCostVertical(CalculateEnergy(image_));

    // vector<int> seam; 

    // //find our starting point 
    // int lowestCost = cost_matrix[image_.Height() - 1][0];
    // int location = 0; 
    // for(int j = 0; j < image_.Width(); j++){
    //     if (cost_matrix[image_.Height() - 1][j] < lowestCost){
    //         lowestCost = cost_matrix[image_.Height() - 1][j];
    //         location = j; 
    //     }
    // }
    // seam.push_back(location); //save the column value 

    // //now we can develop the rest of the seam
    // //vector<vector<int>> tempValue = 0; 
    // int minVal = 0; 
    // for(int i = image_.Height() - 2; i >= 0; i--){
    //     //for (int j = location; j < image_.Width(); j++){
    //     if (location == 0){      //leftmost side 
    //         if (cost_matrix[i][location] <= cost_matrix[i][location + 1]){
    //             seam.push_back(location);
    //         } else {
    //             seam.push_back(location + 1);
    //             location += 1; 
    //         }

    //         //next = min(cost_matrix[i][j], cost_matrix[i][j + 1]);
    //         //seam.push_back()
    //     } else if (location == image_.Width() - 1){    //rightmost side
    //         if (cost_matrix[i][location - 1] <= cost_matrix[i][location]){
    //             seam.push_back(location - 1);
    //             location -= 1;
    //         } else {
    //             seam.push_back(location);
    //         }
    //         //next = min(cost_matrix[i][j-1], cost_matrix[i][j]);
    //     } else {
    //         if (cost_matrix[i][location-1] <= cost_matrix[i][location]){
    //             if (cost_matrix[i][location-1] <= cost_matrix[i][location + 1]){
    //                 seam.push_back(location-1);
    //                 location -= 1; 
    //             } else {
    //                 seam.push_back(location + 1);
    //                 location += 1; 
    //             }
    //         } else if (cost_matrix[i][location] <= cost_matrix[i][location + 1]){
    //             seam.push_back(location);
    //         } else {
    //             seam.push_back(location + 1);
    //             location += 1; 
    //         }
    //         //min automatically takes care of the leftmost condition 
    //         //next = min(cost_matrix[i][j-1], cost_matrix[i][j], cost_matrix[i][j + 1]);
    //     } 
    // }

    // return seam;
//}

    ///////// ORIGINAL VERSION (3/5 TEST CASES PASSED) 
vector<int> FindVerticalSeam(const Image& image_){
    //cout << "Entered find vertical seam" << endl; 
    assert(image_.Height() > 0 && image_.Width() > 0);
    vector<vector<int>> cost_matrix = CalculateCostVertical(CalculateEnergy(image_));

    vector<int> seam; 

    //find our starting point 
    int lowestCost = cost_matrix[image_.Height() - 1][0];
    int location = 0; 
    for(int j = 0; j < image_.Width(); j++){
        if (cost_matrix[image_.Height() - 1][j] < lowestCost){
            lowestCost = cost_matrix[image_.Height() - 1][j];
            location = j; 
        }
    }
    seam.push_back(location); //save the column value 

    //int minVal = 0; 
    for(int i = image_.Height() - 2; i >= 0; i--){
        if (location == 0){      //leftmost side 
            if (cost_matrix[i][location] <= cost_matrix[i][location + 1]){
                seam.push_back(location);
            } else {
                seam.push_back(location + 1);
                location += 1; 
            }

        } else if (location == image_.Width() - 1){    //rightmost side
            if (cost_matrix[i][location - 1] <= cost_matrix[i][location]){
                seam.push_back(location - 1);
                location -= 1;
            } else {
                seam.push_back(location);
            }
        } else {   //general case
            if (cost_matrix[i][location-1] <= cost_matrix[i][location]){
                if (cost_matrix[i][location-1] <= cost_matrix[i][location + 1]){
                    seam.push_back(location-1);
                    location -= 1; 
                } else {
                    seam.push_back(location + 1);
                    location += 1; 
                }
            } else if (cost_matrix[i][location] <= cost_matrix[i][location + 1]){
                seam.push_back(location);
            } else {
                seam.push_back(location + 1);
                location += 1; 
            }
        
        }
    }

    //reverse seam 
    vector<int> newSeam; 
    for (int i = seam.size() - 1; i >= 0; i--){
         newSeam.push_back(seam[i]);
     }
    return newSeam; 
    //return seam; 
}


// REQUIRES: seam is of size image_ height and each element in seam is between
//           [0, image width). image_ is a rectangle of pixels.
// MODIFIES: image_
// EFFECTS: Removes one pixel from each row from the image per the col value
//          found in the seam.
// MP PART: 2
void RemoveVerticalSeam(Image& image_, const std::vector<int>& seam){
    //cout << "Entered remove vertical seam" << endl; 
    //seam is the vector we want to remove 
    for (int i = 0; i < image_.Height(); i++){
        image_.RemovePixel(i, seam[i]); 
        // for (auto j : seam){
        //     image_.RemovePixel(i, j); 
        // }
    }
}
    

// vector<int> FindVerticalSeam_Didi_Version(const Image& image_){
//     assert(image_.Height() > 0 && image_.Width() > 0);
//     vector<vector<int>> cost_matrix = CalculateCostVertical(CalculateEnergy(image_));

//     vector<int> seam; 

//     //find our starting point 
//     int lowestCost = cost_matrix[image_.Height() - 1][0];
//     int location = 0; 
//     for(int j = 0; j < image_.Width(); j++){
//         if (cost_matrix[image_.Height() - 1][j] < lowestCost){
//             lowestCost = cost_matrix[image_.Height() - 1][j];
//             location = j; 
//         }
//     }
//     seam.push_back(location); //save the column value

//     int minVal = 0; 
//     for(int i = image_.Height() - 2; i >= 0; i--){
//         if (location == 0){      //leftmost side 
//             if (cost_matrix[i][location] <= cost_matrix[i][location + 1]){
//                 seam.push_back(location);
//             } else {
//                 seam.push_back(location + 1);
//                 location += 1; 
//             }
//         } else if (location == image_.Width() - 1){    //rightmost side
//             if (cost_matrix[i][location - 1] <= cost_matrix[i][location]){
//                 seam.push_back(location - 1);
//                 location -= 1;
//             } else {
//                 seam.push_back(location);
//             }

//         } else {     //general case 
//             minVal = min(cost_matrix[i][location + 1], min(cost_matrix[i][location - 1], cost_matrix[i][location]));
//             for (int x = location - 1; x < location + 2; x++){
//                 if (cost_matrix[i][x] == minVal){
//                     seam.push_back(x);
//                     location = x; 
//                 }
//             }
//         }
//     }   

// }

    

        ///////// ORIGINAL CODE 
    
       
        // //for (int j = location; j < image_.Width(); j++){
        // if (location == 0){      //leftmost side 
        //     if (cost_matrix[i][location] <= cost_matrix[i][location + 1]){
        //         seam.push_back(location);
        //     } else {
        //         seam.push_back(location + 1);
        //         location += 1; 
        //     }

        //     //next = min(cost_matrix[i][j], cost_matrix[i][j + 1]);
        //     //seam.push_back()
        // } else if (location == image_.Width() - 1){    //rightmost side
        //     if (cost_matrix[i][location - 1] <= cost_matrix[i][location]){
        //         seam.push_back(location - 1);
        //         location -= 1;
        //     } else {
        //         seam.push_back(location);
        //     }
        //     //next = min(cost_matrix[i][j-1], cost_matrix[i][j]);
        // } else {
        //     if (cost_matrix[i][location-1] <= cost_matrix[i][location]){
        //         if (cost_matrix[i][location-1] <= cost_matrix[i][location + 1]){
        //             seam.push_back(location-1);
        //             location -= 1; 
        //         } else if (cost_matrix[i][location+1] <= cost_matrix[i][location]){
        //             seam.push_back(location + 1);
        //             location += 1;
        //         } else {
        //             seam.push_back(location);
        //         }
        //         // } else {
        //         //     seam.push_back(location + 1);
        //         //     location += 1; 
        //         // }
        //     } else if (cost_matrix[i][location] <= cost_matrix[i][location + 1]){
        //         if (cost_matrix[i][location] <= cost_matrix[i][location -1]){
        //             seam.push_back(location-1);
        //             location -= 1; 
        //         } else if (cost_matrix[i][location+1] <= cost_matrix[i][location]){
        //             seam.push_back(location + 1);
        //             location += 1;
        //         } else {
        //             seam.push_back(location);
        //         }
        //         seam.push_back(location);
        //     } else {
        //         seam.push_back(location + 1);
        //         location += 1; 
        //     }
        //     //min automatically takes care of the leftmost condition 
        //     //next = min(cost_matrix[i][j-1], cost_matrix[i][j], cost_matrix[i][j + 1]);
        // }

    //     return seam; 
    // }


//ALGOIRTHMS 

   /*
    ALGORITHM:
    1. start at the bottom of the COST matrix from CalculateCostVertical
        - call the CalculateCostVertical matrix on image_
        - save that 
        - grab the length, the bottom is length - 1
        - save that value as well
    2. find the smallest cost value from the matrix --> this needs to be an [i][j]
    3. move up, find the minimum among: [i + 1][j], [i - 1][j], [i][j]
        - if there is a tie, use the leftmost pixel
        - always check if you've reached the border 
    4. add this minimum to the vector we are returning. this vector should not exceed Height().
    5. the vector should just contains the column value bc it is vertical. 
        - bc you are stacking through the ROWS so we just need the column value 
    
    */

//}

  //initialize the energies for the top row 
    // for (int i = 0; i < 1; i++){
    //     for (int j = 0; j < image_.Width; j++){
    //         cost = energy[i][j]; 
    //         temp.push_back(cost); 
    //         // costs.push_back(cost); 
    //     }
    // }


            //check if the pixel's a border
            //why are there so many cases for this
            //oh nvm theres actually not that many cases 

            //rewrite this to be try-catch?? 

  //for loop through the given energy vector
    //int energy = 0;
    //first check if the pixel is a border pixel
        //if it is --> 
        //check what kind of border pixel it is 
        //and then add its energy + min of (top, size)

        //if it's not --> 
        //energy + min of (side pixel, other side pixel, top pixel)
            //you will need to check case-by-case basis for this
            //it is always top side side
            //so if it is a border pixel then it will be top side
            //ignore the bottom pixel