#include "model.h"
#include <QFile>
#include <cstdio>
#include <iostream>
#include <QStringList>
#include <QRegularExpression>
#include <QRegExp>

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
                verticesDaFace = parseada[i].split("/");
                if(!verticesDaFace[0].isEmpty())
                    vtx[i-3] = verticesDaFace[0].toInt()-1;
                if(!verticesDaFace[1].isEmpty())
                    txt[i-3] = verticesDaFace[0].toInt()-1;
                if(!verticesDaFace[2].isEmpty())
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

}

tnw::Model::Model(QList<tnw::Vertice> vertices, QList<tnw::Face> faces)
{
    this->faces = faces;
    this->vertices = vertices;
}
