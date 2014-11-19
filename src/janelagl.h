#ifndef JANELAGL_H
#define JANELAGL_H

#include <QGLWidget>
#include <QList>
#include <QTimer>
#include "model.h"
#include "transformmatrix.h"

class JanelaGL : public QGLWidget
{
    Q_OBJECT
public:
    explicit JanelaGL(QWidget *parent = 0);

protected:
    QList<tnw::Model> modelos;
    QTimer timer;
    tnw::TransformMatrix projection;

    struct orthoVal {
        double left = -1;
        double right = 1;
        double bottom = -1;
        double top = 1;
        double near = 1;
        double far = -1;
    } orthoValues;

    struct frusVal {
        double left = -1;
        double right = 1;
        double bottom = -1;
        double top = 1;
        double near = 1;
        double far = -1;
    } frusValues;

    struct isoVal {
        double scale = 1;
        double near = 1;
        double far = -1;
        bool positive_hor = true;
        bool positive_ver = true;
    } isoValues;

    void initializeGL();
    void resizeGL(int w, int h);
    void paintGL();
    void desenharModelos();
    void desenharModelos(int i);
signals:

public slots:
    void update();
    void updateOrthoVal(double val);
    void updateFrustumVal(double val);
    void updateIsoVal(double val);
    void updateIsoBoolVal(bool val);
    void applyOrtho();
    void applyFrustum();
    void applyIso();
};

#endif // JANELAGL_H
