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

//array of chars used in asciiart created by code
char ASCII_CHARS[12] = {' ', '.', ',', ':', ';', '+', '*', '?', '%', 'S', '#', '@'};

//self explanatory
void loadData(int argc, char *argv[]){
    for (int i = 0; i < argc; ++i){
        switch (i)
        {
        case 1:
            inputPath = *(argv+i);
            break;

        case 2:
            outputPath = *(argv+i);
            break;

        case 3:
            outputWidth = atoi(*(argv+i));
            break;

        case 4:
            outputHeight = atoi(*(argv+i));
            break;
        
        default:
            break;
        }
    }
}

//imports format specific libraries
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

int main(int argc, char *argv[]){
    loadData(argc, argv);
    checkFormat();
    arrayGrey= new int[outputWidth * outputHeight];
    openAndCimg();
    charArray = new string[outputHeight];
    greyToAscii();
    goThroughAndOutput();
    delete[] arrayGrey;
    return 0;
}
