#include "janelagl.h"
#include <cstdio>
#include "model.h"
#include "transformmatrix.h"
#include <QTimer>

tnw::Vertice pontoMedioMoinho,pontoMedioAstronauta;

JanelaGL::JanelaGL(QWidget *parent) :
    QGLWidget(parent)
{
    QObject::connect(&timer,SIGNAL(timeout()),this,SLOT(update()));
}

void JanelaGL::initializeGL()
{
    glEnable(GL_DEPTH_TEST);
    glPolygonMode(GL_FRONT, GL_LINE);
    glPolygonMode(GL_BACK, GL_LINE);

    modelos << tnw::Model("../modelos/MoinhoCor.obj") << tnw::Model("../modelos/Astronauta.obj");

    modelos[0].aplicarTransformacao(tnw::translacao(-modelos[0].getPontoMedio()));
    modelos[0].aplicarTransformacao(tnw::escala(1.4,1.4,1.4));
    modelos[0].aplicarTransformacao(tnw::rotacaoX(20)*tnw::rotacaoY(-10));
    pontoMedioMoinho = modelos[0].getPontoMedio(3);

    modelos[1].aplicarTransformacao(tnw::translacao(-0.1,0.3,0)*tnw::escala(0.1,0.1,0.1));
    pontoMedioAstronauta = modelos[1].getPontoMedio();
    timer.start(60);
}

void JanelaGL::desenharModelos()
{
    foreach (tnw::Model m, modelos)
        m.desenhar();
}

void JanelaGL::desenharModelos(int i)
{
    modelos[i].desenhar();
}

void JanelaGL::update()
{
    modelos[0].aplicarTransformacao(tnw::translacao(pontoMedioMoinho)*tnw::rotacaoZ(10)*tnw::translacao(-pontoMedioMoinho),3);
    modelos[1].aplicarTransformacao(tnw::rotacaoVetor(-10,QVector3D(1,3,0)));
    pontoMedioAstronauta = modelos[1].getPontoMedio();
    modelos[1].aplicarTransformacao(tnw::translacao(pontoMedioAstronauta)*tnw::rotacaoZ(10)*tnw::translacao(-pontoMedioAstronauta));
    this->repaint();
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
    //desenharEixos();
    glColor3f(1,1,1);
    desenharModelos(0);
    glColor3f(0,0,1);
    desenharModelos(1);
}
