#include <iostream>
#include <string>
#include "CImglib/CImg.h"
#include <string.h>
#include <math.h>
#include <fstream>

using namespace std;
using namespace cimg_library;

//global values so i don't have to use returns and even more of array nightmare
string outputPath;
int outputWidth, outputHeight;
int* arrayGrey;
char* inputPath = new char[260];
string* charArray;

//array of chars used in asciiart, from dimmest to brightest
char ASCII_CHARS[12] = {' ', '.', ',', ':', ';', '+', '*', '?', '%', 'S', '#', '@'};

//gets input and output paths and ascii art size from user
void loadData(){
    cout << "Enter input file path : ";
    cin >> inputPath;
    cin.ignore(255,'\n');
    cout << "Enter output file path : ";
    cin >> outputPath;
    cin.ignore(255,'\n');
    cout << "Enter output width : ";
    cin >> outputWidth;
    cin.ignore(255,'\n');
    cout << "Enter output height : ";
    cin >> outputHeight;
}

//imports format specific libraries //i'm editing this after a few years and honestly, this function serves no purpose, macros are analyzed before the actual code compiles, but it will work so... i don't care
void checkFormat(){
    string s(inputPath);
    string::size_type woe = s.find( ".jpeg\0", 0 );
    string::size_type wie = s.find( ".jpg\0", 0 );
    if ((woe != string::npos)||(wie != string::npos)){
        #define cimg_use_jpeg
    }
    string::size_type peneg = s.find( ".png\0", 0 );
    if (peneg != string::npos){
        #define cimg_use_png
    }
}

//reads image, turns into greyscale and writes to greyscale array
void openAndCimg(){
    CImg<unsigned char> image(inputPath);
    image.resize(outputWidth, outputHeight, 1, 3);
    cimg_forXY(image,x,y) {
        // Separation of channels
        int R = (int)image(x,y,0,0);
        int G = (int)image(x,y,0,1);
        int B = (int)image(x,y,0,2);
        // Real weighted addition of channels for grey
        int greyValueWeight = (int)(floor(0.299*R + 0.587*G + 0.114*B));
        // saving píxel values into image information
        *(arrayGrey + x + y*outputWidth) = greyValueWeight;
    }
}


//goes through every pixel in greyscale array and replaces it with correspponding ascii char
void greyToAscii(){
    string asciibuff;
    int numbuff;
    for (int i = 0; i < outputHeight; i++)
    {
        for (int j = 0; j < outputWidth; j++)
        {
            //gets right char for pixels intensity, 20, cause max value of 255/22 is lower than 12, which would go outside the ASCII_CHARS
            numbuff = floor(((*(arrayGrey + j + i*outputWidth))/23));
            asciibuff.push_back(ASCII_CHARS[numbuff]);
        }
        *(charArray + i) = asciibuff;
        asciibuff = "";
    }
}

//presents output in terminal + writes to file
void goThroughAndOutput(){
    ofstream outFile;
    outFile.open(outputPath);
    for(int i=0; i<outputHeight; i++){
        cout<< *(charArray + i) <<endl;
        outFile << *(charArray + i)<< endl;
    }
}

int main(){
    loadData();
    checkFormat();
    arrayGrey= new int[outputWidth * outputHeight];
    openAndCimg();
    charArray = new string[outputHeight];
    greyToAscii();
    goThroughAndOutput();
    delete[] arrayGrey;
    delete inputPath;
    return 0;
}
