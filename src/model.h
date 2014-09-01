#ifndef TNW_MODEL_H
#define TNW_MODEL_H
#include <QList>
#include <QVector3D>
#include <tuple>

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
	public:
        // Get and Setters
        QList<Vertice> getVertices();
        QList<Face> getFaces();
        // Construtores
        Model(QString pathname); // Construtor que recebe um arquivo OBJ.
        Model(QList<Vertice> vertices,QList<Face> faces); // Construtor que recebe uma lista de vertices e faces.
	};

}
#endif
