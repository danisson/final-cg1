#include "transformmatrix.h"
#include<cstdio>
#include<cstring>
#include<cmath>
#define _USE_MATH_DEFINES
using namespace std;

// Métodos
void tnw::TransformMatrix::mostrar()
{
    printf("┌──────────────────────────────────────────┐\n");
    for (int i = 0; i < 4; ++i) {
        printf("│%0.3le, %0.3le, %0.3le, %0.3le│\n",matrix[i][0],matrix[i][1],matrix[i][2],matrix[i][3]);
    }
    printf("└──────────────────────────────────────────┘\n");
}

// Operadores
tnw::TransformMatrix tnw::TransformMatrix::operator*(const tnw::TransformMatrix& direita)
{
    tnw::TransformMatrix retorno = direita;
    double acc;
    for (int i = 0; i < 4; ++i) {
        for (int j = 0; j < 4; ++j) {
            acc = 0;
            for (int k = 0; k < 4; ++k) {
                acc+= matrix[i][k]*direita(k,j);
            }
            retorno.matrix[i][j] = acc;
        }
    }
    return retorno;
}

tnw::TransformMatrix& tnw::TransformMatrix::operator=(const tnw::TransformMatrix& direita)
{
    for (int i = 0; i < 4; ++i) {
        for (int j = 0; j < 4; ++j) {
            matrix[i][j] = direita.matrix[i][j];
        }
    }
    return *this;
}

double &tnw::TransformMatrix::operator()(unsigned i, unsigned j)
{
    if (i >= 4 || j >= 4)
        throw std::invalid_argument("Indice fora da matrix");
    return matrix[i][j];
}

double tnw::TransformMatrix::operator()(unsigned i, unsigned j) const
{
    if (i >= 4 || j >= 4)
        throw std::invalid_argument("Indice fora da matrix");
    return matrix[i][j];
}

// Construtores
tnw::TransformMatrix::TransformMatrix()
{
    for (int i = 0; i < 4; ++i) {
        this->matrix.resize(4);
        this->matrix[i].resize(4);
        this->matrix[i][i] = 1;
        for (int j = 0; j < 4; ++j)
            if(j!=i)
                this->matrix[i][j] = 0;
    }
}

tnw::TransformMatrix::TransformMatrix(std::initializer_list<std::initializer_list<double> > l)
{
    matrix.resize(4);
    for (unsigned i = 0; i < l.size(); ++i) {
        matrix[i] = std::vector<double>(*(l.begin()+i));
    }

}

tnw::TransformMatrix::TransformMatrix(double a[4][4]) : tnw::TransformMatrix::TransformMatrix()
{
    for (int i = 0; i < 4; ++i)
        for (int j = 0; j < 4; ++j)
            this->matrix[i][j] = a[i][j];
}

tnw::TransformMatrix::TransformMatrix(const tnw::TransformMatrix &obj)
{
    this->matrix = std::vector<std::vector<double>>(obj.matrix);
}

// Destruidor
tnw::TransformMatrix::~TransformMatrix(){}

//Get and Setter

void tnw::TransformMatrix::setMatrix(double a[4][4])
{
    for (int i=0; i<4; ++i){
        for (int j=0; j<4; ++j){
            this->matrix[i][j] = a[i][j];
        }
    }
}

// Operador Matrix * QVector4D
QVector4D tnw::operator*(const TransformMatrix &esquerda, const QVector4D &direita)
{
    QVector4D resultado;
    double acc;
    for (int i = 0; i < 4; ++i) {
        for (int j = 0; j < 4; ++j) {
            acc=0;
            for (int k = 0; k < 4; ++k) {
                acc+= esquerda(i,k)*direita[k];
            }
        }
        resultado[i]=acc;
    }
    return resultado;
}

// Transformações Geométricas
tnw::TransformMatrix tnw::translacao(double x,double y, double z)
{
    tnw::TransformMatrix m = {{1,0,0,x},{0,1,0,y},{0,0,1,z},{0,0,0,1}};
    return m;
}

tnw::TransformMatrix tnw::translacao(QVector3D v)
{
    return tnw::translacao(v[0],v[1],v[2]);
}

tnw::TransformMatrix tnw::escala(double x, double y, double z)
{
    tnw::TransformMatrix m = {{x,0,0,0},{0,y,0,0},{0,0,z,0},{0,0,0,1}};
    return m;
}

tnw::TransformMatrix tnw::rotacaoX(double angGraus)
{
    double angRad = radianos(angGraus);
    tnw::TransformMatrix m = {{1,0,0,0},{0,cos(angRad),-sin(angRad),0},{0,sin(angRad),cos(angRad),0},{0,0,0,1}};
    return m;
}

tnw::TransformMatrix tnw::rotacaoY(double angGraus)
{
    double angRad = tnw::radianos(angGraus);
    tnw::TransformMatrix m = {{cos(angRad),0,-sin(angRad),0},{0,1,0,0},{sin(angRad),0,cos(angRad),0},{0,0,0,1}};
    return m;
}

tnw::TransformMatrix tnw::rotacaoZ(double angGraus)
{
    double angRad = tnw::radianos(angGraus);
    tnw::TransformMatrix m = {{cos(angRad),-sin(angRad),0,0},{sin(angRad),cos(angRad),0,0},{0,0,1,0},{0,0,0,1}};
    return m;
}

tnw::TransformMatrix tnw::rotacaoVetor(double angGraus, QVector3D v)
{
    double angRad  = tnw::radianos(angGraus);
    double seno    = std::sin(angRad);
    double coss    = std::cos(angRad);
    double barCos  = 1 - coss;
    v = v.normalized();
    double x = v[0],y = v[1], z = v[2];
    tnw::TransformMatrix m =
    {
        { coss+x*x*barCos ,x*y*barCos-z*seno,x*z*barCos+y*seno,0},
        {y*x*barCos+z*seno, coss+y*y*barCos ,y*z*barCos-x*seno,0},
        {z*x*barCos-y*seno,z*y*barCos+x*seno, coss+z*z*barCos ,0},
        {       0         ,        0        ,        0        ,1}
    };

    return m;
}

double tnw::radianos(double graus){
    return (M_PI*graus)/180;
}
