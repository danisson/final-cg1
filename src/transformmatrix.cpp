#include "transformmatrix.h"
#include<cstdio>
#include<cstdlib>
using namespace tnw;

void TransformMatrix::multMatrixE(TransformMatrix* arg)
{
    int acc;
    for (int i = 0; i < 4; ++i) {
        for (int j = 0; j < 4; ++j) {
            acc = 0;
            for (int k = 0; k < 4; ++k) {
                acc+= arg->matrix[i][k]*matrix[k][j];
            }
            matrix[i][j] = acc;
        }
    }
}

TransformMatrix::TransformMatrix(double a[4][4]) : TransformMatrix::TransformMatrix()
{
    for (int i = 0; i < 4; ++i)
        for (int j = 0; j < 4; ++j)
            this->matrix[i][j] = a[i][j];
}

TransformMatrix::TransformMatrix()
{
    this->matrix = (double**)malloc(sizeof(double*)*4);
    for (int i = 0; i < 4; ++i) {
        this->matrix[i] = (double*)malloc(sizeof(double)*4);
        this->matrix[i][i] = 1;
        for (int j = 0; j < 4; ++j)
            if(j!=i)
                this->matrix[i][j] = 0;
    }
}


void TransformMatrix::mostrar()
{
    for (int i = 0; i < 4; ++i) {
        printf("[%lf %lf %lf %lf]\n",this->matrix[i][0],this->matrix[i][1],this->matrix[i][2],this->matrix[i][3]);
    }
}

int main()
{
    TransformMatrix* ident = new TransformMatrix();
    printf("Teste de sanidade: I4x4 * I4x4\n");
    ident->multMatrixE(new TransformMatrix());
    ident->mostrar();
    return 0;
}
