#ifndef COLORMATRIX_H
#define COLORMATRIX_H

namespace tnw  {
    class ColorMatrix
    {
    private:
        float m[3][3];
    public:
        ColorMatrix operator*(const ColorMatrix& direita);  // Multiplicação de Matriz
        ColorMatrix& operator= (const ColorMatrix& direita);// Atribuição
        float& operator() (unsigned i, unsigned j); // Acesso para modificação
        float  operator() (unsigned i, unsigned j) const; // Acesso para visualização

        float& getKd(unsigned i);
        float  getKd(unsigned i) const;
        void   setKd(float a, float b, float c);

        float& getKa(unsigned i);
        float  getKa(unsigned i) const;
        void   setKa(float a, float b, float c);

        float& getKs(unsigned i);
        float  getKs(unsigned i) const;
        void   setKs(float a, float b, float c);

        ColorMatrix(); // Construtor
        ColorMatrix(const ColorMatrix& m); // Copiador
    };
}
#endif // COLORMATRIX_H
