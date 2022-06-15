#ifndef _RAY_HPP_
#define _RAY_HPP_

#include "Vector.hpp"
#include "Point.hpp"

class Ray {

    Vector direction;
    Point origin;

public:
    
    Ray(float ox, float oy, float oz, float vx, float vy, float vz) {
        origin = Point(ox, oy, oz);
        direction = Vector(vx, vy, vz);
    };
    
    Ray(Point origin, Vector direction): origin(origin), direction(direction) {};

    void setDirection(const Vector& newDirection);
    Vector getDirection() const;
    
    void setOrigin(const Point& newOrigin);
    Point getOrigin() const;

};

void Ray::setDirection(const Vector& newDirection) {
    direction = newDirection;
    return;
}

Vector Ray::getDirection() const {
    return direction;
}

void Ray::setOrigin(const Point& newOrigin) {
    origin = newOrigin;
}

Point Ray::getOrigin() const {
    return origin;
}

#endif //_RAY_HPP_