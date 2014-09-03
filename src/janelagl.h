#ifndef JANELAGL_H
#define JANELAGL_H

#include <QGLWidget>

class JanelaGL : public QGLWidget
{
    Q_OBJECT
public:
    explicit JanelaGL(QWidget *parent = 0);

protected:
    void initializeGL();
    void resizeGL(int w, int h);
    void paintGL();
signals:

public slots:

};

#endif // JANELAGL_H
