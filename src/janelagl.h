#ifndef JANELAGL_H
#define JANELAGL_H

#include <QGLWidget>
#include <QList>
#include "model.h"

class JanelaGL : public QGLWidget
{
    Q_OBJECT
public:
    explicit JanelaGL(QWidget *parent = 0);

protected:
    QList<tnw::Model> modelos;

    void initializeGL();
    void resizeGL(int w, int h);
    void paintGL();
    void desenharModelos();
signals:

public slots:

};

#endif // JANELAGL_H
