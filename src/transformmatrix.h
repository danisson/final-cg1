#ifndef TRANSFORMMATRIX_H
#define TRANSFORMMATRIX_H

namespace tnw {

    class TransformMatrix
    {
    public:
        double** matrix; //depois colocar como privado pls
        void multMatrixE(TransformMatrix* argumento);
        TransformMatrix(double a[4][4]);
        TransformMatrix();
        ~TransformMatrix();
        void mostrar();
    };
}
#endif // TRANSFORMMATRIX_H
