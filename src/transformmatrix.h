#ifndef TRANSFORMMATRIX_H
#define TRANSFORMMATRIX_H

class TransformMatrix
{
public:
    double matrix[4][4];
    TransformMatrix multMatrix(TransformMatrix nova);
    TransformMatrix(double a[4][4]);
};

#endif // TRANSFORMMATRIX_H
