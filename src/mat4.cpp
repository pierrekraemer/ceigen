#include "mat4.h"
#include <eigen/Eigen/Dense>

using Matrix4d = Eigen::Matrix<double, 4, 4>;

extern "C"
{
    void computeInverseWithCheck(const SCALAR (*mat)[16], SCALAR (*inv)[16], bool *invertible)
    {
        Eigen::Map<const Matrix4d> m(*mat);
        Eigen::Map<Matrix4d> inverse(*inv);
        m.computeInverseWithCheck(inverse, *invertible);
    }
}
