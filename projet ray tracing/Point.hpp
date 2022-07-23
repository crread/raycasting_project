#ifndef _POINT_HPP_
#define _POINT_HPP_

#include <vector>

class Point {

    std::vector<float> data;

public:

    Point() {
        data = std::vector<float> (4, 0);
        data[3] = 1.f;
    }
    
    Point(const float& x, const float& y, const float& z) {
        data = std::vector<float> (4, 0);
        
        data[0] = x;
        data[1] = y;
        data[2] = z;
        data[3] = 1.f;
    };

    Point(const float& x, const float& y, const float& z, const float& w) {
        data = std::vector<float>(4, 0);

        data[0] = x;
        data[1] = y;
        data[2] = z;
        data[3] = 1.f;
    };

    Point(const Point& point) {
        data = std::vector<float>(4, 0);

        data[0] = point[0];
        data[1] = point[1];
        data[2] = point[2];
        data[3] = 1.f;
    }

    float dot(const Point& point) const;
    float norm() const;
    Point normalized() const;

    float operator[] (const int& idx) const;
    float& operator[] (const int& idx);
    friend std::ostream& operator<<(std::ostream& os, const Point& point);
};

float Point::dot(const Point& point) const {
    return data[0] * point[0] + data[1] * point[1] + data[2] * point[2];
}

float Point::norm() const {
    return sqrt((data[0] * data[0]) + (data[1] * data[1]) + (data[2] * data[2]));
}

Point Point::normalized() const {
    float mag = norm();
    return Point(data[0] / mag, data[1] / mag, data[2] / mag, data[3] / mag);
}

float Point::operator[] (const int& idx) const {
    return data[idx];
}

float& Point::operator[] (const int& idx) {
    return data[idx];
}

std::ostream& operator<<(std::ostream& os, const Point& point) {

    os << "x : " << point[0];
    os << " y : " << point[1];
    os << " z : " << point[2];
    os << " w : " << point[3];

    return os;
}

#endif //_POINT_HPP_