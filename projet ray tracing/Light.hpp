#ifndef _LIGHT_HPP_
#define _LIGHT_HPP_

struct Light : public Entity {

    Color id;
    Color is;

    Light(const Color& id, const Color& is) : id(id), is(is) {};
    //Ray getRayToLight(const Point& p) const;
    //Ray getRayFromLight(const Point& p) const;
    Vector getVectorToLight(const Point& p) const;
    Vector getVectorFromLight(const Point& p) const;
};

//Ray Light::getRayToLight(const Point& p) const {
//    return Ray(p, Vector(trans[0], trans[5], trans[10]));
//}
//
//Ray Light::getRayFromLight(const Point& p) const {
//    return Ray(Point(trans[0], trans[5], trans[10], trans[15]), Vector(p));
//}

Vector Light::getVectorToLight(const Point& p) const {
    return Vector(trans[3] - p[0], trans[7] - p[1], trans[11] - p[2]).normalized();
}

Vector Light::getVectorFromLight(const Point& p) const {
    return Vector(p[0] - trans[3], p[1] - trans[7], p[2] - trans[11]).normalized();
}

#endif //_LIGHT_HPP_