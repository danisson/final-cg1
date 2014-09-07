#include "transformmatrix.h"
#include<cstdio>
#include<cstring>
#include<cmath>
#define _USE_MATH_DEFINES
using namespace tnw;
using namespace std;

// Métodos
void TransformMatrix::mostrar()
{
    printf("┌──────────────────────────────────────────┐\n");
    for (int i = 0; i < 4; ++i) {
        printf("│%0.3le, %0.3le, %0.3le, %0.3le│\n",matrix[i][0],matrix[i][1],matrix[i][2],matrix[i][3]);
    }
    printf("└──────────────────────────────────────────┘\n");
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

//Get and Setter

void TransformMatrix::setMatrix(double a[4][4])
{
    if (matrix==nullptr){
        this->matrix = new double*[4];
        for (int i=0; i<4; ++i){
            this->matrix[i] = new double[4];
        }
    }
    for (int i=0; i<4; ++i){
        for (int j=0; j<4; ++j){
            this->matrix[i][j] = a[i][j];
        }
    }
}

void TransformMatrix::setMatrix(int i,int j,double a)
{
    this->matrix[i][j] = a;
}

double** TransformMatrix::getMatrix()
{
    return this->matrix;
}

double TransformMatrix::getMatrix(int i, int j)
{
    return matrix[i][j];
}

double radianos(double graus){
    return (M_PI*graus)/180;
}

TransformMatrix translacao(double a[3])
{
    double m[4][4] = {{1,0,0,a[0]},{0,1,0,a[1]},{0,0,1,a[2]},{0,0,0,1}};
    return new TransformMatrix(m);
}

TransformMatrix escala(double a[3])
{
    double m[4][4] = {{a[0],0,0,0},{0,a[1],0,0},{0,0,a[2],0},{0,0,0,1}};
    return new TransformMatrix(m);
}

TransformMatrix rotacaoX(double angGraus)
{
    angRad = radianos(angGraus);
    double m[4][4] = {{1,0,0,0},{0,cos(angRad),-sin(angRad),0},{0,sin(angRad),cos(angRad),0},{0,0,0,1}};
    return new TransformMatrix(m);
}

TransformMatrix rotacaoY(double angGraus)
{
    angRad = radianos(angGraus);
    double m[4][4] = {{cos(angRad),0,sin(angRad),1},{0,1,0,0},{-sin(angRad),0,cos(angRad),0},{0,0,0,1}};
    return new TransformMatrix(m);
}

TransformMatrix rotacaoZ(double angGraus)
{
    angRad = radianos(angGraus);
    double m[4][4] = {{cos(angRad),-sin(angRad),0,0},{sin(angRad),cos(angRad),0,0},{0,0,1,0},{0,0,0,1}};
    return new TransformMatrix(m);
}

TransformMatrix rotacaoVetor(double angGraus, double p1[3], double p2[3])
{
    //Encontra o vetor formado por esses dois pontos!
    double x = p2[0]-p1[0];
    double y = p2[1]-p1[1];
    double z = p2[2]-p1[2];

    //Tamanho do vetor
    double tamanho = sqrt(x*x+y*y+z*z);

    //Finalmente, transforma as coordenadas para um vetor unitário
    double a = x/tamanho;
    double b = y/tamanho;
    double c = z/tamanho;

    //Passo 1: Levar um dos pontos para a origem
    //TransformMatrix MRot1 = new TransformMatrix();
    TransformMatrix MRot1 = translacao({-p1[0],-p1[1],-p1[2]});

    //Passo 2: Levar o vetor de rotação para o plano xz
    double d = sqrt(b*b+c*c); //Comprimento da projeção do vetor no plano yz

    /*double cosAngRotX = c/d;
    double angRotX = acos(cosAngRotX);
    angRotX = (angRotX*180)/M_PI
    Podia definir a matriz em termos do ângulo de rotação ou direto?*/

    //TransformMatrix MRot2 = new TransformMatrix();
    double a[4][4] = {{1,0,0,0},{0,c/d,-b/d,0},{0,b/d,c/d,0},{0,0,0,1}};
    TransformMatrix MRot2 = MRot2.setMatrix(a);
    //Ou MRot2 = rotacaoX(angRotX);

   //Passo 3: Rotacionar em relação ao eixo y para levar o vetor de rotação ao eixo z
    TransformMatrix MRot3 = new TransformMatrix();
    a = {{d,0,0,-a},{0,1,0,0},{a,0,d,0},{0,0,0,1}};
    MRot3 = MRot3.setMatrix(a);

    //Passo 4:Rotacionar em torno de z pelo ângulo dado
    TransformMatrix MRot4 = new TransformMatrix();
    MRot4 = rotacaoZ(angGraus);

    //Passos 5,6,7: Inverter as transformações aplicadas!

    //Passo 5: Inverter a rotação em y
    TransformMatrix MRot5 = new TransformMatrix();
    MRot5 = MRot5.setMatrix({ {d,0,a,0},{0,1,0,0},{-a,0,d,0},{0,0,0,1} });

    //Passo 6: Inverter a rotação em x
    TransformMatrix MRot6 = new TransformMatrix();
    MRot6 = MRot6.setMatrix({ {1,0,0,0},{0,c/d,b/d,0},{0,-b/d,c/d,0},{0,0,0,1} });
    //Ou MRot6 = rotacaoX(-angRotX);

    //Passo 7: Inverter a translação
    TransformMatrix MRot7 = new TransformMatrix();
    MRot7 = translacao({p1[0],p1[1],p1[2]});

    //O resultado é a multiplicação das matrizes na ordem inversa em que foram nomeadas

    return MRot7*MRot6*MRot5*MRot4*MRot3*MRot2*MRot1;
}

TransformMatrix rotacaoVetorOrigem(double angGraus, double a[3])
{
    return rotacaoVetor(angGraus,{0,0,0},a);
}

int main()
{
    double x[4][4] = {{4,3,2,1},{4,3,2,1},{4,3,2,1},{4,3,2,1}};
    TransformMatrix ident;
    TransformMatrix teste(x);
    ident.setMatrix(0,1,1);
    ident.mostrar();
    ident= teste * (ident);
    ident.mostrar();
    return 0;
}
