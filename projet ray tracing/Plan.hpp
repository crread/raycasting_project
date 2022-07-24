#ifndef _PLANE_HPP_
#define _PLANE_HPP_

struct Plan: public Object {

    Plan() {};

    Point getTextureCoordinates(const Point& p) const;
    Ray getNormal(const Point& p, const Point& o) const;
    bool intersect(const Ray& ray, Point& impact) const;
};

Point Plan::getTextureCoordinates(const Point& p) const {	 		 	  			 		 	  
    auto tmp = globalToLocal(p);	 		 	  			 		 	  
    return Point(tmp[0] - floor(tmp[0]), tmp[1] - floor(tmp[1]), 0.f);	 		 	  			 		 	  
}

Ray Plan::getNormal(const Point& p, const Point& o) const {
    Point lp = globalToLocal(p);
    Point lo = globalToLocal(o);
    float z = 1;
    if (lo[2] < 0)z = -1;
    return localToGlobal(Ray(lp, Vector(0, 0, z))).normalized();
}

bool Plan::intersect(const Ray& ray, Point& impact) const {
    Ray lr = globalToLocal(ray).normalized();
    if (lr.direction[2]<0.0001 && lr.direction[2]>-0.0001)return false;
    if (lr.direction[2] * lr.origin[2] > 0)return false;
    float t = -lr.origin[2] / lr.direction[2];

    impact[0] = lr.origin[0] + t * lr.direction[0];
    impact[1] = lr.origin[1] + t * lr.direction[1];
    impact[2] = lr.origin[2] + t * lr.direction[2];
	 	  			 		 	  
    impact = localToGlobal(impact);
    return true;
}
#endif //_PLANE_HPP_