#include "transformmatrix.h"
#include<cstdio>
#include<cstring>
using namespace tnw;

// Métodos
void TransformMatrix::mostrar()
{
    for (int i = 0; i < 4; ++i) {
        printf("[%lf %lf %lf %lf]\n",this->matrix[i][0],this->matrix[i][1],this->matrix[i][2],this->matrix[i][3]);
    }
}

// Operadores
TransformMatrix TransformMatrix::operator*(const TransformMatrix& direita)
{
    TransformMatrix retorno = direita;
    int acc;
    for (int i = 0; i < 4; ++i) {
        for (int j = 0; j < 4; ++j) {
            acc = 0;
            for (int k = 0; k < 4; ++k) {
                acc+= matrix[i][k]*direita.matrix[k][j];
            }
            retorno.matrix[i][j] = acc;
        }
    }
    return retorno;
}

TransformMatrix& TransformMatrix::operator=(const TransformMatrix& direita)
{
    for (int i = 0; i < 4; ++i) {
        for (int j = 0; j < 4; ++j) {
            matrix[i][j] = direita.matrix[i][j];
        }
    }
    return *this;
}

// Construtores
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

TransformMatrix::TransformMatrix(double a[4][4]) : TransformMatrix::TransformMatrix()
{
    for (int i = 0; i < 4; ++i)
        for (int j = 0; j < 4; ++j)
            this->matrix[i][j] = a[i][j];
}

TransformMatrix::TransformMatrix(double** a) : TransformMatrix::TransformMatrix()
{
    for (int i = 0; i < 4; ++i)
        for (int j = 0; j < 4; ++j)
            this->matrix[i][j] = a[i][j];
}

TransformMatrix::TransformMatrix(const TransformMatrix &obj)
{
    this->matrix = new double*[4];
    for (int i = 0; i < 4; ++i) {
        this->matrix[i] = new double[4];
        this->matrix[i][i] = 1;
        for (int j = 0; j < 4; ++j)
            if(j!=i)
                this->matrix[i][j] = 0;
    }
    for (int i = 0; i < 4; ++i) {
        for (int j = 0; j < 4; ++j) {
            matrix[i][j] = obj.matrix[i][j];
        }
    }
}

// Destruidor
TransformMatrix::~TransformMatrix()
{
    if(matrix!=nullptr) {
        for (int i = 0; i < 4; ++i) {
                delete[] matrix[i];
        }
        delete[] matrix;
    }
}

int main()
{
    double x[4][4] = {{4,3,2,1},{4,3,2,1},{4,3,2,1},{4,3,2,1}};
    TransformMatrix ident;
    TransformMatrix teste(x);
    ident= teste * (ident);
    ident.mostrar();
    return 0;
}