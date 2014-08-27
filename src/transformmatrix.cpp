#include "transformmatrix.h"

TransformMatrix TransformMatrix::multMatrix(TransformMatrix nova)
{
    TransformMatrix retorna = new TransformMatrix;
    int m, n, i = 0;
    for (i=1;i<=4;i++)
        for (n=1;n<=4;n++)
            for (m=1;m<=4;m++)
                this->matrix[i][m] = nova.matrix[m][n]*this->matrix[i][m];
    return retorna;
}

TransformMatrix::TransformMatrix(double a[4][4])
{
    this->matrix = a;
}
