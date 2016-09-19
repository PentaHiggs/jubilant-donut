#include <QtTest/QtTest>
#include <array>
#include "src/projectivetransform.h"

class Test_projectiveTransform: public QObject
{
    Q_OBJECT
private:
    void compareMatrices(std::array<float,9> a, std::array<float,9> b, float tol = .001);
private slots:
    void identity();
    void doubling();
    void translationX();
    void translationY();
};
