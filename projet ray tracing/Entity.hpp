#ifndef _ENTITY_HPP_
#define _ENTITY_HPP_

#include <cmath>
#include "Matrix.hpp"
#include "Vector.hpp"
#include "Point.hpp"
#include "Ray.hpp"

constexpr auto PI = 3.14159265359;

class Entity {

protected:
    Matrix<float> trans;
    Matrix<float> transInv;
public:
    Entity() {
        transInv = trans.inverse();
    };

    void translation(const float& x,const float& y, const float& z);
    void scale(const float& scale);
    void rotateX(const float& deg);
    void rotateY(const float& deg);
    void rotateZ(const float& deg);
    Point localToGlobal(const Point& p) const;
    Vector localToGlobal(const Vector& v) const;
    Ray localToGlobal(const Ray& r) const;

    Point globalToLocal(const Point& p) const;
    Vector globalToLocal(const Vector& v) const;
    Ray globalToLocal(const Ray& r) const;
    void getTransform() const;
    void getTransformInverse() const;
};

void Entity::translation(const float& x,const float& y, const float& z) {
    Matrix<float> m;
    m(0, 3) = x;
    m(1, 3) = y;
    m(2, 3) = z;
    trans = m * trans;
    transInv = trans.inverse();
}

void Entity::scale(const float& scale) {
    Matrix<float> m;
    m(0, 0) = scale;
    m(1, 1) = scale;
    m(2, 2) = scale;
    trans = m * trans;
    transInv = trans.inverse();
    trans.getMatrix();
    transInv.getMatrix();
}

void Entity::rotateX(const float& deg){
    float radian = deg * PI / 180;
    Matrix<float> m;
    float c = cos(radian);
    float s = sin(radian);
    m(1, 1) = c;
    m(1, 2) = -s;
    m(2, 1) = s;
    m(2, 2) = c;
    trans = m * trans;
    transInv = trans.inverse();
}

void Entity::rotateY(const float& deg){
    float radian = deg * PI / 180;
    Matrix<float> m;
    float c = cos(radian);
    float s = sin(radian);
    m(0, 0) = c;
    m(0, 2) = s;
    m(2, 0) = -s;
    m(2, 2) = c;
    trans = m * trans;
    transInv = trans.inverse();
}

void Entity::rotateZ(const float& deg){
    float radian = deg * PI / 180;
    Matrix<float> m;
    float c = cos(radian);
    float s = sin(radian);
    m(0, 0) = c;
    m(0, 1) = -s;
    m(1, 0) = s;
    m(1, 1) = c;
    trans = m * trans;
    transInv = trans.inverse();
}

Point Entity::localToGlobal(const Point& p) const{
    return trans * p;
}

Vector Entity::localToGlobal(const Vector& v) const{
    return trans * v;
}
	 		 	  			 		 	  
Ray Entity::localToGlobal(const Ray& r) const{	 		 	  			 		 	  
  	Ray hr(r);
  	
  	hr.setDirection(localToGlobal(hr.getDirection()));
  	hr.setOrigin(localToGlobal(hr.getOrigin()));

  	return hr;
}

Point Entity::globalToLocal(const Point& p) const {
    return transInv * p;
}

Vector Entity::globalToLocal(const Vector& v) const {
    return transInv * v;
}

Ray Entity::globalToLocal(const Ray& r) const {
    Ray hr(r);

    hr.setDirection(globalToLocal(hr.getDirection()));
    hr.setOrigin(globalToLocal(hr.getOrigin()));

    return hr;
}

void Entity::getTransform() const {
    std::cout << trans(0, 0) << " " << trans(0, 1) << " " << trans(0, 2) << " " << trans(0, 3) << std::endl;
    std::cout << trans(1, 0) << " " << trans(1, 1) << " " << trans(1, 2) << " " << trans(1, 3) << std::endl;
    std::cout << trans(2, 0) << " " << trans(2, 1) << " " << trans(2, 2) << " " << trans(2, 3) << std::endl;
    std::cout << trans(3, 0) << " " << trans(3, 1) << " " << trans(3, 2) << " " << trans(3, 3) << std::endl;
};

void Entity::getTransformInverse() const {
    std::cout << transInv(0, 0) << " " << transInv(0, 1) << " " << transInv(0, 2) << " " << transInv(0, 3) << std::endl;
    std::cout << transInv(1, 0) << " " << transInv(1, 1) << " " << transInv(1, 2) << " " << transInv(1, 3) << std::endl;
    std::cout << transInv(2, 0) << " " << transInv(2, 1) << " " << transInv(2, 2) << " " << transInv(2, 3) << std::endl;
    std::cout << transInv(3, 0) << " " << transInv(3, 1) << " " << transInv(3, 2) << " " << transInv(3, 3) << std::endl;
};

#endif //_ENTITY_HPP_