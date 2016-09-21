#include "projectivetransform.h"
#include <Eigen/Dense>
#include <qDebug>

std::array<float,9> projectiveTransform(std::array<std::pair<int,int>,4> inPoints,
                                      std::array<std::pair<int,int>,4> outPoints){
    /* Function that calculates the transformation in projective space that maps the quadrilateral
     * with points given by inPoints to the quadilateral given by outPoint.  The points (x,y)
     * correspond, through the use of homogenous coordinates, to points (x,y,1) in projective space.
     * The output, a 9-element array, corresponds to the elements of the matrix M that acts on these points,
     * with the elements in the order M_01, M_02, M_03, M_10, M_11, M_12, M_20, M_21, M_22.
     *
     * The output is an array of floats, the input is two arrays of length four of pairs of int.
     *
     */
    int x1 = inPoints[0].first; int y1 = inPoints[0].second;
    int x2 = inPoints[1].first; int y2 = inPoints[1].second;
    int x3 = inPoints[2].first; int y3 = inPoints[2].second;
    int x4 = inPoints[3].first; int y4 = inPoints[3].second;

    int X1 = outPoints[0].first; int Y1 = outPoints[0].second;
    int X2 = outPoints[1].first; int Y2 = outPoints[1].second;
    int X3 = outPoints[2].first; int Y3 = outPoints[2].second;
    int X4 = outPoints[3].first; int Y4 = outPoints[3].second;

    Eigen::Matrix<float, 8, 9> M;
    M<<     x1, y1, 1,  0,  0,  0,  -1*X1*x1,   -1*X1*y1,   -1*X1,
            0,  0,  0,  x1, y1, 1,  -1*Y1*x1,   -1*Y1*y1,   -1*Y1,
            x2, y2, 1,  0,  0,  0,  -1*X2*x2,   -1*X2*y2,   -1*X2,
            0,  0,  0,  x2, y2, 1,  -1*Y2*x2,   -1*Y2*y2,   -1*Y2,
            x3, y3, 1,  0,  0,  0,  -1*X3*x3,   -1*X3*y3,   -1*X3,
            0,  0,  0,  x3, y3, 1,  -1*Y3*x3,   -1*Y3*y3,   -1*Y3,
            x4, y4, 1,  0,  0,  0,  -1*X4*x4,   -1*X4*y4,   -1*X4,
            0,  0,  0,  x4, y4, 1,  -1*Y4*x4,   -1*Y4*y4,   -1*Y4;

    // The kernel of M is the set of all matrices that transform inPoints to outPoints.  For simpicity, we fix
    // the matrices via normalization to one unique matrix corresponding to this kernel.
    Eigen::Matrix<float,9,1> s = M.fullPivLu().kernel();
    Eigen::Matrix<float,9,1> m = s.normalized();
    std::array<float,9> retArray = std::array<float,9>();
    for(int i=0; i<9; i++) retArray[i]=m(i,0);
    return retArray;
}
