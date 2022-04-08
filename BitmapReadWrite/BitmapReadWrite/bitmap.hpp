//
//  bitmap.hpp
//  BitmapReadWrite
//
//  Created by iva stival on 07/04/22.
//

#ifndef bitmap_hpp
#define bitmap_hpp

#include <iostream>
#include <string>

#include "logging.hpp"


// BITMAP FILE HEADER STRUCT (14 BYTES)
struct header{
    char signature[2];      // BM
    char file_size[4];      // FILE SIZE IN BYTES
    char reserved1[2];      // RESERVED SPACE1
    char reserved2[2];      // RESERVED SPACE2
    char data_offset[4];    // OFFSET FROM THE BEGING OF THE FILE AND THE INIT OF THE BITMAP DATA
};

// INFO DATA HEADER
// HERE ARE SAVED THE IMAGE INFORMATION (40 BYTES)
struct infoHeader{
    char size[4];           // SIZE OF THE INFO HEAD (40)
    char width[4];          // IMAGE WIDTH IN PIXELS
    char height[4];         // IMAGE HEIGHT IN PIXELS
    char planes[2];         // NUMBER OF PLANES (1)
    char bits_pixel[2];     // Used to store palette entry information. This also identifies in an indirect way the number of possible colors.
                            // Possible values are:
                            // 1 = monochrome palette. NumColors = 1
                            // 4 = 4bit palletized. NumColors = 16
                            // 8 = 8bit palletized. NumColors = 256
                            // 16 = 16bit RGB. NumColors = 65536
                            // 24 = 24bit RGB. NumColors = 16M
    
    char compression[4];    // COMPRESSION TYPE
                            // 0 = BI_RGB (NO COMPRESSION)
                            // 1 = BI_RLE 8bit (RLE ENCODING)
                            // 2 = BI_RLE4 4bit (RLE ENCODING)
    
    char image_size[4];     // IMAGE SIZE (IF COMPRESSEION == 0 THIS SET TO 0)
    char X_pixels_per_m[4]; // HORIZONTAL RESOLUTION IN PIXELS/METERS
    char Y_pixels_per_m[4]; // VERTICAL RESOLUTION IN PIXELS/METERS
    char colors_used[4];    // NUMBER OF USED COLORS
    char important_colors[4]; // NUMBER OF IMPORTANT COLORS
};


// COLOR TABLE (4 BYTES)
struct colorTable{
    char red, green, blue; // CHANNELS INTESITY
    char reserved;         // UNUSED (0)
};

class bitmap{
public:
    header bmp_head;
    infoHeader info_header;
    char* color_table;
    char *pixel_array;
    
    bitmap();
    ~bitmap();
    
    void readFile(std::string path_file);
    void writeFile(std::string path_file);
    
};

#endif /* bitmap_hpp */
