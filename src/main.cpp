#include <QCoreApplication>
#include "model.h"

int main(int argc, char *argv[])
{
    tnw::Model modelo("teste.obj");
    for (int idx = 0; idx < modelo.getVertices().size(); ++idx) {
        printf("%d %f %f %f\n",idx,modelo.getVertices()[idx].x(),modelo.getVertices()[idx].y(),modelo.getVertices()[idx].z());
    }
    for (int idx = 0; idx < modelo.getFaces().size(); ++idx) {
        printf("%d %f %f %f\n",idx,(std::get<0>(modelo.getFaces()[idx]))->x()
                           ,(std::get<1>(modelo.getFaces()[idx]))->x()
                           ,(std::get<2>(modelo.getFaces()[idx]))->x());
    }
    return 0;
}
