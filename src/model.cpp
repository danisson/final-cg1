#include "model.h"
#include <QFile>
#include <cstdio>
#include <iostream>
#include <QStringList>
#include <QRegularExpression>
#include <QRegExp>
#include <GL/gl.h>

void tnw::Model::desenhar()
{
    glBegin(GL_TRIANGLES);
    foreach (tnw::Face f, this->faces) {
        glVertex3d((std::get<0>(f))->x(),(std::get<0>(f))->y(),(std::get<0>(f))->z());
        glVertex3d((std::get<1>(f))->x(),(std::get<1>(f))->y(),(std::get<1>(f))->z());
        glVertex3d((std::get<2>(f))->x(),(std::get<2>(f))->y(),(std::get<2>(f))->z());
    }
    glEnd();
}

QList<tnw::Vertice> tnw::Model::getVertices()
{
    return this->vertices;
}

QList<tnw::Face> tnw::Model::getFaces()
{
    return this->faces;
}

tnw::Model::Model(QString pathname)
{
    if(pathname.isEmpty())
        throw -1;
    // Se tudo estiver certo..
    QFile arquivo(pathname);
    // Vamos tentar abrir o arquivo
    if(!arquivo.open(QIODevice::ReadOnly))
        throw -1;

    QString linha;
    QStringList parseada;
    QStringList verticesDaFace;
    int* vtx = new int[3];
    int* txt = new int[3];
    int* nrm = new int[3];
    QRegExp regularExpression("([\\S]*)([\\s]*)([\\S]*[\\s]*)([\\S]*[\\s]*)([\\S]*[\\s]*)");

    while(!arquivo.atEnd())
    {
        linha = arquivo.readLine();
        switch (linha[0].toLatin1()) {
        case '#':
            // É um comentário
            break;
        case 'v': // Se for um vértice ou uma normal ou uma textura...
            regularExpression.indexIn(linha);
            parseada = regularExpression.capturedTexts();
            if(parseada[1] == "v")
                vertices << QVector3D(parseada[3].toFloat(),parseada[4].toFloat(),parseada[5].toFloat());
            break;
        case 'f': // Se for uma face...
            regularExpression.indexIn(linha);
            parseada = regularExpression.capturedTexts();
            for (int i = 3; i < 6; ++i) {
                verticesDaFace = parseada[i].split("/",QString::KeepEmptyParts);
                if(!verticesDaFace[0].isEmpty())
                    vtx[i-3] = verticesDaFace[0].toInt()-1;
                if(verticesDaFace.size() > 1&&!verticesDaFace[1].isEmpty())
                    txt[i-3] = verticesDaFace[0].toInt()-1;
                if(verticesDaFace.size() > 2&&!verticesDaFace[2].isEmpty())
                    nrm[i-3] = verticesDaFace[0].toInt()-1;
            }
            faces << tnw::Face(&(vertices[vtx[0]]),
                               &(vertices[vtx[1]]),
                               &(vertices[vtx[2]]));
            break;
        default:
            break;
        }
    }
    delete[] vtx;
    delete[] txt;
    delete[] nrm;

    float max[4]={0,0,0,0};
    foreach (tnw::Vertice v, vertices) {
        for (int i = 0; i < 3; ++i) {
            if(std::abs(v[i]) > max[i])
                max[i] = std::abs(v[i]);
        }
    }
    for (int i = 0; i < 3; ++i) {
        if(max[i] > max[3])
            max[3] = max[i];
    }
    std::cout << max[3] << std::endl;

    QMutableListIterator<tnw::Vertice> iter(vertices);
    while (iter.hasNext()) {
        tnw::Vertice v = iter.next();
        iter.setValue(tnw::Vertice(v.x()/max[3],v.y()/max[3],v.z()/max[3]));
    }

}

tnw::Model::Model(QList<tnw::Vertice> vertices, QList<tnw::Face> faces)
{
    this->faces = faces;
    this->vertices = vertices;
}
