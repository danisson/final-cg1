#ifndef JANELAGL_H
#define JANELAGL_H

#include <QGLWidget>
#include <QList>
#include <QTimer>
#include "model.h"

class JanelaGL : public QGLWidget
{
    Q_OBJECT
public:
    explicit JanelaGL(QWidget *parent = 0);

protected:
    QList<tnw::Model> modelos;
    QTimer timer;

    void initializeGL();
    void resizeGL(int w, int h);
    void paintGL();
    void desenharModelos();
    void desenharModelos(int i);
signals:

public slots:
    void update();
};

#endif // JANELAGL_H
