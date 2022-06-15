#ifndef _ENTITY_HPP_
#define _ENTITY_HPP_

#include <cmath>

#include "Point.hpp"
#include "HPoint.hpp"
#include "Vector.hpp"
#include "HVector.hpp"
#include "Ray.hpp"
#include "HRay.hpp"
#include "Matrix.hpp"

class Entity {

protected:
    Matrix<float> trans;
    Matrix<float> transInv;

    void rotateX(const float deg);
    void rotateY(const float deg);
    void rotateZ(const float deg);
    Point localToGlobal(const Point& p) const;
    Vector localToGlobal(const Vector& v) const;
    Ray localToGlobal(const Ray& r) const;
};

void Entity::rotateX(const float deg){	 		 	  			 		 	  
    Matrix<float> m;
    m(0,0) = 1;
    m(1,1) =  cos(deg);
    m(1,2) = -sin(deg);
    m(2,1) =  sin(deg);
    m(2,2) =  cos(deg);
    m(3,3) = 1;
	 		 	  			 		 	  
    trans = m * trans;
	 		 	  			 		 	  
    transInv = trans.inverse();
}

void Entity::rotateY(const float deg){	 		 	  			 		 	  
	 		 	  			 		 	  
    Matrix<float> m;	 		 	  			 		 	  
    m(0,0) = cos(deg);
    m(0,2) = sin(deg);
    m(1,1) = 1;
    m(2,0) = -sin(deg);
    m(2,2) = cos(deg);
    m(3,3) = 1;
	 		 	  			 		 	  
    trans = m * trans;	 		 	  			 		 	  
	 		 	  			 		 	  
    transInv = trans.inverse();	 		 	  			 		 	  
}

void Entity::rotateZ(const float deg){	 		 	  			 		 	  
    Matrix<float> m;
    m(0,0) = cos(deg);
    m(0,1) = -sin(deg);
    m(1,0) = sin(deg);
    m(1,1) = cos(deg);
    m(2,2) = 1;
    m(3,3) = 1;

    trans = m * trans;

    transInv = trans.inverse();
}

Point Entity::localToGlobal(const Point& p) const{
	Point hp(p);
	return transInv * hp;
}
	 		 	  			 		 	  
Vector Entity::localToGlobal(const Vector& v) const{	 		 	  			 		 	  
	Vector hv(v);
	return transInv * hv;
}
	 		 	  			 		 	  
Ray Entity::localToGlobal(const Ray& r) const{	 		 	  			 		 	  
  	Ray hr(r);
  	
  	hr.setDirection(localToGlobal(hr.getDirection()));	 		 	  			 		 	  
  	hr.setOrigin(localToGlobal(hr.getOrigin()));

  	return hr;	 		 	  			 		 	  
}

#endif //_ENTITY_HPP_