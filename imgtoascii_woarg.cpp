#include <iostream>
#include "CImglib/CImg.h"

using namespace std;
using namespace cimg_library;

string outputPath;
int outputWidth, outputHeight;
int* arrayGrey;
char* inputPath = new char[50], charaaray;


void loadData(){
    cout << "Enter input file path : ";
    cin >> *inputPath;
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

void cimgProc(){
    CImg<unsigned char> image = CImg<>(*inputPath).resize(outputWidth, outputHeight, 1, 3);
    cimg_forXY(image,x,y) {
        // Separation of channels
        int R = (int)image(x,y,0,0);
        int G = (int)image(x,y,0,1);
        int B = (int)image(x,y,0,2);
        // Real weighted addition of channels for gray
        int grayValueWeight = (int)(0.299*R + 0.587*G + 0.114*B);
        // saving píxel values into image information
        *(arrayGrey + x + y) = grayValueWeight;
    }
}



int main(){
    loadData();
    arrayGrey= new int[outputWidth * outputHeight];
    cimgProc();

    delete[] arrayGrey;
    delete inputPath;
    return 0;
}
