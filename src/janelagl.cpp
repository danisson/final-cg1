#include "janelagl.h"
#include "model.h"
#include "transformmatrix.h"

tnw::Model* modelo = new tnw::Model("../modelos/Moinho.obj");
                     //new tnw::Model("../modelos/ico.obj");
                     //new tnw::Model("../modelos/cube.obj");

tnw::Model* modelo2 = new tnw::Model("../modelos/ico.obj");
tnw::Model* modelo3 = new tnw::Model("../modelos/ico.obj");

JanelaGL::JanelaGL(QWidget *parent) :
    QGLWidget(parent)
{
}

void JanelaGL::initializeGL()
{
    glPolygonMode(GL_FRONT, GL_LINE);
    glPolygonMode(GL_BACK, GL_LINE);
    modelo->aplicarTransformacao(tnw::translacao(-0.4,-0.3,0));

    modelo2->aplicarTransformacao(tnw::escala(0.1,0.1,0.1));
    modelo2->aplicarTransformacao(tnw::translacao(-0.6,0,0));

    modelo3->aplicarTransformacao(tnw::escala(0.2,0.2,0.2));
    modelo3->aplicarTransformacao(tnw::translacao(0.6,0,0));
    //glClearColor(1,1,1,1);
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
    glLoadIdentity();
    //glOrtho(-10,10,-10,10,0,10);
    //glTranslated(-0.4,-0.3,0);
    //modelo->aplicarTransformacao(tnw::translacao(-0.01,-0.01,0),4);
    //glRotated(25,0,1,0);
    //glRotated(25,1,0,0);
    modelo->desenhar();
    modelo2->desenhar();
    modelo3->desenhar();

}
