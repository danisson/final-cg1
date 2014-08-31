#ifndef QQVECTOR4D_H
#define QQVECTOR4D_H

#include <QVector4D>
//Nome temporário, por favor, mudar para algo menos tosco
//O X, Y e Z são as dimensões do vetor, enquanto o W assinala vetor ou ponto(0 ou 1)
class QQVector4D : public QVector4D
{
    Q_OBJECT
public:
    //Métodos
    void multiplicar(double m[4][4]);
    void mostrar();
signals:

public slots:

};

#endif // QQVECTOR4D_H
