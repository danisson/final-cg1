#ifndef TRANSFORMMATRIX_H
#define TRANSFORMMATRIX_H

#include <QVector4D>

namespace tnw {

    class TransformMatrix
    {
    private:
        double** matrix;
    public:
        // Métodos
        void mostrar();

        // Operadores
        TransformMatrix operator*(const TransformMatrix& direita);  // Multiplicação de Matriz
        TransformMatrix& operator= (const TransformMatrix& direita);// Atribuição
        double& operator() (unsigned i, unsigned j); // Acesso para modificação
        double operator() (unsigned i, unsigned j) const; // Acesso para visualização

        // Construtores
        TransformMatrix(); // Identidade
        TransformMatrix(double a[4][4]); // Por um vetor
        TransformMatrix(double** a); // Por um vetor dinâmico
        TransformMatrix(const TransformMatrix &obj); //Copiador

        // Desconstrutor
        ~TransformMatrix();

        //Get and Setter
        void setMatrix(double a[4][4]);
    };

    //Operador Matrix * QVector4D
    QVector4D operator*(const TransformMatrix& right, const QVector4D& left);

    //Funções que retornam as matrizes de transformação
    TransformMatrix translacao(double x, double y, double z);
    TransformMatrix rotacaoX(double angGraus);
    TransformMatrix rotacaoY(double angGraus);
    TransformMatrix rotacaoZ(double angGraus);
    TransformMatrix rotacaoVetor(double angGraus, double p1[3], double p2[3]);
    TransformMatrix rotacaoVetorOrigem(double angGraus, double a[3]);
    TransformMatrix escala(double x, double y, double z);

    //Função pra transformar graus em radianos
    double radianos(double graus);

}
#endif // TRANSFORMMATRIX_H
