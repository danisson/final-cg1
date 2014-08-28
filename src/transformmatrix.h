#ifndef TRANSFORMMATRIX_H
#define TRANSFORMMATRIX_H

namespace tnw {

    class TransformMatrix
    {
    public:
        double** matrix; //depois colocar como privado pls

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
    };
}
#endif // TRANSFORMMATRIX_H
