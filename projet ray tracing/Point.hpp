#ifndef _POINT_HPP_
#define _POINT_HPP_

#include <vector>

class Point {

    std::vector<float> data;

public:

    Point() {
        data = std::vector<float> (3, 0);
    }
    
    Point(float x, float y, float z) {
        data = std::vector<float> (3, 0);
        
        data[0] = x;
        data[1] = y;
        data[2] = z;
    };

};

#endif //_POINT_HPP_