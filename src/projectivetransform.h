#ifndef PROJECTIVETRANSFORM_H
#define PROJECTIVETRANSFORM_H

#include<array>
#include<utility>
#include<Eigen/Dense>
std::array<float,9> projectiveTransform(std::array<std::pair<int,int>,4> inPoints, std::array<std::pair<int,int>,4> outPoints);
Eigen::Matrix<float, 8, 9> createMatrix(std::array<std::pair<int,int>,4>& inPoints,
                                        std::array<std::pair<int,int>,4>& outPoints);
#endif // PROJECTIVETRANSFORM_H
