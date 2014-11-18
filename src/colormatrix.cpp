#include "colormatrix.h"
#include <stdexcept>

tnw::ColorMatrix tnw::ColorMatrix::operator*(const tnw::ColorMatrix &direita)
{
    tnw::ColorMatrix retorno;
    for (int i = 0; i < 3; ++i)
        for (int j = 0; j < 3; ++j)
            retorno(i,j) = m[i][j]*direita(i,j);
    return retorno;
}

tnw::ColorMatrix &tnw::ColorMatrix::operator=(const tnw::ColorMatrix &direita)
{
    for (int i = 0; i < 3; ++i)
        for (int j = 0; j < 3; ++j)
            m[i][j] = direita(i,j);
    return *this;
}

float &tnw::ColorMatrix::operator()(unsigned i, unsigned j)
{
    if(i < 3 && j < 3)
        return m[i][j];
    throw std::invalid_argument("Indice fora da matrix");
}

float tnw::ColorMatrix::operator()(unsigned i, unsigned j) const
{
    if(i < 3 && j < 3)
        return m[i][j];
    throw std::invalid_argument("Indice fora da matrix");
}

float &tnw::ColorMatrix::getKd(unsigned i)
{
    if(i<3)
        return m[0][i];
    throw std::invalid_argument("Indice fora da matrix");
}

float tnw::ColorMatrix::getKd(unsigned i) const
{
    if(i<3)
        return m[0][i];
    throw std::invalid_argument("Indice fora da matrix");
}

void tnw::ColorMatrix::setKd(float a, float b, float c)
{
    m[0][0] = a;
    m[0][1] = b;
    m[0][2] = c;
}

float &tnw::ColorMatrix::getKa(unsigned i)
{
    if(i<3)
        return m[1][i];
    throw std::invalid_argument("Indice fora da matrix");
}

float tnw::ColorMatrix::getKa(unsigned i) const
{
    if(i<3)
        return m[1][i];
    throw std::invalid_argument("Indice fora da matrix");
}

void tnw::ColorMatrix::setKa(float a, float b, float c)
{
    m[1][0] = a;
    m[1][1] = b;
    m[1][2] = c;
}

float &tnw::ColorMatrix::getKs(unsigned i)
{
    if(i<3)
        return m[2][i];
    throw std::invalid_argument("Indice fora da matrix");
}

float tnw::ColorMatrix::getKs(unsigned i) const
{
    if(i<3)
        return m[2][i];
    throw std::invalid_argument("Indice fora da matrix");
}

void tnw::ColorMatrix::setKs(float a, float b, float c)
{
    m[2][0] = a;
    m[2][1] = b;
    m[2][2] = c;
}

float *tnw::ColorMatrix::toColor(QVector3D point,QVector3D normal,float ambiente[3],QList<tnw::Light> luzes)
{
    float* r = new float[3];
    for (int i = 0; i < 3; ++i) {
        r[i] = getKa(i)*ambiente[i];
        foreach (tnw::Light l, luzes) {
            QVector3D lpos = l.getPos();
            //QVector3D direction =  point - lpos;
            QVector3D direction =  lpos - point;
            direction.normalize();
            double cosseno = (QVector3D::dotProduct(direction,normal));
            if (cosseno<0)
                cosseno = 0;
            r[i] += getKd(i)*l.getKd(i)*cosseno;
            /*if(r[i] < 0 || r[i] > 1)  {
                printf("r[i] error\nn = %f %f %f\n",normal[0],normal[1],normal[2]);
                printf("l = %f %f %f\n",direction[0],direction[1],direction[2]);
                printf("lpos = %f %f %f\n",lpos[0],lpos[1],lpos[2]);
                printf("point = %f %f %f\n",point[0],point[1],point[2]);
                printf("d*n = %f\n",QVector3D::dotProduct(direction,normal));
                printf("kd = %f %f %f\n",l.getKd(0),l.getKd(1),l.getKd(2));
                printf("r = %f %f %f\n",r[0],r[1],r[2]);
                throw -1;
            }*/
            if(l.getKd(i) > 1) {
                printf("kd error\nn = %f %f %f\n",normal[0],normal[1],normal[2]);
                printf("l = %f %f %f\n",direction[0],direction[1],direction[2]);
                printf("lpos = %f %f %f\n",lpos[0],lpos[1],lpos[2]);
                printf("kd = %f %f %f\n",l.getKd(0),l.getKd(1),l.getKd(2));
                printf("point = %f %f %f\n",point[0],point[1],point[2]);
                throw -1;
            }
            if(l.getKs(i) != 0) {
                printf("ks error\nn = %f %f %f\n",normal[0],normal[1],normal[2]);
                printf("l = %f %f %f\n",direction[0],direction[1],direction[2]);
                printf("lpos = %f %f %f\n",lpos[0],lpos[1],lpos[2]);
                printf("kd = %f %f %f\n",l.getKd(0),l.getKd(1),l.getKd(2));
                printf("point = %f %f %f\n",point[0],point[1],point[2]);
                throw -1;
            }
        }
    }
    return r;
}

tnw::ColorMatrix::ColorMatrix() {
    for (int i = 0; i < 3; ++i)
        for (int j = 0; j < 3; ++j)
            m[i][j]=0;
}

tnw::ColorMatrix::ColorMatrix(const tnw::ColorMatrix &matrix)
{
    for (int i = 0; i < 3; ++i)
        for (int j = 0; j < 3; ++j)
            m[i][j]=matrix(i,j);
}
