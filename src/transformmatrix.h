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
}
#endif // TRANSFORMMATRIX_H
