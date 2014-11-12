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

tnw::ColorMatrix::ColorMatrix() {
    for (int i = 0; i < 3; ++i)
        for (int j = 0; j < 3; ++j)
            m[i][j]=0;
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
