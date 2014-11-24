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
    glPointSize(15);

    modelos << tnw::Model("../modelos/MoinhoCor.obj") << tnw::Model("../modelos/AstronautaCor.obj");

    modelos[0].aplicarTransformacao(tnw::translacao(-modelos[0].getPontoMedio()));
    modelos[0].aplicarTransformacao(tnw::escala(1.4,1.4,1.4));
    modelos[0].aplicarTransformacao(tnw::rotacaoX(20)*tnw::rotacaoY(-10));
    pontoMedioMoinho = modelos[0].getPontoMedio(3);

    modelos[1].aplicarTransformacao(tnw::translacao(-0.1,0.3,0)*tnw::escala(0.1,0.1,0.1));
    pontoMedioAstronauta = modelos[1].getPontoMedio();

    projection = tnw::ortho(-1.0,1.0,-1.0,1.0,-1.0,1.0);

    // Luz
    for (int i = 0; i < 3; ++i)
        ambiente[i] = 0.1;

    tnw::Light l1(1,0.2,0);
    l1.setKd(1,1,1);
    l1.setKs(0,0,0);
    tnw::Light l2(-1,0.2,0);
    l2.setKd(1,1,1);
    l2.setKs(0,0,0);
    luzes << l1 << l2;
    //luzes << l2;

    timer.start(60);
}

void JanelaGL::desenharModelos()
{
    foreach (tnw::Model m, modelos) {
        m.desenhar(projection,ambiente,luzes);
    }
}

void JanelaGL::desenharModelos(int i)
{
    modelos[i].desenhar(projection,ambiente,luzes);
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
    desenharModelos(0);
    glColor3f(0,0,1);
    desenharModelos(1);
    glColor3f(1,1,1);
    glBegin(GL_POINTS);
    foreach (tnw::Light l, luzes) {
        glVertex3d(l[0],l[1],l[2]);
    }
    glEnd();
}

void JanelaGL::updateOrthoVal(double val)
{
    QObject* nVal = sender();
    QString nome = nVal->objectName();
    if (nome == "lOrtho"){
        orthoValues.left = val;
    } else if (nome == "rOrtho"){
        orthoValues.right = val;
    } else if (nome == "tOrtho"){
        orthoValues.top = val;
    } else if (nome == "bOrtho"){
        orthoValues.bottom = val;
    } else if (nome == "nOrtho"){
        orthoValues.near = val;
    } else if (nome == "fOrtho"){
        orthoValues.far = val;
    }
}

void JanelaGL::updateFrustumVal(double val)
{
    QObject* nVal = sender();
    QString nome = nVal->objectName();

    if (nome == "lFrustum"){
        frusValues.left = val;
    } else if (nome == "rFrustum"){
        frusValues.right = val;
    } else if (nome == "tFrustum"){
        frusValues.top = val;
    } else if (nome == "bFrustum"){
        frusValues.bottom = val;
    } else if (nome == "nFrustum"){
        frusValues.near = val;
    } else if (nome == "fFrustum"){
        frusValues.far = val;
    }
}

void JanelaGL::updateIsoVal(double val)
{
    QObject* nVal = sender();
    QString nome = nVal->objectName();

    if (nome == "sIso"){
        isoValues.scale = val;
    } else if (nome == "nIso"){
        isoValues.near = val;
    } else if (nome == "fIso"){
        isoValues.far = val;
    }
}

void JanelaGL::updateIsoBoolVal(bool val)
{
    QObject* nVal = sender();
    QString nome = nVal->objectName();

    if (nome == "hIso"){
        isoValues.positive_hor = val;
    } else if (nome == "vIso"){
        isoValues.positive_ver = val;
    }
}

void JanelaGL::updatePersVal(double val)
{
    QObject* nVal = sender();
    QString nome = nVal->objectName();

    if (nome=="fovyPers"){
        persValues.fovy = val;
    } else if (nome=="aspPers"){
        persValues.aspect = val;
    } else if (nome=="nPers"){
        persValues.near = val;
    } else if (nome=="fPers"){
        persValues.far = val;
    }
}

void JanelaGL::applyOrtho()
{
    projection = tnw::ortho(orthoValues.left,orthoValues.right,orthoValues.bottom,orthoValues.top,orthoValues.near,orthoValues.far);
}

void JanelaGL::applyFrustum()
{
    projection = tnw::frustum(frusValues.left,frusValues.right,frusValues.bottom,frusValues.top,frusValues.near,frusValues.far)*tnw::translacao(QVector3D(0,0,-1));
}

void JanelaGL::applyIso(){
    projection = tnw::isometric(isoValues.scale,isoValues.near,isoValues.far,isoValues.positive_hor,isoValues.positive_ver);
}

void JanelaGL::applyPers(){
    projection = tnw::perspective(persValues.fovy,persValues.aspect,persValues.near,persValues.far)*tnw::translacao(QVector3D(0,0,-1));
}
