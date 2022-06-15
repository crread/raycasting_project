#ifndef _MATRIX_HPP_
#define _MATRIX_HPP_

#include <vector>
#include <Vector.hpp>

template<typename T>
class Matrix {
    std::vector<T> values;

public:

    Matrix() {
        values = std::vector<T> (16, 0);
    };
    
    T& operator() (const int x, const int y);
    T operator() (const int x, const int y) const;
    T operator[] (const int idx) const;
    Matrix<T> operator* (const Matrix<T>& matrix) const;
    Vector operator* (const Vector& vector) const;
    Matrix<T> inverse() const;
};

template<typename T> 
T& Matrix<T>::operator() (const int x, const int y) {
    return &values[y * x + x]; 		 	  			 		 	  
}

template<typename T> 
T Matrix<T>::operator() (const int x, const int y) const {
    return &values[y * x + x];
}

template<typename T> 
T Matrix<T>::operator[] (const int idx) const {
    return values[idx];
}

template<typename T>
Vector Matrix<T>::operator* (const Vector& vector) const {

    return Vector
    (
    
    );
    
}

template<typename T>
Matrix<T> Matrix<T>::operator* (const Matrix<T>& matrix) const {

    Matrix<T> newMatrix;

    T a00 = values[0][0];
    T a01 = values[0][1];
    T a02 = values[0][2];
    T a03 = values[0][3];
    
    T a10 = values[1][0];
    T a11 = values[1][1];
    T a12 = values[1][2];
    T a13 = values[1][3];
    
    T a20 = values[2][0];
    T a21 = values[2][1];
    T a22 = values[2][2];
    T a23 = values[2][3];
    
    T a30 = values[3][0];
    T a31 = values[3][1];
    T a32 = values[3][2];
    T a33 = values[3][3];
    
    T b00 = matrixB[0][0];
    T b01 = matrixB[0][1];
    T b02 = matrixB[0][2];
    T b03 = matrixB[0][3];
    
    T b10 = matrixB[1][0];
    T b11 = matrixB[1][1];
    T b12 = matrixB[1][2];
    T b13 = matrixB[1][3];
    
    T b20 = matrixB[2][0];
    T b21 = matrixB[2][1];
    T b22 = matrixB[2][2];
    T b23 = matrixB[2][3];
    
    T b30 = matrixB[3][0];
    T b31 = matrixB[3][1];
    T b32 = matrixB[3][2];
    T b33 = matrixB[3][3];
    
    newMatrix[0][0] = a00*b00+a10*b01+a20*b02+a30*b03;
    newMatrix[0][1] = a01*b00+a11*b01+a21*b02+a31*b03;
    newMatrix[0][2] = a02*b00+a12*b01+a22*b02+a32*b03;
    newMatrix[0][3] = a03*b00+a13*b01+a23*b02+a33*b03;
    
    newMatrix[1][0] = a00*b10+a10*b11+a20*b12+a30*b13;
    newMatrix[1][1] = a01*b10+a11*b11+a21*b12+a31*b13;
    newMatrix[1][2] = a02*b10+a12*b11+a22*b12+a32*b13;
    newMatrix[1][3] = a03*b10+a13*b11+a23*b12+a33*b13;
    
    newMatrix[2][0] = a00*b20+a10*b21+a20*b22+a30*b23;
    newMatrix[2][1] = a01*b20+a11*b21+a21*b22+a31*b23;
    newMatrix[2][2] = a02*b20+a12*b21+a22*b22+a32*b23;
    newMatrix[2][3] = a03*b20+a13*b21+a23*b22+a33*b23;
    
    newMatrix[3][0] = a00*b30+a10*b31+a20*b32+a30*b33;
    newMatrix[3][1] = a01*b30+a11*b31+a21*b32+a31*b33;
    newMatrix[3][2] = a02*b30+a12*b31+a22*b32+a32*b33;
    newMatrix[3][3] = a03*b30+a13*b31+a23*b32+a33*b33;
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

    det = values[0] * invMatrix[0] + values[1] * invMatrix[4] + values[2] * invMatrix[8] + values[3] * invMatrix[12];

    if (det == 0)
        return false;

    det = 1.0 / det;

    for (i = 0; i < 16; i++)
        invMatrix[i] = invMatrix[i] * det;
        
    return &invMatrix;
};

#endif //_MATRIX_HPP_