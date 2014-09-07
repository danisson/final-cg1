#ifndef TNW_MODEL_H
#define TNW_MODEL_H
#include <QList>
#include <QVector3D>
#include <tuple>
#include "transformatrix.h"

namespace tnw {

	/** Uma face é simplesmente uma tripla de Vertices. */
    typedef std::tuple<QVector3D*,QVector3D*,QVector3D*> Face;

	/** Um vertice tem a mesma representação que um QVector3D. */
	typedef QVector3D Vertice;

	/**
	 *  Esta classe representa um modelo. TODO
	 */
    class Model {
	private:
        QList<Vertice> vertices; // A lista de vertices normalzados do modelo.
        QList<Face> faces; // A lista de faces do modelo.
        QList<QList<Vertice*>> grupos; // A lista de grupos
        Vertice pontoMedio; // Ponto médio do objeto, pode estar desatualizado
	public:
        //Métodos
        void desenhar();
        void aplicarTransformação(TransformMatrix m); // Aplica a transformação no modelo inteiro
        void aplicarTransformação(TransformMatrix m,unsigned i) // Aplica a transformação no i-ésimo grupo do modelo.
        // Get and Setters
        QList<Vertice> getVertices();
        QList<Face> getFaces();
        Vertice getPontoMedio(); // Retorna e atualiza o ponto médio
        // Construtores
        Model(QString pathname); // Construtor que recebe um arquivo OBJ.
        Model(QList<Vertice> vertices,QList<Face> faces); // Construtor que recebe uma lista de vertices e faces.
	};

}
#endif
