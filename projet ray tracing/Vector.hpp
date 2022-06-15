#ifndef _VECTOR_HPP_
#define _VECTOR_HPP_

#include <vector>

class Vector {

    std::vector<float> data;

public:
    
    Vector() {
        data = std::vector<float> (4, 0);
    }
    
    Vector(float x, float y, float z) {
        data = std::vector<float> (4, 0);
        
        data[0] = x;
        data[1] = y;
        data[2] = z;
        data[3] = 0;
    };

};

#endif //_VECTOR_HPP_