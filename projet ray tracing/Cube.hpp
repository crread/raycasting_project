#ifndef _CUBE_HPP_
#define _CUBE_HPP_

struct Cube: public Object {
    Cube() {};

    Point getTextureCoordinates(const Point& p) const;
    Ray getNormal(const Point& p, const Point& o) const;
    bool intersect(const Ray& ray, Point& impact) const;
    float interSide(const Ray& r, int dim, float offset) const;
};

Point Cube::getTextureCoordinates(const Point& p) const {
	 		 	  			 		 	  
    auto tmp = globalToLocal(p);

    if ((tmp[0] + 1 >= -0.000001f && tmp[0] + 1 <= 0.000001f) || (tmp[0] - 1 <= 0.000001f && tmp[0] - 1 >= -0.000001f)) {	 		 	  			 		 	  
        return Point((tmp[2] / 2) + 0.5, (tmp[1] / 2) + 0.5, 0.f);
    }
    if ((tmp[1] + 1 >= -0.000001f && tmp[1] + 1 <= 0.000001f) || (tmp[1] - 1 <= 0.000001f && tmp[1] - 1 >= -0.000001f)) {	 		 	  			 		 	  
        return Point((tmp[0] / 2) + 0.5, (tmp[2] / 2) + 0.5, 0.f);	 		 	  			 		 	  
    }
    if ((tmp[2] + 1 >= -0.000001f && tmp[2] + 1 <= 0.000001f) || (tmp[2] - 1 <= 0.000001f && tmp[2] - 1 >= -0.000001f)) {	 		 	  			 		 	  
        return Point((tmp[0] / 2) + 0.5, (tmp[1] / 2) + 0.5, 0.f);	 		 	  			 		 	  
    }
}

float Cube::interSide(const Ray& r, int dim, float offset) const {
    float t = -1;
    if (r.direction[dim]<0.00001 && r.direction[dim]>-0.00001)return -1;
    t = (offset - r.origin[dim]) / r.direction[dim];
    if (t < 0)return -1;
    for (int d = 0; d < 3; d++) {
        if (d == dim)continue;
        float x = r.origin[d] + t * r.direction[d];
        if (x < -1 || x > 1)return -1;
    }
    return t;
}

bool Cube::intersect(const Ray& ray, Point& impact) const {
    Ray r = globalToLocal(ray).normalized();

    float mint = -1;
    float offsets[] = { -1,1 };
    for (int d = 0; d < 3; d++) {
        for (int o = 0; o < 2; o++) {
            float t = interSide(r, d, offsets[o]);
            if (t >= 0 && (mint<0 || mint>t)) {
                mint = t;
            }
        }
    }

    if (mint >= 0) {
        impact[0] = r.origin[0] + mint * r.direction[0];
        impact[1] = r.origin[1] + mint * r.direction[1];
        impact[2] = r.origin[2] + mint * r.direction[2];

        impact = localToGlobal(impact);
        return true;
    }

    return false;
}

Ray Cube::getNormal(const Point& p, const Point& o) const {
    Point lp = globalToLocal(p);
    Point lo = globalToLocal(o);
    Vector v(0, 0, 0);
    if (lp[0] > 0.999)v[0] = 1.0;
    else if (lp[0] < -0.999)v[0] = -1.0;
    else if (lp[1] > 0.999)v[1] = 1.0;
    else if (lp[1] < -0.999)v[1] = -1.0;
    else if (lp[2] > 0.999)v[2] = 1.0;
    else if (lp[2] < -0.999)v[2] = -1.0;
    if (lo[0]<1 && lo[0]>-1 && lo[1]<1 && lo[1]>-1 && lo[2]<1 && lo[2]>-1)
        return localToGlobal(Ray(lp, -1 * v)).normalized();
    return localToGlobal(Ray(lp, v)).normalized();
}

#endif //_CUBE_HPP_