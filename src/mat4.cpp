#include "mat4.h"
#include <Eigen/Dense>

extern "C"
{
    void computeInverseWithCheck(const SCALAR (*mat)[16], SCALAR (*inv)[16], bool *invertible)
    {
        Eigen::Map<const Eigen::Matrix4d> m(*mat);
        Eigen::Map<Eigen::Matrix4d> inverse(*inv);
        m.computeInverseWithCheck(inverse, *invertible);
    }
}
