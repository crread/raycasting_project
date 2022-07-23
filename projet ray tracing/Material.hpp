#ifndef _MATERIAL_HPP_
#define _MATERIAL_HPP_

struct Color {
	float r;
	float g;
	float b;

	Color() {
		r = 0.5;
		g = 0.5;
		b = 0.5;
	};

	Color(const float& r, const float& g, const float& b): r(r), g(g), b(b) {};
	Color mul(Color& color) const;
	Color operator+(const Color& color);
	Color operator*(const float& value);
	Color operator/(const float& value);
	Color& operator+=(const Color& color);
	float operator[](const int& idx) const;
	friend std::ostream& operator<<(std::ostream& os, const Color& color);
};

Color Color::mul(Color& color) const {
	return Color(r * color.r, g * color.g, b * color.b);
}

Color Color::operator+(const Color& color) {
	return Color(r + color.r, g + color.g, b + color.b);
}

Color Color::operator*(const float& value) {
	return Color(r * value, g * value, b * value);
}

Color Color::operator/(const float& value) {
	return Color(r / value, g / value, b / value);
}

Color& Color::operator+=(const Color& value) {
	auto result = operator+(value);

	r = result.r;
	g = result.g;
	b = result.b;

	return *this;
}

float Color::operator[](const int& idx) const {
	switch (idx)
	{
	case 0:
		return r;
	case 1:
		return g;
	case 2:
		return b;
	default:
		break;
	}
}

std::ostream& operator<<(std::ostream& os, const Color& color) {

	os << "r : " << color[0];
	os << " g : " << color[1];
	os << " b : " << color[2];

	return os;

}

struct Material {
	Color ka;
	Color kd;
	Color ks;
	float shininess;

	Material() {
		ka = Color(1, 1, 1);
		kd = Color(0.8, 0, 0);
		ks = Color(0, 0, 0);
		shininess = 0.8;
	};
};

#endif //_MATERIAL_HPP_