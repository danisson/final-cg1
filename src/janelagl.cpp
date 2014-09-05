#include "janelagl.h"
#include "model.h"

tnw::Model* modelo = new tnw::Model("../modelos/Moinho.obj");
                     //new tnw::Model("../modelos/ico.obj");
                     //new tnw::Model("../modelos/cube.obj");

JanelaGL::JanelaGL(QWidget *parent) :
    QGLWidget(parent)
{
}

void JanelaGL::initializeGL()
{
    glPolygonMode(GL_FRONT, GL_LINE);
    glPolygonMode(GL_BACK, GL_LINE);
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
    //glOrtho(-1000,1000,-1000,1000,0,1000);
    glTranslated(-0.4,-0.3,0);
    glRotated(25,0,1,0);
    glRotated(25,1,0,0);
    modelo->desenhar();

}
