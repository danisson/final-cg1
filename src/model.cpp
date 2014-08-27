#include "model.h"


tnw::Model::Model(QList<tnw::Vertice> vertices, QList<tnw::Face> faces)
{
    this->faces = faces;
    this->vertices = vertices;
}
