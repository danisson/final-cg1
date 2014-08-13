#ifndef TNW_MODEL_H
#define TNW_MODEL_H
#include <QList>
#include <QVector3D>
#include <tuple>

namespace tnw {

	typedef std::tuple<QVector3D,QVector3D,QVector3D> Face;

	class Model {
	private:
		QList<QVector3D> vertices;
		QList<Face> faces;
	public:
		Model(QString pathname);
		Model(QList<QVector3D> vertices,QList<Face> faces);
	};

}
#endif