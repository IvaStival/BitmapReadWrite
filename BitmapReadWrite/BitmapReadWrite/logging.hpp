//
//  logging.hpp
//  BitmapReadWrite
//
//  Created by iva stival on 07/04/22.
//

#ifndef logging_hpp
#define logging_hpp

#include <iostream>
#include <string>

class logging{
private:
    logging();
    
public:
    ~logging();
    
    
    template<class T>
    static void log(T value){
        std::cout << "Log: " << value << std::endl;
    }
};

#endif /* logging_hpp */
