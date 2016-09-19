#include "test/test_projectivetransform.h"
#include "src/projectivetransform.h"

#include <Eigen/Dense>
#include <cmath>
#include <string>
#include <iostream>
#include <sstream>

//#include "test_projectivetransform.moc"
QTEST_MAIN(Test_projectiveTransform)

using std::array;
using std::pair;

std::string arraysToString(array<float,9> a, array<float,9> b) {
    std::ostringstream os;
    os << "[";
    for( float x : a ) os << x << ", ";
    os << "]\n - vs - \n[";
    for( float x : b ) os << x << ", ";
    os << "]\n";
    return os.str();
}

void Test_projectiveTransform::compareMatrices(array<float,9> a, array<float,9> b, float tol ) {
    bool pass;
    for(int i = 0; i < 9; i++) {
        if (std::abs(a[i] - b[i]) >= tol) {
            pass = false;
        }
    }
    if (pass) {
        QVERIFY(true); 
    } else {
        QVERIFY2(false, arraysToString(a,b).c_str());
    }
    return;
}



void Test_projectiveTransform::identity() {
    array<pair<int,int>,4> in = {pair<int,int>(10,10), pair<int,int>(100,10), pair<int,int>(100,100), pair<int,int>(10,100)};
    array<pair<int,int>,4> out = {pair<int,int>(10,10), pair<int,int>(100,10), pair<int,int>(100,100), pair<int,int>(10,100)};
    
    // We should expect the identity transformation
    array<float,9> out_mat = {1.,0,0, 0,1.,0, 0,0,1.};
    compareMatrices(out_mat, projectiveTransform(in,out));
}

void Test_projectiveTransform::doubling() {
    array<pair<int,int>,4> in = {pair<int,int>(10,10), pair<int,int>(100,10), pair<int,int>(100,100), pair<int,int>(10,100)};
    array<pair<int,int>,4> out = {pair<int,int>(20,20), pair<int,int>(200,20), pair<int,int>(200,200), pair<int,int>(20,200)};
    
    // We should expect the (normalized) matrix [[2/3, 0, 0], [0, 2/3, 0], [0, 0, 1/3]]
    array<float,9> out_mat = {2/3., 0, 0,  0, 2/3.,0,  0, 0, 1/3.};
    compareMatrices(out_mat, projectiveTransform(in,out));
}

void Test_projectiveTransform::translationX() {
    array<pair<int,int>,4> in = {pair<int,int>(10,10), pair<int,int>(100,10), pair<int,int>(100,100), pair<int,int>(10,100)};
    array<pair<int,int>,4> out = {pair<int,int>(20,10), pair<int,int>(110,10), pair<int,int>(110,100), pair<int,int>(20,100)};
    
    // We should expect the (normalized) matrix [[.098533, 0, .98533], [0, .098533, 0], [0, 0, .098533]]
    array<float,9> out_mat = {0.098532927816, 0, 0.98532927816,  0, 0.098532927816, 0,  0, 0, 0.098532927816};
    compareMatrices(out_mat, projectiveTransform(in,out));
}

void Test_projectiveTransform::translationY() {
    array<pair<int,int>,4> in = {pair<int,int>(10,10), pair<int,int>(100,10), pair<int,int>(100,100), pair<int,int>(10,100)};
    array<pair<int,int>,4> out = {pair<int,int>(10,20), pair<int,int>(100,20), pair<int,int>(100,110), pair<int,int>(10,110)};
    
    // We should expect the (normalized) matrix [[.098533, 0, .98533], [0, .098533, 0], [0, 0, .098533]]
    array<float,9> out_mat = {0.098532927816, 0, 0,  0, 0.098532927816, 0.98532927816,  0, 0, 0.098532927816};
    compareMatrices(out_mat, projectiveTransform(in,out));
}

