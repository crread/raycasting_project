#ifndef _OBJECT_HPP_
#define _OBJECT_HPP_

#include <string>

struct Object : public Entity {

    Material material;
    Color color;

    Material getMaterial(const Point& p) const;
    Vector getPosition() const;
    virtual Ray getNormal(const Point& p, const Point& o) const;
    virtual bool intersect(const Ray& ray, Point& impact) const;
    virtual void rendering() const;
};

Material Object::getMaterial(const Point& p) const {
    return material;
}

Vector Object::getPosition() const {
    return Vector(trans[3], trans[7], trans[11]);
}

Ray Object::getNormal(const Point& p, const Point& o) const {
    return Ray(0.f, 0.f, 0.f, 0.f, 0.f, 0.f);
}

bool Object::intersect(const Ray& ray, Point& impact) const {
    return false;
}

void Object::rendering() const {}

#endif //_OBJECT_HPP_