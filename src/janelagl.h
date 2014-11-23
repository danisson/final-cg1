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
    tnw::TransformMatrix projection;
    QList<tnw::Light> luzes;
    float ambiente[3];

    QTimer timer;

    struct orthoVal {
        double left = -1;
        double right = 1;
        double bottom = -1;
        double top = 1;
        double near = 0.7;
        double far = 3;
    } orthoValues;

    struct frusVal {
        double left = -0.5;
        double right = 0.5;
        double bottom = -0.5;
        double top = 0.5;
        double near = 0.7;
        double far = 3;
    } frusValues;

    struct isoVal {
        double scale = 1;
        double near = 0.7;
        double far = 3;
        bool positive_hor = true;
        bool positive_ver = false;
    } isoValues;

    struct persVal {
        double fovy = 90;
        double aspect = 1;
        double near = 0.7;
        double far = 3;
    } persValues;

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
    void updatePersVal(double val);
    void applyOrtho();
    void applyFrustum();
    void applyIso();
    void applyPers();
};

#endif // JANELAGL_H
