#include "image_processing.hpp"
#include <string> 

using namespace std;

/// HELPER FUNCTIONS 
void ReduceWidth(Image& theImage, int width){
    while (theImage.Width() != width){
      vector<int> theSeam = FindVerticalSeam(theImage); 
      RemoveVerticalSeam(theImage, theSeam); 
      //cout << "Image width: " << to_string(theImage.Width()) << endl;
    } 
}

void ReduceHeight(Image& theImage, int height){
  //cout << "Entered reduce height" << endl; 
  //cout << "initial Image height: " << to_string(theImage.Height()) << endl;
  //cout << "desired height: " << to_string(height) << endl;
  RotateLeft(theImage); 
  while (theImage.Width() != height){
    vector<int> theSeam = FindVerticalSeam(theImage); 
    RemoveVerticalSeam(theImage, theSeam);
    //cout << "Image height: " << to_string(theImage.Height()) << endl;
  }  
  RotateRight(theImage); 

}

string getBaseFileName(string const& path){
  return path.substr(path.find_last_of("//") + 1);
}

void removePPM(string& str){
  int position = str.find(".ppm"); 
  str.erase(position, 4); 
}

int main(int argc, char* argv[]) {
  Image* ourImage; 
  //cout << "before try block" << endl; 
  if (argc != 4){
    cout << "The format is, <image_name> <new_width> <new_height>" << endl; 
    //exit(1); 
    return 0; 
  }
  
  //cout << argv[0] << " " << argv[1] << " " << argv[2] << " " << argv[3] << endl; 
  string image_name = argv[1];
  int new_width = stoi(argv[2]); 
  int new_height = stoi(argv[3]); 

  try { 
    ourImage = new Image(image_name);  
  } catch(runtime_error e){
    cout << e.what() << endl; 
    //exit(1);
    return 0; 
  }

  //ourImage = new Image(image_name); 

  if (new_width > ourImage->Width()){
    cout << "Width is too big. We cannot currently grow the image." << endl; 
    //exit(1);
    return 0; 
  } 
  if (new_height > ourImage->Height()){
    cout << "Height is too big. We cannot currently grow the image." << endl; 
    //exit(1);
    return 0;  
  }

  //reduce width & height 
  ReduceWidth(*ourImage, new_width);
  ReduceHeight(*ourImage, new_height); 

  string base_file_name = getBaseFileName(argv[1]); 
  removePPM(base_file_name);
  string newFileName = base_file_name + to_string(new_width) + "x" + to_string(new_height) + "_actual.ppm";

  //write the image into a PPM file
  ourImage->SaveToFile(newFileName);

}

