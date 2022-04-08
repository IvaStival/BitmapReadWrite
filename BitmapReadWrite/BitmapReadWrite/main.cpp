//
//  main.cpp
//  BitmapReadWrite
//
//  Created by iva stival on 07/04/22.
//

#include <cmath>
#include <iomanip>
#include <iostream>

#include "bitmap.hpp"

using namespace std;

int main(int argc, const char * argv[]) {
    bitmap bmp;
    
    bmp.readFile("/Users/ivastival/OneDrive/Documentos/_Blog/Code/Projects/BitmapReadWrite/code/BitmapReadWrite/BitmapReadWrite/"
                 "images/sample.bmp");
    
    bmp.writeFile("/Users/ivastival/OneDrive/Documentos/_Blog/Code/Projects/BitmapReadWrite/code/BitmapReadWrite/BitmapReadWrite/"
                  "images/image2.bmp");

    return 0;
}
