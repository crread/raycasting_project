#ifndef _CAMERA_HPP_
#define _CAMERA_HPP_

#include <math.h> 

struct Camera : public Entity {

    float focal;

    Camera() {
        focal = 0.f;
        transInv = trans.inverse();
    };

    Camera(const float& focal) {
        this->focal = focal;
    }
    
    Ray getRay(const float& x,const float& y, const float& alpha) const;
    bool nearest(const Object& oldObject, const Object& newObject) const;
};

Ray Camera::getRay(const float& x,const float& y, const float& alpha) const {
    Ray r(- 1 + 2 * x, 1 - 2 * y, 0, 0, 0, 0);
    Point foc(0, 0, -focal);
    r.direction = (r.origin - foc);
    r = localToGlobal(r);
    return r.normalized();
}

bool Camera::nearest(const Object& oldObject, const Object& newObject) const {
    return oldObject.getPosition().norm() < newObject.getPosition().norm();
}

#endif //_CAMERA_HPP_