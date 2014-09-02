#include "qqvector4d.h"
#include<cstdio>
#include<cstring>
#include<qstring.h>
void QQVector4D::multiplicar(TransformMatrix matrix)
{
    //Não dá pra fazer a multiplicação direto porque ele pede um Qvector4d na multiplicação já implementada...
    double temp=0;
    int i = 0;
    for (i=0;i<4;i++){
      temp+=matrix.getMatrix(0,i)*(this->x());
    }
    this->setX(temp);
    temp=0;
    for (i=0;i<4;i++){
     temp+=matrix.getMatrix(1,i)*(this->y());
    }
    this->setY(temp);
    temp=0;
    for (i=0;i<4;i++){
      temp+=matrix.getMatrix(2,i)*(this->z());
    }
    this->setZ(temp);
    //Na maior parte dos casos, a matrix será [0 0 0 1] nesta coluna.
    //Se precisar, podemos simplificar os calculos aqui setando o W da forma abaixo.
    //this->setW((m[3][4])*(this->w()));
    temp=0;
    for (i=0;i<4;i++){
      temp+=matrix.getMatrix(3,i)*(this->w());
    }
    this->setW(temp);
    temp=0;
}

/*void QQVector4D::mostrar()
{
    printf("┌──────────────────────────────────────────┐\n");
        printf("│%0.3le, %0.3le, %0.3le, %0.3le│\n",(double)(this->x),(double)(this->y),(double)(this->z),(double)(this->w));
    printf("└──────────────────────────────────────────┘\n");
}*/

int main()
{
    double x[4][4] = {{4,3,2,0},{4,3,2,0},{4,3,2,0},{4,3,2,1}};
    QQVector4D a(2.0,2.0,2.0,1.0);
    a.setX(2.0);
    a.setY(2.0);
    a.setZ(2.0);
    a.setW(1.0);
    //a.mostrar();
    a.multiplicar(x);
   // a.mostrar();
}

