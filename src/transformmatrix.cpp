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

TransformMatrix& TransformMatrix::operator=(const TransformMatrix& direita)
{
    for (int i = 0; i < 4; ++i) {
        for (int j = 0; j < 4; ++j) {
            matrix[i][j] = direita.matrix[i][j];
        }
    }
    return *this;
}

double &TransformMatrix::operator()(unsigned i, unsigned j)
{
    if (i >= 4 || j >= 4)
        throw std::invalid_argument("Indice fora da matrix");
    return matrix[i][j];
}

double TransformMatrix::operator()(unsigned i, unsigned j) const
{
    if (i >= 4 || j >= 4)
        throw std::invalid_argument("Indice fora da matrix");
    return matrix[i][j];
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

// Operador Matrix * QVector4D
QVector4D tnw::operator*(const TransformMatrix &right, const QVector4D &left)
{
    QVector4D resultado;
    double acc;
    for (int i = 0; i < 4; ++i) {
        for (int j = 0; j < 4; ++j) {
            acc=0;
            for (int k = 0; k < 4; ++k) {
                acc+= right(i,k)*left[k];
            }
        }
        resultado[i]=acc;
    }
    return resultado;
}

// Transformações Geométricas
TransformMatrix tnw::translacao(double x,double y, double z)
{
    double m[4][4] = {{1,0,0,x},{0,1,0,y},{0,0,1,z},{0,0,0,1}};
    return TransformMatrix(m);
}

TransformMatrix tnw::translacao(QVector3D v)
{
    return tnw::translacao(v[0],v[1],v[2]);
}

TransformMatrix tnw::escala(double x, double y, double z)
{
    double m[4][4] = {{x,0,0,0},{0,y,0,0},{0,0,z,0},{0,0,0,1}};
    return TransformMatrix(m);
}

TransformMatrix tnw::rotacaoX(double angGraus)
{
    double angRad = radianos(angGraus);
    double m[4][4] = {{1,0,0,0},{0,cos(angRad),-sin(angRad),0},{0,sin(angRad),cos(angRad),0},{0,0,0,1}};
    return TransformMatrix(m);
}

TransformMatrix tnw::rotacaoY(double angGraus)
{
    double angRad = radianos(angGraus);
    double m[4][4] = {{cos(angRad),0,sin(angRad),1},{0,1,0,0},{-sin(angRad),0,cos(angRad),0},{0,0,0,1}};
    return TransformMatrix(m);
}

TransformMatrix tnw::rotacaoZ(double angGraus)
{
    double angRad = radianos(angGraus);
    double m[4][4] = {{cos(angRad),-sin(angRad),0,0},{sin(angRad),cos(angRad),0,0},{0,0,1,0},{0,0,0,1}};
    return TransformMatrix(m);
}


TransformMatrix tnw::rotacaoVetor(double angGraus, double p1[3], double p2[3])
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
    TransformMatrix MRot1 = translacao(-p1[0],-p1[1],-p1[2]);

    //Passo 2: Levar o vetor de rotação para o plano xz
    double d = sqrt(b*b+c*c); //Comprimento da projeção do vetor no plano yz

    //double cosAngRotX = c/d;
    //double angRotX = acos(cosAngRotX);
    //angRotX = (angRotX*180)/M_PI
    //Podia definir a matriz em termos do ângulo de rotação ou direto?

    double m1[4][4] = {{1,0,0,0},{0,c/d,-b/d,0},{0,b/d,c/d,0},{0,0,0,1}};
    TransformMatrix MRot2(m1);
    //Ou MRot2 = rotacaoX(angRotX);

   //Passo 3: Rotacionar em relação ao eixo y para levar o vetor de rotação ao eixo z
    double m2[4][4] = {{d,0,0,-a},{0,1,0,0},{a,0,d,0},{0,0,0,1}};
    TransformMatrix MRot3(m2);

    //Passo 4:Rotacionar em torno de z pelo ângulo dado
    TransformMatrix MRot4 = rotacaoZ(angGraus);

    //Passos 5,6,7: Inverter as transformações aplicadas!

    //Passo 5: Inverter a rotação em y
    double m3[4][4] = {{d,0,a,0},{0,1,0,0},{-a,0,d,0},{0,0,0,1}};
    TransformMatrix  MRot5(m3);

    //Passo 6: Inverter a rotação em x
    double m4[4][4] = {{1,0,0,0},{0,c/d,b/d,0},{0,-b/d,c/d,0},{0,0,0,1}};
    TransformMatrix MRot6(m4);
    //Ou MRot6 = rotacaoX(-angRotX);

    //Passo 7: Inverter a translação
    TransformMatrix MRot7 = translacao(p1[0],p1[1],p1[2]);

    //O resultado é a multiplicação das matrizes na ordem inversa em que foram nomeadas

    return MRot7*MRot6*MRot5*MRot4*MRot3*MRot2*MRot1;
}
TransformMatrix tnw::rotacaoVetor(double angGraus, QVector3D p1, QVector3D p2)
{
    double a[3] = {p1[0],p1[1],p1[2]};
    double b[3] = {p2[0],p2[1],p2[2]};
    return tnw::rotacaoVetor(angGraus,a,b);
}


TransformMatrix tnw::rotacaoVetorOrigem(double angGraus, double a[3])
{
    double origin[] = {0,0,0};
    return rotacaoVetor(angGraus,origin,a);
}

double tnw::radianos(double graus){
    return (M_PI*graus)/180;
}
