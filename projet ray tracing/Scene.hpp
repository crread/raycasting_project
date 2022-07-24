#ifndef _SCENE_HPP_
#define _SCENE_HPP_

#include <vector>

struct Scene {

	std::vector<Object*> objects;
	std::vector<Light*> lights;
	Camera* camera;
	Color backgroundColor;
	Color ambiantColor;
	
	Scene() {
		backgroundColor.r = 0.f;
		backgroundColor.g = 0.f;
		backgroundColor.b = 1.f;

		ambiantColor.r = 0.5f;
		ambiantColor.g = 0.5f;
		ambiantColor.b = 0.5f;

		camera = new Camera();
	}
	
	Color getBackground() const;
	Color getAmbiant() const;
	int nbLights() const;
	const Light* getLight(const int idx) const;
	Color getImpactColor(const Ray& ray, const Object& obj, const Point& impact) const;
};

Color Scene::getBackground() const {
	return backgroundColor;
}

Color Scene::getAmbiant() const {
	return ambiantColor;
}

int Scene::nbLights() const {
	return lights.size();
}

const Light* Scene::getLight(const int idx) const {
	return lights[idx];
}

Color Scene::getImpactColor(const Ray& ray, const Object& obj, const Point& impact) const {
	Material m = obj.getMaterial(impact);
	Ray normal = obj.getNormal(impact, ray.getOrigin());
	Color c = m.ka.mul(getAmbiant());

	for (int l = 0; l < nbLights(); l++) {
		const Light* light = getLight(l);
		Vector lv = light->getVectorToLight(impact);
		float alpha = lv.dot(normal.getDirection());
		if (alpha > 0)
			c += (light->id).mul(m.kd) * alpha;

		Vector rm = (2 * lv.dot(normal.getDirection()) * normal.getDirection()) - lv;

		float beta = -rm.dot(ray.getDirection());
		if (beta > 0)
			c += (light->is).mul(m.ks) * pow(beta, m.shininess);
	}

	return c;
}

#endif //_SCENE_HPP_