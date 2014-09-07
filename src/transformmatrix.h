#ifndef TRANSFORMMATRIX_H
#define TRANSFORMMATRIX_H

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

        // Construtores
        TransformMatrix(); // Identidade
        TransformMatrix(double a[4][4]); // Por um vetor
        TransformMatrix(double** a); // Por um vetor dinâmico
        TransformMatrix(const TransformMatrix &obj); //Copiador

        // Desconstrutor
        ~TransformMatrix();

        //Get and Setter
        void setMatrix(double a[4][4]);
        void setMatrix(int i,int j,double a);
        double** getMatrix();
        double getMatrix(int i, int j);
    };

    //Funções que retornam as matrizes de transformação

    TransformMatrix translacao(double a[3]);
    TransformMatrix rotacaoX(double angGraus);
    TransformMatrix rotacaoY(double angGraus);
    TransformMatrix rotacaoZ(double angGraus);
    TransformMatrix rotacaoVetor(double angGraus, double p1[3], double p2[3]);
    TransformMatrix rotacaoVetorOrigem(double angGraus, double a[3]);
    TransformMatrix escala(double a[3]);

    //Função pra transformar graus em radianos

    double radianos(double graus);

}
#endif // TRANSFORMMATRIX_H
