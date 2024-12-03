#include "image.hpp"
using namespace std;

// Write the member functions of Image below.

// REQUIRES: height and width are > 0.
// MODIFIES: Image
// EFFECTS: Initializes an image of height x width.
// MP PART: 1
Image::Image(int height, int width){
    assert(height > 0 && width > 0);
    data_.resize(height); //resize outer vector

    //resize inner vector 
    for (int i = 0; i < height; i++){
        data_[i].resize(width); 
    } 
}


// REQUIRES: filename leads to a valid PPM P3 file.
// MODIFIES: Image
// EFFECTS: Initializes an image from a PPM file at filename.
//          If the file cannot be opened, throw a runtime_error exception with
//          the message "File could not be opened."
// MP PART: 1
Image::Image(const std::string& filename){
    ifstream fcin(filename); 

    if (!fcin.is_open()){
        throw runtime_error("File could not be opened.");
        //cout << "File could not be opened." << endl; 
        //exit(1); 
        //end(0); 
    }

    string trash;
    int height, width, num; 

    fcin >> trash >> width >> height >> num; 
    
    //write in the pixels 
    //convert rgb to pixel and then put pixel to vector
    //if vector is equal to length, push into data_, clear vector

    vector<Pixel> temp; //this is what we write into data 
    int spacer = 0; 
    int x; 

    //we can't lose the other values in Pixel after an iteration
    //so we have to use global variables or else we lose the data  
    int red = 0; 
    int green = 0; 
    int blue = 0; 

    while (fcin >> x){
        Pixel tempPixel; 
        //pixels are every 3 bc of rgb 
        //first one is always r
        if (spacer % 3 == 0){
            red = x;
            spacer++; //move to the next color 
        } else if (spacer % 3 == 1){ //second one is always g
            green = x; 
            //tempPixel.g = x;  
            spacer++;  
        } else if (spacer % 3 == 2){ //third one is always b
            blue = x; 

            //now we've finished the set, so let's add everything in
            tempPixel.r = red; 
            tempPixel.g = green; 
            tempPixel.b = blue; 
            temp.push_back(tempPixel); 
            spacer++; 
        }

        if (temp.size() == width){
            //temp.push_back(" "); 
            data_.push_back(temp); 
            temp.clear(); 

            //we don't need to reset counter since the conditionals work fine 
            //counter = 0;
        }
    }    
}
    

// REQUIRES:
// MODIFIES:
// EFFECTS: Writes the image to a PPM file named filename.
//          The three header items in the PPM file are not followed by a space, just a 
//          newline. Each pixel is printed in the format of "<red> <green> <blue> ". 
//          This includes the last pixel in the row. Each row is followed by a newline. 
// MP PART: 1
void Image::SaveToFile(const std::string& filename){
    ofstream fout(filename); 
    
    //the standard stuff of the header 
    fout << "P3" << endl; 
    fout << Width() << " " << Height() << endl; 
    fout << 255 << endl; 

    for (auto& x : data_){
        for(size_t y = 0; y < x.size(); y++){
            Pixel& pix = x[y]; 
            fout << pix.r << " " << pix.g << " " << pix.b; 
            //because of exact checking 
            if (y < x.size() - 1){
                fout << " "; 
            }
        }
        fout << " " << "\n"; 
    }
}

// REQUIRES: data_ has at least 1 row.
// MODIFIES:
// EFFECTS: Returns the width of the 1st row of the image as an int.
//          Use assert to check the REQUIRES.
// MP PART: 1
int Image::Width() const{
    assert (data_.size() > 0); //we haven't defined height function yet 
    return data_[0].size(); 
    
}


// REQUIRES:
// MODIFIES:
// EFFECTS: Returns the image height as an int.
// MP PART: 1
int Image::Height() const{
    return data_.size(); 
}

// REQUIRES: row is between [0, height), and col is between [0, width).
// MODIFIES:
// EFFECTS: Returns the pixel at row, col.
//          Use assert to check the REQUIRES.
// MP PART: 1
Pixel Image::GetPixel(int row, int col) const{
    assert (row >= 0 && row < Height());
    assert (col >= 0 && col < data_[row].size()); 
    return data_[row][col]; 
}

// REQUIRES: row is between [0, height), col is between [0, width), and
//           new_pixel is a valid pixel.
// MODIFIES: Image
// EFFECTS: Sets the pixel at row, col to new_pixel.
//          Use assert to check the REQUIRES.
// MP PART: 1
void Image::SetPixel(int row, int col, Pixel new_pixel){
    assert (row >= 0 && row < Height()); 
    assert (col >= 0 && col < data_[row].size()); 
    
    data_[row][col] = new_pixel; 

}

// REQUIRES: row is between [0, height), col is between [0, width). There are
//            at least 2 pixels in row's corresponding row.
// MODIFIES: Image
// EFFECTS: Removes the pixel at row, col. Changing that row to have one less
//          pixel. Use assert to check the requires.
//          hint: Feel free to use any vector member functions
// MP PART: 1
void Image::RemovePixel(int row, int col){
    assert (row >= 0 && row < Height() && data_[row].size() >= 2); 
    assert (col >= 0 && col < data_[row].size()); 

    data_[row].erase(data_[row].begin() + col); 
}






