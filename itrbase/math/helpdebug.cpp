#include "helpdebug.h"

namespace itr_math
{
    void helpdebug::PrintMatrix(const Matrix& mat)
    {
        int n=mat.GetCol(),m=mat.GetRow();
        for(int i=0;i<m;i++)
        {
            for(int j=0;j<n;j++)
            {
                printf("%f ",mat(i,j));
            }
            printf("\n");
        }
        printf("\n");
    }
    void helpdebug::PrintVector(const Vector& vec)
    {
        int n=vec.GetDim();
        for(int i=0;i<n;i++)
            printf("%f ",vec[i]);
        printf("\n");
    }
}
