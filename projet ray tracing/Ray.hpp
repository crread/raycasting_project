#ifndef _RAY_HPP_
#define _RAY_HPP_

struct Ray {

    Vector direction;
    Point origin;
    
    Ray(const float& ox,const float& oy,const float& oz,const float& vx,const float& vy,const float& vz) {
        origin = Point(ox, oy, oz);
        direction = Vector(vx, vy, vz);
    };
    
    Ray(const Point& origin,const Vector& direction): origin(origin), direction(direction) {};

    Ray normalized() const;

    void setDirection(const Vector& newDirection);
    Vector getDirection() const;
    
    void setOrigin(const Point& newOrigin);
    Point getOrigin() const;

    friend std::ostream& operator<<(std::ostream& os, const Ray& ray);
};

void Ray::setDirection(const Vector& newDirection) {
    direction = newDirection;
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

Ray Ray::normalized() const {
    return Ray(origin, direction.normalized());
}

std::ostream& operator<<(std::ostream& os, const Ray& ray) {

    os << " origin " << std::endl;
    os << ray.getOrigin();
    os << " direction " << std::endl;
    os << ray.getDirection();

    return os;
}

#endif //_RAY_HPP_