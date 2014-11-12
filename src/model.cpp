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
        std::get<3>(f)->normalize();
        std::get<4>(f)->normalize();
        std::get<5>(f)->normalize();

        // Passando os vértices pro OpenGL
        glVertex3d((std::get<0>(f))->x(),(std::get<0>(f))->y(),(std::get<0>(f))->z());
        glVertex3d((std::get<1>(f))->x(),(std::get<1>(f))->y(),(std::get<1>(f))->z());
        glVertex3d((std::get<2>(f))->x(),(std::get<2>(f))->y(),(std::get<2>(f))->z());
    }
    glEnd();
}

void tnw::Model::aplicarTransformacao(TransformMatrix m)
{
    QMutableListIterator<tnw::Vertice> iter(vertices);
    while (iter.hasNext()) {
        tnw::Vertice v = iter.next();
        iter.setValue(m*v);
    }
}

void tnw::Model::aplicarTransformacao(tnw::TransformMatrix m, int i)
{
    if(i < grupos.length()) {
        QMutableListIterator<tnw::Vertice*> iter(grupos[i]);
        while (iter.hasNext()) {
            tnw::Vertice* v = iter.next();
            *v = (m*(*v));
        }
    }
    else
        throw std::out_of_range("Grupo não existente");
}

QList<tnw::Vertice> tnw::Model::getVertices()
{
    return this->vertices;
}

QList<tnw::Face> tnw::Model::getFaces()
{
    return this->faces;
}

tnw::Vertice tnw::Model::getPontoMedio()
{
    double medio[4] = {0,0,0,1};
    int n = vertices.length();

    foreach (Vertice v, vertices) {
        for (int i = 0; i < 3; ++i) {
            medio[i] += v[i]/n;
        }
    }

    pontoMedio[0] = medio[0];
    pontoMedio[1] = medio[1];
    pontoMedio[2] = medio[2];
    pontoMedio[3] = medio[3];

    return pontoMedio;
}

tnw::Vertice tnw::Model::getPontoMedio(int i)
{
    if(i < grupos.length()) {
        float medio[4] = {0,0,0,1};
        int n = 0;
        tnw::Vertice pontoMedioG;

        foreach (Vertice* v, grupos[i])
            if((*v)[3]==1) n++;

        foreach (Vertice* v, grupos[i])
            if((*v)[3]==1)
                for (int j = 0; j < 3; ++j)
                    medio[j] += (*v)[j]/n;

        pontoMedioG[0] = medio[0];
        pontoMedioG[1] = medio[1];
        pontoMedioG[2] = medio[2];
        pontoMedioG[3] = medio[3];

        return pontoMedioG;
    }
    else
        throw std::out_of_range("Grupo não existente");
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
    //int* txt = new int[3];
    int* nrm = new int[3];
    QRegExp regularExpression("([\\S]*)([\\s]*)([\\S]*[\\s]*)([\\S]*[\\s]*)([\\S]*[\\s]*)");

    while(!arquivo.atEnd())
    {
        linha = arquivo.readLine();
        switch (linha[0].toLatin1()) {
        case '#':
            // É um comentário
            break;
        case 'g': // Se for um grupo.
            grupos << tnw::Grupo(); // Adiciona um novo grupo
            break;
        case 'v': // Se for um vértice ou uma normal ou uma textura...
            regularExpression.indexIn(linha);
            parseada = regularExpression.capturedTexts();
            if(parseada[1] == "v") {
                vertices << tnw::Vertice(parseada[3].toFloat(),parseada[4].toFloat(),parseada[5].toFloat(),1);
                if(grupos.length() > 0)
                    grupos.last() << &vertices.last();
            }
            if(parseada[1] == "vn") {
                normais << tnw::Vertice(parseada[3].toFloat(),parseada[4].toFloat(),parseada[5].toFloat(),0);
                if(grupos.length() > 0)
                    grupos.last() << &normais.last();
            }
            break;
        case 'f': // Se for uma face...
            regularExpression.indexIn(linha);
            parseada = regularExpression.capturedTexts();
            for (int i = 3; i < 6; ++i) {
                verticesDaFace = parseada[i].split("/",QString::KeepEmptyParts);
                if(!verticesDaFace[0].isEmpty())
                    vtx[i-3] = verticesDaFace[0].toInt()-1;
                if(verticesDaFace.size() > 2 && !verticesDaFace[2].isEmpty())
                    nrm[i-3] = verticesDaFace[2].toInt()-1;
                else
                    nrm[i-3] = -1;
            }

            faces << tnw::Face(&(vertices[vtx[0]]),
                               &(vertices[vtx[1]]),
                               &(vertices[vtx[2]]),
                               &(normais[nrm[0]]),
                               &(normais[nrm[1]]),
                               &(normais[nrm[2]]));
            break;
        default:
            break;
        }
    }
    delete[] vtx;
    //delete[] txt;
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

    QMutableListIterator<tnw::Vertice> iter(vertices);
    while (iter.hasNext()) {
        tnw::Vertice v = iter.next();
        iter.setValue(tnw::Vertice(v.x()/max[3],v.y()/max[3],v.z()/max[3],1));
    }

    double medio[3] = {0,0,0};

    foreach (Vertice v, vertices) {
        for (int i = 0; i < 3; ++i) {
            medio[i] += v[i];
        }
    }

    for (int i = 0; i < 3; ++i) {
        medio[i] /= vertices.length();
    }

    pontoMedio.setX(medio[0]);
    pontoMedio.setY(medio[1]);
    pontoMedio.setZ(medio[2]);
    pontoMedio.setW(1);

    std::cout << "Modelo carregado: " << pathname.toStdString() << std::endl;
    std::cout << "Quantidade de grupos: " << grupos.length() << std::endl;
    std::cout << "Ponto Médio: " << pontoMedio[0] << " , " << pontoMedio[1] << " , " << pontoMedio[2] << std::endl;
}

tnw::Model::Model(QList<tnw::Vertice> vertices, QList<tnw::Face> faces)
{
    this->faces = faces;
    this->vertices = vertices;
}
