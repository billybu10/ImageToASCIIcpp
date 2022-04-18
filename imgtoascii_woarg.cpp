#include <iostream>
#include "CImglib/CImg.h"
#include <string.h>
#include <math.h>
#include <fstream>

using namespace std;
using namespace cimg_library;

string outputPath;
int outputWidth, outputHeight;
int* arrayGrey;
char* inputPath = new char[50];
string* charArray;

char ASCII_CHARS[12] = {' ', '.', ',', ':', ';', '+', '*', '?', '%', 'S', '#', '@'};


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

void openAndCimg(){
    CImg<unsigned char> image(inputPath);
    image.resize(outputWidth, outputHeight, 1, 3);
    cimg_forXY(image,x,y) {
        // Separation of channels
        int R = (int)image(x,y,0,0);
        int G = (int)image(x,y,0,1);
        int B = (int)image(x,y,0,2);
        // Real weighted addition of channels for gray
        int grayValueWeight = (int)(floor(0.299*R + 0.587*G + 0.114*B));
        // saving píxel values into image information
        *(arrayGrey + x + y*outputWidth) = grayValueWeight;
    }
}

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
    arrayGrey= new int[outputWidth * outputHeight];
    openAndCimg();
    charArray = new string[outputHeight];
    greyToAscii();
    goThroughAndOutput();
    delete[] arrayGrey;
    delete inputPath;
    return 0;
}
