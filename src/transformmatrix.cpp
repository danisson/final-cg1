#include "transformmatrix.h"
#include<cstdio>
#include<cstring>
using namespace tnw;
/*
TransformMatrix::~TransformMatrix()
{
    if(matrix!=nullptr) {
        for (int i = 0; i < 4; ++i) {
            if(matrix[i]!=)
                delete[] matrix[i];
        }
        delete[] matrix;
    }
}
*/
void TransformMatrix::multMatrixE(TransformMatrix* arg)
{
    int acc;
    double temp[4][4];
    for (int i = 0; i < 4; ++i) {
        for (int j = 0; j < 4; ++j) {
            acc = 0;
            for (int k = 0; k < 4; ++k) {
                acc+= arg->matrix[i][k]*matrix[k][j];
            }
            temp[i][j] = acc;
        }
    }
    for (int i = 0; i < 4; ++i) {
        for (int j = 0; j < 4; ++j) {
            this->matrix[i][j]=temp[i][j];
        }
    }
}

TransformMatrix TransformMatrix::operator*(TransformMatrix &m)
{
    TransformMatrix nova;
    nova.multMatrixE(&m);
    return nova;
}

TransformMatrix TransformMatrix::operator=(TransformMatrix m)
{
    TransformMatrix nova;
    int i=0;
    for(i=0;i<=4;i++) {
    memcpy(nova.matrix[i], m.matrix[i], sizeof &(m.matrix[i]));
    }
    return nova;
}

TransformMatrix::TransformMatrix(double a[4][4]) : TransformMatrix::TransformMatrix()
{
    for (int i = 0; i < 4; ++i)
        for (int j = 0; j < 4; ++j)
            this->matrix[i][j] = a[i][j];
}

TransformMatrix::TransformMatrix()
{
    this->matrix = new double*[4];
    for (int i = 0; i < 4; ++i) {
        this->matrix[i] = new double[4];
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
    double x[4][4] = {{4,3,2,1},{4,3,2,1},{4,3,2,1},{4,3,2,1}};
    TransformMatrix* ident = new TransformMatrix();
    TransformMatrix* teste = new TransformMatrix(x);
    TransformMatrix receptor;
    printf("Teste de sanidade: I4x4 * I4x4\n");
    ident->multMatrixE(new TransformMatrix());
    ident->mostrar();
    receptor = (*teste)*(*ident);
   // receptor.mostrar();
  //  receptor = (*teste)*(*teste);
   // receptor.mostrar();
    return 0;
}
