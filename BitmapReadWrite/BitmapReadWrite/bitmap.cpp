//
//  bitmap.cpp
//  BitmapReadWrite
//
//  Created by iva stival on 07/04/22.
//

#include "bitmap.hpp"

#include <stdio.h>
#include "math.h"
#include <iostream>
#include <vector>
#include <fstream>

bitmap::bitmap(){
    this->color_table = new char;
    this->pixel_array = new char;
}

bitmap::~bitmap(){
    delete this->color_table;
    delete this->pixel_array;
}

void bitmap::readFile(std::string path_file){
    
    std::fstream file;

    file.open(path_file.c_str(), std::fstream::in | std::fstream::binary);
    
    if(!file.is_open()) {
        logging::log <std::string> ("Error! File is Not Open!");
        return;
    }
    
    // GET BITMAP HEADER
    size_t header_size = sizeof(this->bmp_head);
    file.read((char*)&this->bmp_head, header_size);
    
    // GET BITMAP INFOHEADER
    size_t info_size = sizeof(this->info_header);
    file.read((char*)&this->info_header, info_size);
    

    // GET COLOR TABLE IF THE NUMBER OF BITS PER PIXEL IS LESS THAN 8
    int bits_pixel = (*(int*)this->info_header.bits_pixel);
    
    if(bits_pixel <= 8){
        // NUMBER OF COLORS BY CHANNEL
        int number_of_colors = pow(2,bits_pixel);
        
        size_t color_size = 4*number_of_colors;
        this->color_table = new char[color_size];
        
        // READ THE COLOR TABLE
        file.read(this->color_table, color_size);
    }

    // GET IMAGE
    // DATA OFFSET IS OFFSET OF THE IMAGE INIT
    int data_offset = *(int*)this->bmp_head.data_offset;

    // IMAGE DIMENSIONS
    int width = *(int*)this->info_header.width;
    int heigth = *(int*)this->info_header.height;

    // TRANSFORM BITS PER PIXEL TO BYTES PER PIXEL
    int bytes_pixel_unit = (*(int*)this->info_header.bits_pixel) / 8.0f; // GET THE BYTES BY PIXEL
    
    // THE ROW SIZE WITH PADDING, THIS IS BECAUSE THE BMP USE A PADDING TO MAKE THE FILE DIVIBLE FOR 4
    //    int32_t padding_row_size = (int) (4 * ceil(((float)width / 4.0f)* bytes_pixel_unit)) ; // OLD STILE
    int padding = (4 - (width % 4)) % 4;
    int32_t padding_row_size = (padding + width) * bytes_pixel_unit;
    
    // UNPPADED ROW SIZE
    int32_t unpadding_row_size = ceil((int)width * bytes_pixel_unit);
    
//    logging::log <int> (width);
    
    // PIXEL VECTOR ARRAY
    this->pixel_array = new char[unpadding_row_size*heigth];
    
    // POINTER TO PIXEL ARRAY, WE MOVE THEN TO THE FINAL SPACE ROW, BECAUSE THE BMP STORE THE PIXELS IN THE BOTTON - TOP MODE
    char *pointer_count = this->pixel_array;

    // INIT WITH THE FIRST PIXEL OF THE FILE LINE AND SAVE ON THE LAST ARRAY LINE POSITION, AND CONTINUE THIS PROCESS UNTIL FINISH.
    // WHEN FINISHED WE HAVE THE PIXEL IN THE TOP - BOTTON MODE.

    for(int i = 0; i < heigth; ++i){
        file.seekg(data_offset+(i*padding_row_size), std::ifstream::beg);
        file.read(pointer_count, unpadding_row_size);
        pointer_count += unpadding_row_size;
    }

    file.close();
}

void bitmap::writeFile(std::string path_file){
    
    std::fstream file;
    
    file.open(path_file, std::fstream::out | std::fstream::binary);
    
    file.write((char*)&this->bmp_head, sizeof(bmp_head));

    file.write((char*)&this->info_header, sizeof(info_header));

    int bits_pixel = (*(int*)this->info_header.bits_pixel);
    
    
    if(bits_pixel <= 8){
        // THE COLOR TABLE SIZE IS EQUAL TO 2 ^ BITS PER PIXEL TIMES 4
        
        int color_by_channel = pow(2,bits_pixel);
        size_t color_size = 4*color_by_channel;
        
        file.write(this->color_table, color_size);
//        file.seekg(color_size);
    }
    
    int data_offset = *(int*)this->bmp_head.data_offset;
    
    // IMAGE DIMENSIONS
    int width = *(int*)this->info_header.width;
    int heigth = *(int*)this->info_header.height;
    float bytes_pixel_unit = (*(int*)this->info_header.bits_pixel) / 8.0f; // GET THE BYTES BY PIXEL
    
//    int32_t padding_row_size = (int) (4 * ceil(((float)width / 4.0f)* bytes_pixel_unit)) ;
    int padding = (4 - (width % 4)) % 4;
    int32_t padding_row_size = (padding + width) * bytes_pixel_unit;
    
    int32_t unpadding_row_size = ceil((int)width * bytes_pixel_unit);
    
    for(int i = 0; i<heigth; ++i){
        file.seekg(data_offset+(i*padding_row_size), std::ifstream::beg);
        file.write(&this->pixel_array[unpadding_row_size*i], padding_row_size);
    }
//    file.seekg(data_offset+(heigth*padding_row_size));
//    file.write((char*)"\0", 2);
//    file.close();
    
}
