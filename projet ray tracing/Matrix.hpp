#ifndef _MATRIX_HPP_
#define _MATRIX_HPP_

#include <vector>

#include "Vector.hpp"

template<typename T>
class Matrix {
    std::vector<T> values;

public:
    Matrix() {
        values      = std::vector<T> (16, 0);
        values[0] = 1.f;
        values[5] = 1.f;
        values[10] = 1.f;
        values[15] = 1.f;
    };
    
    T& operator() (const int x, const int y);
    T operator() (const int x, const int y) const;
    T operator[] (const int idx) const;
    T& operator[] (const int idx);
    Vector operator* (const Vector& vector) const;
    Point operator* (const Point& point) const;
    Matrix<T> operator* (const Matrix<T>& matrix) const;
    friend Vector operator* (const Vector& vector, const Matrix<T>& matrix);
    friend Point operator* (const Point& point, const Matrix<T>& matrix);
    Matrix<T> inverse() const;
};

template<typename T>
Vector Matrix<T>::operator* (const Vector& vector) const {
    return Vector
    (
        values[0] * vector[0] + values[1] * vector[1] + values[2] * vector[2] + values[3] * vector[3],
        values[4] * vector[0] + values[5] * vector[1] + values[6] * vector[2] + values[7] * vector[3],
        values[8] * vector[0] + values[9] * vector[1] + values[10] * vector[2] + values[11] * vector[3],
        0.f
    );
}

template<typename T>
Point Matrix<T>::operator* (const Point& point) const {
    return Point
    (
        values[0] * point[0] + values[1] * point[1] + values[2] * point[2] + values[3] * point[3],
        values[4] * point[0] + values[5] * point[1] + values[6] * point[2] + values[7] * point[3],
        values[8] * point[0] + values[9] * point[1] + values[10] * point[2] + values[11] * point[3],
        1.f
    );
}

template<typename T>
Vector operator* (const Vector& vector, const Matrix<T>& matrix) {
    return matrix * vector;
}

template<typename T>
Point operator* (const Point& point, const Matrix<T>& matrix) {
    return matrix * point;
}

template<typename T> 
T& Matrix<T>::operator() (const int x, const int y) {
    return values[x * 4 + y];	 	  			 		 	  
}

template<typename T> 
T Matrix<T>::operator() (const int x, const int y) const {
    return values[x * 4 + y];
}

template<typename T> 
T Matrix<T>::operator[] (const int idx) const {
    return values[idx];
}

template<typename T>
T& Matrix<T>::operator[] (const int idx) {
    return values[idx];
}

template<typename T>
Matrix<T> Matrix<T>::operator* (const Matrix<T>& matrix) const {

    Matrix<T> newMatrix;

    T a00 = values[0];
    T a01 = values[1];
    T a02 = values[2];
    T a03 = values[3];
    
    T a10 = values[4];
    T a11 = values[5];
    T a12 = values[6];
    T a13 = values[7];
    
    T a20 = values[8];
    T a21 = values[9];
    T a22 = values[10];
    T a23 = values[11];
    
    T a30 = values[12];
    T a31 = values[13];
    T a32 = values[14];
    T a33 = values[15];
    
    T b00 = matrix[0];
    T b01 = matrix[1];
    T b02 = matrix[2];
    T b03 = matrix[3];
    
    T b10 = matrix[4];
    T b11 = matrix[5];
    T b12 = matrix[6];
    T b13 = matrix[7];
    
    T b20 = matrix[8];
    T b21 = matrix[9];
    T b22 = matrix[10];
    T b23 = matrix[11];
    
    T b30 = matrix[12];
    T b31 = matrix[13];
    T b32 = matrix[14];
    T b33 = matrix[15];
    
    newMatrix[0] = a00*b00+a10*b01+a20*b02+a30*b03;
    newMatrix[1] = a01*b00+a11*b01+a21*b02+a31*b03;
    newMatrix[2] = a02*b00+a12*b01+a22*b02+a32*b03;
    newMatrix[3] = a03*b00+a13*b01+a23*b02+a33*b03;
    
    newMatrix[4] = a00*b10+a10*b11+a20*b12+a30*b13;
    newMatrix[5] = a01*b10+a11*b11+a21*b12+a31*b13;
    newMatrix[6] = a02*b10+a12*b11+a22*b12+a32*b13;
    newMatrix[7] = a03*b10+a13*b11+a23*b12+a33*b13;
    
    newMatrix[8] = a00*b20+a10*b21+a20*b22+a30*b23;
    newMatrix[9] = a01*b20+a11*b21+a21*b22+a31*b23;
    newMatrix[10] = a02*b20+a12*b21+a22*b22+a32*b23;
    newMatrix[11] = a03*b20+a13*b21+a23*b22+a33*b23;
    
    newMatrix[12] = a00*b30+a10*b31+a20*b32+a30*b33;
    newMatrix[13] = a01*b30+a11*b31+a21*b32+a31*b33;
    newMatrix[14] = a02*b30+a12*b31+a22*b32+a32*b33;
    newMatrix[15] = a03*b30+a13*b31+a23*b32+a33*b33;
    
    return newMatrix;
}

template<typename T> 
Matrix<T> Matrix<T>::inverse() const {

    Matrix<T> invMatrix;

    invMatrix[0] =  values[5]  * values[10] * values[15] - 
                    values[5]  * values[11] * values[14] - 
                    values[9]  * values[6]  * values[15] + 
                    values[9]  * values[7]  * values[14] +
                    values[13] * values[6]  * values[11] - 
                    values[13] * values[7]  * values[10];

    invMatrix[4] =  -values[4]  * values[10] * values[15] + 
                    values[4]  * values[11] * values[14] + 
                    values[8]  * values[6]  * values[15] - 
                    values[8]  * values[7]  * values[14] - 
                    values[12] * values[6]  * values[11] + 
                    values[12] * values[7]  * values[10];

    invMatrix[8] =  values[4]  * values[9] * values[15] - 
                    values[4]  * values[11] * values[13] - 
                    values[8]  * values[5] * values[15] + 
                    values[8]  * values[7] * values[13] + 
                    values[12] * values[5] * values[11] - 
                    values[12] * values[7] * values[9];

    invMatrix[12] = -values[4]  * values[9] * values[14] + 
                    values[4]  * values[10] * values[13] +
                    values[8]  * values[5] * values[14] - 
                    values[8]  * values[6] * values[13] - 
                    values[12] * values[5] * values[10] + 
                    values[12] * values[6] * values[9];

    invMatrix[1] =  -values[1]  * values[10] * values[15] + 
                    values[1]  * values[11] * values[14] + 
                    values[9]  * values[2] * values[15] - 
                    values[9]  * values[3] * values[14] - 
                    values[13] * values[2] * values[11] + 
                    values[13] * values[3] * values[10];

    invMatrix[5] =  values[0]  * values[10] * values[15] - 
                    values[0]  * values[11] * values[14] - 
                    values[8]  * values[2] * values[15] + 
                    values[8]  * values[3] * values[14] + 
                    values[12] * values[2] * values[11] - 
                    values[12] * values[3] * values[10];

    invMatrix[9] =  -values[0]  * values[9] * values[15] + 
                    values[0]  * values[11] * values[13] + 
                    values[8]  * values[1] * values[15] - 
                    values[8]  * values[3] * values[13] - 
                    values[12] * values[1] * values[11] + 
                    values[12] * values[3] * values[9];

    invMatrix[13] = values[0]  * values[9] * values[14] - 
                    values[0]  * values[10] * values[13] - 
                    values[8]  * values[1] * values[14] + 
                    values[8]  * values[2] * values[13] + 
                    values[12] * values[1] * values[10] - 
                    values[12] * values[2] * values[9];

    invMatrix[2] =  values[1]  * values[6] * values[15] - 
                    values[1]  * values[7] * values[14] - 
                    values[5]  * values[2] * values[15] + 
                    values[5]  * values[3] * values[14] + 
                    values[13] * values[2] * values[7] - 
                    values[13] * values[3] * values[6];

    invMatrix[6] =  -values[0]  * values[6] * values[15] + 
                    values[0]  * values[7] * values[14] + 
                    values[4]  * values[2] * values[15] - 
                    values[4]  * values[3] * values[14] - 
                    values[12] * values[2] * values[7] + 
                    values[12] * values[3] * values[6];

    invMatrix[10] = values[0]  * values[5] * values[15] - 
                    values[0]  * values[7] * values[13] - 
                    values[4]  * values[1] * values[15] + 
                    values[4]  * values[3] * values[13] + 
                    values[12] * values[1] * values[7] - 
                    values[12] * values[3] * values[5];

    invMatrix[14] = -values[0]  * values[5] * values[14] + 
                    values[0]  * values[6] * values[13] + 
                    values[4]  * values[1] * values[14] - 
                    values[4]  * values[2] * values[13] - 
                    values[12] * values[1] * values[6] + 
                    values[12] * values[2] * values[5];

    invMatrix[3] =  -values[1] * values[6] * values[11] + 
                    values[1] * values[7] * values[10] + 
                    values[5] * values[2] * values[11] - 
                    values[5] * values[3] * values[10] - 
                    values[9] * values[2] * values[7] + 
                    values[9] * values[3] * values[6];

    invMatrix[7] =  values[0] * values[6] * values[11] - 
                    values[0] * values[7] * values[10] - 
                    values[4] * values[2] * values[11] + 
                    values[4] * values[3] * values[10] + 
                    values[8] * values[2] * values[7] - 
                    values[8] * values[3] * values[6];

    invMatrix[11] = -values[0] * values[5] * values[11] + 
                    values[0] * values[7] * values[9] + 
                    values[4] * values[1] * values[11] - 
                    values[4] * values[3] * values[9] - 
                    values[8] * values[1] * values[7] + 
                    values[8] * values[3] * values[5];

    invMatrix[15] = values[0] * values[5] * values[10] - 
                    values[0] * values[6] * values[9] - 
                    values[4] * values[1] * values[10] + 
                    values[4] * values[2] * values[9] + 
                    values[8] * values[1] * values[6] - 
                    values[8] * values[2] * values[5];

    float det = values[0] * invMatrix[0] + values[1] * invMatrix[4] + values[2] * invMatrix[8] + values[3] * invMatrix[12];

    det = 1.0 / det;

    for (int i = 0; i < 16; i++)
        invMatrix[i] = invMatrix[i] * det;

    return invMatrix;
};

#endif //_MATRIX_HPP_