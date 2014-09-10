#include "janelagl.h"
#include <iostream>
#include "model.h"
#include "transformmatrix.h"

QVector3D aux;

JanelaGL::JanelaGL(QWidget *parent) :
    QGLWidget(parent)
{
}

void JanelaGL::initializeGL()
{
    glPolygonMode(GL_FRONT, GL_LINE);
    glPolygonMode(GL_BACK, GL_LINE);

    modelos << tnw::Model("../modelos/Moinho.obj") ;//<< tnw::Model("../modelos/ico.obj") << tnw::Model("../modelos/ico.obj");

    modelos[0].aplicarTransformacao(tnw::translacao(-1.2,0,0));
    modelos[0].aplicarTransformacao(tnw::escala(1.3,1.3,1.3));
    modelos[0].aplicarTransformacao(tnw::rotacaoX(25)*tnw::rotacaoY(25));
    aux = modelos[0].getPontoMedio(3);

    //modelos[1].aplicarTransformacao(tnw::translacao(-0.6,0,0)*tnw::escala(0.1,0.1,0.1));

    //modelos[2].aplicarTransformacao(tnw::translacao(0.6,0,0)*tnw::escala(0.2,0.2,0.2));
}

void JanelaGL::desenharModelos()
{
    foreach (tnw::Model m, modelos) {
        m.desenhar();
    }
}

void desenharEixos(){
    glBegin(GL_LINES);
    glColor3f(1.000000f, 0.000000f, 0.000000f);
    glVertex3d(0, 0, 0);
    glVertex3d(1, 0, 0);
    glColor3f(0.000000f, 1.000000f, 0.000000f);
    glVertex3d(0, 0, 0);
    glVertex3d(0, 1, 0);
    glColor3f(0.000000f, 0.000000f, 1.000000f);
    glVertex3d(0, 0, 0);
    glVertex3d(0, 0, 1);
    glColor3f(1.0f, 1.0f, 1.0f);
    glEnd();
}

void JanelaGL::resizeGL(int w, int h)
{
    if(h<w)
        glViewport((w-h)/2,0,h,h);
    else
        glViewport(0,(h-w)/2,w,w);
}

void JanelaGL::paintGL()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    //glOrtho(-1,1,-1,1,-1,1);
    modelos[0].aplicarTransformacao(tnw::translacao(aux)*tnw::rotacaoZ(10)*tnw::translacao(-aux),3);
    desenharModelos();

    desenharEixos();
}
