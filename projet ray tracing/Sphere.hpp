#ifndef _SPHERE_HPP_
#define _SPHERE_HPP_

#include <cmath>	 		 	  			 		 	  
	 		 	  			 		 	  
#define PI 3.14159265

class Sphere: public Object {

public :

    Sphere() {};

    Point getTextureCoordinates(const Point& p) const;
    Ray getNormal(const Point& p, const Point& o) const;
    bool intersect(const Ray& ray, Point& impact) const;
    void rendering() const;
}; 
	 		 	  			 		 	  
 Point Sphere::getTextureCoordinates(const Point& p) const {	 		 	  			 		 	  
	 		 	  			 		 	  
     auto tmp = globalToLocal(p);
	 		 	  			 		 	  
    auto phi = atan2(-tmp[1], tmp[0]);	 		 	  			 		 	  
    auto teta = acos(tmp[2]);	 		 	  			 		 	  
    auto X = (phi / (2 * PI)) + 0.5;	 		 	  			 		 	  
    auto Y = teta / PI;	 		 	  			 		 	  
	 		 	  			 		 	  
    return Point(X, Y, 0.f);	 		 	  
}

 Ray Sphere::getNormal(const Point& p, const Point& o) const {
     Point impactLocal = globalToLocal(p);
     Point observatorLocal = globalToLocal(o);

     auto isInside = pow((observatorLocal[0] - 0), 2) + pow((observatorLocal[1] - 0), 2) + pow((observatorLocal[2] - 0), 2) < pow(1, 2);

     if (isInside) {
         Ray r(impactLocal[0], impactLocal[1], impactLocal[2], -impactLocal[0], -impactLocal[1], -impactLocal[2]);
         r = localToGlobal(r);
         r.direction = r.direction.normalized();
         return r;
     }
     else {
         Ray r(impactLocal[0], impactLocal[1], impactLocal[2], impactLocal[0], impactLocal[1], impactLocal[2]);
         r = localToGlobal(r);
         r.direction = r.direction.normalized();
         return r;
     }
 }

 bool Sphere::intersect(const Ray& ray, Point& impact) const {

     if (ray.direction[2] == 0) {
         return false;
     }

     auto v = globalToLocal(ray.direction.normalized());
     auto o = globalToLocal(ray.origin);

     auto c = o[0] * o[0] + o[1] * o[1] + o[2] * o[2] - 1;
     auto b = 2 * (o[0] * v[0] + o[1] * v[1] + o[2] * v[2]);
     auto a = v[0] * v[0] + v[1] * v[1] + v[2] * v[2];

     auto delta = b * b - 4 * a * c;

     if (delta < 0) {
         return false;
     }

     auto t = 0.f;

     if (delta == 0) {
         t = -b / (2 * a);
     }

     if (delta > 0) {
         auto deltaMin = (-b - sqrt(delta)) / (2 * a);
         auto deltaMax = (-b + sqrt(delta)) / (2 * a);

         if (deltaMin < 0 && deltaMax < 0) {
             return false;
         }

         if (deltaMin < deltaMax && deltaMin > 0) {
             t = deltaMin;
         }
         else {
             t = deltaMax;
         }
     }

     auto impactX = o[0] + t * v[0];
     auto impactY = o[1] + t * v[1];
     auto impactZ = o[2] + t * v[2];

     impact[0] = impactX;
     impact[1] = impactY;
     impact[2] = impactZ;

     impact = localToGlobal(impact);

     return true;
 }

 void Sphere::rendering() const {

 }

#endif //_SPHERE_HPP_