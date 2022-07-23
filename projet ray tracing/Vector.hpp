#ifndef _Vector_HPP_
#define _Vector_HPP_

#include <vector>

class Vector {

    std::vector<float> data;

public:
    
    Vector() {
        data = std::vector<float> (4, 0);
    }
    
    Vector(const float& x, const float& y, const float& z, const float& w) {
        data = std::vector<float>(4, 0);

        data[0] = x;
        data[1] = y;
        data[2] = z;
        data[3] = 0.f;
    };

    Vector(const float& x, const float& y, const float& z) {
        data = std::vector<float> (4, 0);
        
        data[0] = x;
        data[1] = y;
        data[2] = z;
        data[3] = 0.f;
    };

    Vector(const Point& point) {
        data = std::vector<float>(4, 0);

        data[0] = point[0];
        data[1] = point[1];
        data[2] = point[2];
        data[3] = 0.f;
    }

    Vector(const Vector& vector) {
        data = std::vector<float>(4, 0);

        data[0] = vector[0];
        data[1] = vector[1];
        data[2] = vector[2];
        data[3] = 0.f;
    }

    float norm() const;
    float dot(const Vector& vector) const;
    Vector normalized() const;
    
    float operator[] (const int& idx) const;
    float& operator[] (const int& idx);

    friend Vector operator+(const Vector& vectorA, const Vector& vectorB);
    friend Vector operator-(const Vector& vectorA, const Vector& vectorB);
    friend Vector operator/(const Vector& vectorA, const Vector& vectorB);
    friend Vector operator*(const Vector& vectorA, const Vector& vectorB);
    
    friend Vector operator+(const Vector& vectorA, const float& value);
    friend Vector operator-(const Vector& vectorA, const float& value);
    friend Vector operator/(const Vector& vectorA, const float& value);
    friend Vector operator*(const Vector& vectorA, const float& value);
    
    friend Vector operator+(const float& value, const Vector& vectorA);
    friend Vector operator-(const float& value, const Vector& vectorA);
    friend Vector operator/(const float& value, const Vector& vectorA);
    friend Vector operator*(const float& value, const Vector& vectorA);

    friend bool operator<(const Vector& vectorA, const Vector& vectorB);

    friend std::ostream& operator<<(std::ostream& os, const Vector& rational);
};

float Vector::norm() const {
    return sqrt((data[0] * data[0]) + (data[1] * data[1]) + (data[2] * data[2]));
}

float Vector::dot(const Vector& vector) const {
    return data[0] * vector[0] + data[1] * vector[1] + data[2] * vector[2];
}

Vector Vector::normalized() const {
    float mag = norm();
    return Vector(data[0] / mag, data[1] / mag, data[2] / mag, 0.f);
}

float Vector::operator[] (const int& idx) const {
    return data[idx];
}

float& Vector::operator[] (const int& idx) {
    return data[idx];
}

Vector operator+(const Vector& vectorA, const Vector& vectorB) {
    return Vector(vectorA[0] + vectorB[0], vectorA[1] + vectorB[1], vectorA[2] + vectorB[2], vectorA[3] + vectorB[3]);
}

Vector operator-(const Vector& vectorA, const Vector& vectorB) {
    return Vector(vectorA[0] - vectorB[0], vectorA[1] - vectorB[1], vectorA[2] - vectorB[2], vectorA[3] - vectorB[3]);
}

Vector operator/(const Vector& vectorA, const Vector& vectorB) {
    return Vector(vectorA[0] / vectorB[0], vectorA[1] / vectorB[1], vectorA[2] / vectorB[2], vectorA[3] / vectorB[3]);
}

Vector operator*(const Vector& vectorA, const Vector& vectorB) {
    return Vector(vectorA[0] * vectorB[0], vectorA[1] * vectorB[1], vectorA[2] * vectorB[2], vectorA[3] * vectorB[3]);
}

Vector operator+(const Vector& vectorA, const float& value) {
    return Vector(vectorA[0] + value, vectorA[1] + value, vectorA[2] + value);
}

Vector operator-(const Vector& vectorA, const float& value) {
    return Vector(vectorA[0] - value, vectorA[1] - value, vectorA[2] - value);
}

Vector operator/(const Vector& vectorA, const float& value) {
    return Vector(vectorA[0] / value, vectorA[1] / value, vectorA[2] / value);
}

Vector operator*(const Vector& vectorA, const float& value) {
    return Vector(vectorA[0] * value, vectorA[1] * value, vectorA[2] * value);
}

Vector operator+(const float& value, const Vector& vectorA) {
    return operator+(vectorA, value);
}

Vector operator-(const float& value, const Vector& vectorA) {
    return operator-(vectorA, value);
}

Vector operator/(const float& value, const Vector& vectorA) {
    return operator/(vectorA, value);
}

Vector operator*(const float& value, const Vector& vectorA) {
    return operator*(vectorA, value);
}

bool operator<(const Vector& vectorA, const Vector& vectorB) {
    return vectorA[0] < vectorB[0] && vectorA[1] < vectorB[1] && vectorA[2] < vectorB[2];
}

std::ostream& operator<<(std::ostream& os, const Vector& vector) {

    os << "x : " << vector[0];
    os << " y : " << vector[1];
    os << " z : " << vector[2];
    os << " w : " << vector[3];

    return os;
}

#endif //_Vector_HPP_