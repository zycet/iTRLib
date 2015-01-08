#ifndef HELPDEBUG_H
#define HELPDEBUG_H
#include "math.h"

namespace itr_math
{
class helpdebug
{
    public:
    static void PrintMatrix(const Matrix& mat);
    static void PrintVector(const Vector& vec);
};
}
#endif // HELPDEBUG_H
