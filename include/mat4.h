#pragma once

#include <stdbool.h>

#define SCALAR double
#define INDEX unsigned int

#ifdef __cplusplus
extern "C"
{
#endif /* __cplusplus */

    void computeInverseWithCheck(const SCALAR (*mat)[16], SCALAR (*inv)[16], bool *invertible);

#ifdef __cplusplus
}
#endif /* __cplusplus */
