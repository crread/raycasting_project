#ifndef _PLANE_HPP_
#define _PLANE_HPP_

class Plan: protected Object {

public:
    Point getTextureCoordinates(const Point& p) const;
    Ray getNormal(const Point& p, const Point& o) const;
    bool intersect(const Ray& ray, Point& impact) const;
    void rendering() const;
};

Point Plan::getTextureCoordinates(const Point& p) const {	 		 	  			 		 	  
    auto tmp = globalToLocal(p);	 		 	  			 		 	  
    return Point(tmp[0] - floor(tmp[0]), tmp[1] - floor(tmp[1]), 0.f);	 		 	  			 		 	  
}

Ray Plan::getNormal(const Point& p, const Point& o) const {
    Point impactLocal = globalToLocal(p);
    Point observatorLocal = globalToLocal(o);

    if (observatorLocal[2] > 0) {
        observatorLocal[2] = 1.f;
    }
    else {
        observatorLocal[2] = -1.f;
    }

    Ray r(impactLocal[0], impactLocal[1], impactLocal[2], 0.f, 0.f, observatorLocal[2]);

    return localToGlobal(r);
}

bool Plan::intersect(const Ray& ray, Point& impact) const {
    if (ray.getDirection()[2] == 0) {
        return false;
    }

    auto v = globalToLocal(ray.getDirection());
    auto o = globalToLocal(ray.getOrigin());

    auto t = -o[2] / v[2];

    if (t < 0) {
        return false;
    }

    impact[0] = o[0] + t * v[0];
    impact[1] = o[1] + t * v[1];
    impact[2] = o[2] + t * v[2];

    impact = localToGlobal(impact);

    return true;
}

void Plan::rendering() const {

}

#endif //_PLANE_HPP_