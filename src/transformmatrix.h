#ifndef TRANSFORMMATRIX_H
#define TRANSFORMMATRIX_H

namespace tnw {

    class TransformMatrix
    {
    public:
        double** matrix; //depois colocar como privado pls
        void multMatrixE(TransformMatrix* argumento);
        TransformMatrix operator* (TransformMatrix &m);
        TransformMatrix operator= (TransformMatrix m);
        TransformMatrix(double a[4][4]);
        TransformMatrix();
       // ~TransformMatrix();
        void mostrar();
        void setMatrix(double a[4][4]);
        double** getMatrix();
    };
}
#endif // TRANSFORMMATRIX_H
