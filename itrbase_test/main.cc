/*
 *
 *   Copyright (C) 2013 BUAA iTR Research Center. All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 *
 * 1. Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in
 *    the documentation and/or other materials provided with the
 *    distribution.
 * 3. Neither the name PX4 nor the names of its contributors may be
 *    used to endorse or promote products derived from this software
 *    without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
 * "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
 * LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS
 * FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE
 * COPYRIGHT OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT,
 * INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING,
 * BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS
 * OF USE, DATA, OR PROFITS; OR BUSINESS S32ERRUPTION) HOWEVER CAUSED
 * AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT
 * LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN
 * ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
 * POSSIBILITY OF SUCH DAMAGE.
 *
 * main.cc
 *  Created on: 2013-9-10
 *      Author: buaa
 */

#include "itrbase.h"
#include "platform_test.h"
#include "containertest.h"
#include "mathtest.h"
#include "helpertest.h"
#include"math.h"


/*******************************************************************************
Singular value decomposition program, svdcmp, from "Numerical Recipes in C"
(Cambridge Univ. Press) by W.H. Press, S.A. Teukolsky, W.T. Vetterling,
and B.P. Flannery
*******************************************************************************/
#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#define NR_END 0
#define FREE_ARG char*
#define SIGN(a,b) ((b) >= 0.0 ? fabs(a) : -fabs(a))
static F32 dmaxarg1,dmaxarg2;
#define DMAX(a,b) (dmaxarg1=(a),dmaxarg2=(b),(dmaxarg1) > (dmaxarg2) ?(dmaxarg1) : (dmaxarg2))
static int iminarg1,iminarg2;
#define IMIN(a,b) (iminarg1=(a),iminarg2=(b),(iminarg1) < (iminarg2) ?(iminarg1) : (iminarg2))
/*F32 **dmatrix(int nrl, int nrh, int ncl, int nch)
// allocate a F32 matrix with subscript range m[nrl..nrh][ncl..nch]
{
    int i,nrow=nrh-nrl+1,ncol=nch-ncl+1;
    F32 **m;

    m=(F32 **) malloc((size_t)((nrow+NR_END)*sizeof(F32*)));
    m += NR_END;
    m -= nrl;
 //  allocate rows and set pointers to them
    m[nrl]=(F32 *) malloc((size_t)((nrow*ncol+NR_END)*sizeof(F32)));
    m[nrl] += NR_END;
    m[nrl] -= ncl;
    for(i=nrl+1;i<=nrh;i++) m[i]=m[i-1]+ncol;
    // return pointer to array of pointers to rows
    return m;
}*/
/*F32 *dvector(int nl, int nh)
 allocate a F32 vector with subscript range v[nl..nh]
{
    F32 *v;
    v=(F32 *)malloc((size_t) ((nh-nl+1+NR_END)*sizeof(F32)));
    return v-nl+NR_END;
}*/
/*
void free_dvector(itr_math::Vector v, int nl, int nh)
// free a F32 vector allocated with dvector()
{
    free((FREE_ARG) (v+nl-NR_END));
}   */
F32 pythag(F32 a, F32 b)
// compute (a2 + b2)^1/2 without destructive underflow or overflow
{
    F32 absa,absb;
    absa=fabs(a);
    absb=fabs(b);
    if (absa > absb)
        return absa*sqrt(1.0+(absb/absa)*(absb/absa));
    else
        return (absb == 0.0 ? 0.0 : absb*sqrt(1.0+(absa/absb)*(absa/absb)));
}
/******************************************************************************/
void svdcmp(itr_math::Matrix &a, itr_math::Vector &w, itr_math::Matrix &v)
/*******************************************************************************
Given a matrix a[1..m][1..n], this routine computes its singular value
decomposition, A = U.W.VT.  The matrix U replaces a on output.  The diagonal
matrix of singular values W is output as a vector w[1..n].  The matrix V (not
the transpose VT) is output as v[1..n][1..n].
 * U 代替 A 作为输出；并以向量的形式输出W，输出 n*n 大小的V，没有输出V的转置。
*******************************************************************************/
{
    S32 m=a.GetRow();
    S32 n=a.GetCol();
    S32 flag,i,its,j,jj,k,l,nm;
    F32 anorm,c,f,g,h,s,scale,x,y,z;
    //rv1=dvector(1,n);
    itr_math::Vector rv1(n);
    g=scale=anorm=0.0; // Householder reduction to bidiagonal form
    for (i=1;i<=n;i++)
    {
        l=i+1;
        rv1[i-1]=scale*g;
        g=s=scale=0.0;
        if (i <= m)
        {
            for (k=i;k<=m;k++)
                scale += fabs(a(k-1,i-1));
            if (scale)
            {
                for (k=i;k<=m;k++)
                {
                    a(k-1,i-1) /= scale;
                    s += a(k-1,i-1)*a(k-1,i-1);
                }
                f=a(i-1,i-1);
                g = -SIGN(sqrt(s),f);
                h=f*g-s;
                a(i-1,i-1)=f-g;
                for (j=l;j<=n;j++)
                {
                    for (s=0.0,k=i;k<=m;k++)
                        s += a(k-1,i-1)*a(k-1,j-1);
                f=s/h;
                for (k=i;k<=m;k++)
                    a(k-1,j-1) += f*a(k-1,i-1);
                }
                for (k=i;k<=m;k++)
                    a(k-1,i-1) *= scale;
            }
        }
        w[i-1]=scale *g;
        g=s=scale=0.0;
        if (i<=m&&i!=n)
        {
            for (k=l;k<=n;k++)
                scale += fabs(a(i-1,k-1));
            if (scale) {
                for (k=l;k<=n;k++)
                {
                    a(i-1,k-1) /= scale;
                    s += a(i-1,k-1)*a(i-1,k-1);
                }
                f=a(i-1,l-1);
                g = -SIGN(sqrt(s),f);
                h=f*g-s;
                a(i-1,l-1)=f-g;
                for (k=l;k<=n;k++)
                    rv1[k-1]=a(i-1,k-1)/h;
                for (j=l;j<=m;j++)
                {
                    for (s=0.0,k=l;k<=n;k++)
                        s += a(j-1,k-1)*a(i-1,k-1);
                    for (k=l;k<=n;k++)
                        a(j-1,k-1) += s*rv1[k-1];
                }
                for (k=l;k<=n;k++)
                    a(i-1,k-1) *= scale;
            }
        }
        anorm = DMAX(anorm,(fabs(w[i-1])+fabs(rv1[i-1])));
    }
    /*printf("debug bidialog\n");
    for(S32 i=0; i<m;i++)
    {   for(S32 j=0; j<n;j++)
            printf("%f\t",a(i,j));
        printf("\n");
    }*/
    for (i=n;i>=1;i--)
    { // Accumulation of right-hand transformations.
        if (i < n)
        {
            if (g)
            {
                for (j=l;j<=n;j++) // Double division to avoid possible underflow.
                    v(j-1,i-1)=(a(i-1,j-1)/a(i-1,l-1))/g;
                for (j=l;j<=n;j++)
                {
                    for (s=0.0,k=l;k<=n;k++)
                        s += a(i-1,k-1)*v(k-1,j-1);
                    for (k=l;k<=n;k++)
                        v(k-1,j-1) += s*v(k-1,i-1);
                }
            }
            for (j=l;j<=n;j++)
                v(i-1,j-1)=v(j-1,i-1)=0.0;
        }
        v(i-1,i-1)=1.0;
        g=rv1[i-1];
        l=i;
    }

    for (i=IMIN(m,n);i>=1;i--)
    { // Accumulation of left-hand transformations.
        l=i+1;
        g=w[i-1];
        for (j=l;j<=n;j++)
            a(i-1,j-1)=0.0;
        if (g)
        {
            g=1.0/g;
            for (j=l;j<=n;j++)
            {
                for (s=0.0,k=l;k<=m;k++)
                    s += a(k-1,i-1)*a(k-1,j-1);
                f=(s/a(i-1,i-1))*g;
                for (k=i;k<=m;k++)
                    a(k-1,j-1) += f*a(k-1,i-1);
            }
            for (j=i;j<=m;j++)
                a(j-1,i-1) *= g;
        }
        else
            for (j=i;j<=m;j++)
                a(j-1,i-1)=0.0;
        ++a(i-1,i-1);
    }

    for (k=n;k>=1;k--)
    { // Diagonalization of the bidiagonal form.
        for (its=1;its<=30;its++)
        {
            flag=1;
            for (l=k;l>=1;l--)
            { // Test for splitting.
                nm=l-1; // Note that rv1[1-1] is always zero.
                if ((F32)(fabs(rv1[l-1])+anorm) == anorm)
                {
                    flag=0;
                    break;
                }
                if ((F32)(fabs(w[nm-1])+anorm) == anorm)
                    break;
            }
            if (flag)
            {
                c=0.0; // Cancellation of rv1[l-1], if l > 1.
                s=1.0;
                for (i=l;i<=k;i++)
                {
                    f=s*rv1[i-1];
                    rv1[i-1]=c*rv1[i-1];
                    if ((F32)(fabs(f)+anorm) == anorm)
                        break;
                    g=w[i-1];
                    h=pythag(f,g);
                    w[i-1]=h;
                    h=1.0/h;
                    c=g*h;
                    s = -f*h;
                    for (j=1;j<=m;j++)
                    {
                        y=a(j-1,nm-1);
                        z=a(j-1,i-1);
                        a(j-1,nm-1)=y*c+z*s;
                        a(j-1,i-1)=z*c-y*s;
                    }
                }
            }
            z=w[k-1];
            if (l == k)
            { // Convergence.
                if (z < 0.0)
                { // Singular value is made nonnegative.
                    w[k-1] = -z;
                    for (j=1;j<=n;j++)
                        v(j-1,k-1) = -v(j-1,k-1);
                }
                break;
            }
            if (its == 30)
                printf("no convergence in 30 svdcmp iterations");
            x=w[l-1]; // Shift from bottom 2-by-2 minor.
            nm=k-1;
            y=w[nm-1];
            g=rv1[nm-1];
            h=rv1[k-1];
            f=((y-z)*(y+z)+(g-h)*(g+h))/(2.0*h*y);
            g=pythag(f,1.0);
            f=((x-z)*(x+z)+h*((y/(f+SIGN(g,f)))-h))/x;
            c=s=1.0; // Next QR transformation:
            for (j=l;j<=nm;j++)
            {
                i=j+1;
                g=rv1[i-1];
                y=w[i-1];
                h=s*g;
                g=c*g;
                z=pythag(f,h);
                rv1[j-1]=z;
                c=f/z;
                s=h/z;
                f=x*c+g*s;
                g = g*c-x*s;
                h=y*s;
                y *= c;
                for (jj=1;jj<=n;jj++)
                {
                    x=v(jj-1,j-1);
                    z=v(jj-1,i-1);
                    v(jj-1,j-1)=x*c+z*s;
                    v(jj-1,i-1)=z*c-x*s;
                }
                z=pythag(f,h);
                w[j-1]=z; // Rotation can be arbitrary if z = 0.
                if (z)
                {
                    z=1.0/z;
                    c=f*z;
                    s=h*z;
                }
                f=c*g+s*y;
                x=c*y-s*g;
                for (jj=1;jj<=m;jj++)
                {
                    y=a(jj-1,j-1);
                    z=a(jj-1,i-1);
                    a(jj-1,j-1)=y*c+z*s;
                    a(jj-1,i-1)=z*c-y*s;
                }
            }
            rv1[l-1]=0.0;
            rv1[k-1]=f;
            w[k-1]=x;
        }
    }
   // free_dvector(rv1,1,n);
}
void decomposition(itr_math::Matrix &B,itr_math::Matrix &U,itr_math::Vector &S,itr_math::Matrix &V)
{
    S32 m=B.GetRow();
    S32 n=B.GetCol();
    itr_math::Vector e(n);

    itr_math::Vector work(m);
    S32 wantu = 1;
    S32 wantv = 1;
    S32 nct;
        nct=(m-1)>n?n:(m-1);
    S32 nrt;
        nrt =0>(n-2)?0:(n-2);
    S32 i=0,
        j=0,
        k=0;
    S32 max_ncr=nct>nrt?nct:nrt;
    for( k=0; k<max_ncr; ++k )
    {
        if( k < nct )
        {
            S[k] = 0;
            for( i=k; i<m; ++i )
                 S[k] = hypot( S[k], B(i,k) );

            if( S[k] != 0 )
            {
                if( B(k,k) < 0 )
                    S[k] = -S[k];

                for( i=k; i<m; ++i )
                    B(i,k) /= S[k];
                B(k,k) += 1;
            }
            S[k] = -S[k];
        }

        for( j=k+1; j<n; ++j )
        {
            if( (k < nct) && ( S[k] != 0 ) )
            {
                // apply the transformation
                F32 t = 0;
                for( i=k; i<m; ++i )
                    t += B(i,k) * B(i,j);

                t = -t / B(k,k);
                for( i=k; i<m; ++i )
                    B(i,j) += t*B(i,k);
            }
            e[j] = B(k,j);
        }
    if( wantu & (k < nct) )
            for( i=k; i<m; ++i )
                U(i,k) = B(i,k);

        if( k < nrt )
        {
            // Compute the k-th row transformation and place the
            // k-th super-diagonal in e[k].
            // Compute 2-norm without under/overflow.
            e[k] = 0;
            for( i=k+1; i<n; ++i )
                e[k] = hypot( e[k], e[i] );

            if( e[k] != 0 )
            {
                if( e[k+1] < 0 )
                    e[k] = -e[k];

                for( i=k+1; i<n; ++i )
                    e[i] /= e[k];
                e[k+1] += 1;
            }
            e[k] = -e[k];

            if( (k+1 < m) && ( e[k] != 0 ) )
            {
                // apply the transformation
                for( i=k+1; i<m; ++i )
                    work[i] = 0;

                for( j=k+1; j<n; ++j )
                    for( i=k+1; i<m; ++i )
                        work[i] += e[j] * B(i,j);

                for( j=k+1; j<n; ++j )
                {
                    F32 t = -e[j]/e[k+1];
                    for( i=k+1; i<m; ++i )
                        B(i,j) += t * work[i];
                }
            }

            // Place the transformation in V for subsequent
            // back multiplication.
            if( wantv )
                for( i=k+1; i<n; ++i )
                    V(i,k) = e[i];
        }
    }

    // Set up the final bidiagonal matrix or order p.
    S32 p = n;

    if( nct < n )
        S[nct] = B(nct,nct);
    if( m < p )
        S[p-1] = 0;

    if( nrt+1 < p )
        e[nrt] = B(nrt,p-1);
    e[p-1] = 0;

    // if required, generate U
    if( wantu )
    {
        for( j=nct; j<n; ++j )
        {
            for( i=0; i<m; ++i )
                U(i,j) = 0;
            U(j,j) = 1;
        }

        for( k=nct-1; k>=0; --k )
            if( S[k] != 0 )
            {
                for( j=k+1; j<n; ++j )
                {
                    F32 t = 0;
                    for( i=k; i<m; ++i )
                        t += U(i,k) * U(i,j);
                    t = -t / U(k,k);

                    for( i=k; i<m; ++i )
                        U(i,j) += t * U(i,k);
                }

                for( i=k; i<m; ++i )
                    U(i,k) = -U(i,k);
                U(k,k) = 1 + U(k,k);

                for( i=0; i<k-1; ++i )
                    U(i,k) = 0;
            }
            else
            {
                for( i=0; i<m; ++i )
                    U(i,k) = 0;
                U(k,k) = 1;
            }
    }

    // if required, generate V
    if( wantv )
        for( k=n-1; k>=0; --k )
        {
            if( (k < nrt) && ( e[k] != 0 ) )
                for( j=k+1; j<n; ++j )
                {
                    F32 t = 0;
                    for( i=k+1; i<n; ++i )
                        t += V(i,k) * V(i,j);
                    t = -t / V(k+1,k);

                    for( i=k+1; i<n; ++i )
                        V(i,j) += t * V(i,k);
                }

            for( i=0; i<n; ++i )
                V(i,k) = 0;
            V(k,k) = 1;
        }

    // main iteration loop for the singular values
    S32 pp = p-1;
    S32 iter = 0;
    itr_math::Numerical NumericalObj;
    F32 eps;
        NumericalObj.Pow(2.0, -52.0, eps);

    while( p > 0 )
    {
        S32 k = 0;
        S32 kase = 0;

        for( k=p-2; k>=-1; --k )
        {
            if( k == -1 )
                break;

            if( GET_ABS(e[k]) <= eps*( GET_ABS(S[k])+GET_ABS(S[k+1]) ) )
            {
                e[k] = 0;
                break;
            }
        }

        if( k == p-2 )
            kase = 4;
        else
        {
            S32 ks;
            for( ks=p-1; ks>=k; --ks )
            {
                if( ks == k )
                    break;

                F32 t = ( (ks != p) ? GET_ABS(e[ks]) : 0 ) +
                         ( (ks != k+1) ? GET_ABS(e[ks-1]) : 0 );

                if( GET_ABS(S[ks]) <= eps*t )
                {
                    S[ks] = 0;
                    break;
                }
            }

            if( ks == k )
                kase = 3;
            else if( ks == p-1 )
                kase = 1;
            else
            {
                kase = 2;
                k = ks;
            }
        }
        k++;

        // Perform the task indicated by kase.
        switch( kase )
        {
            // deflate negligible s(p)
            case 1:
            {
                F32 f = e[p-2];
                e[p-2] = 0;

                for( j=p-2; j>=k; --j )
                {
                    F32 t = hypot( S[j], f );
                    F32 cs = S[j] / t;
                    F32 sn = f / t;
                    S[j] = t;

                    if( j != k )
                    {
                        f = -sn * e[j-1];
                        e[j-1] = cs * e[j-1];
                    }

                    if( wantv )
                        for( i=0; i<n; ++i )
                        {
                            t = cs*V(i,j) + sn*V(i,p-1);
                            V(i,p-1) = -sn*V(i,j) + cs*V(i,p-1);
                            V(i,j) = t;
                        }
                }
            }
            break;

            // split at negligible s(k)
            case 2:
            {
                F32 f = e[k-1];
                e[k-1] = 0;

                for( j=k; j<p; ++j )
                {
                    F32 t = hypot( S[j], f );
                    F32 cs = S[j] / t;
                    F32 sn = f / t;
                    S[j] = t;
                    f = -sn * e[j];
                    e[j] = cs * e[j];

                    if( wantu )
                        for( i=0; i<m; ++i )
                        {
                            t = cs*U(i,j) + sn*U(i,k-1);
                            U(i,k-1) = -sn*U(i,j) + cs*U(i,k-1);
                            U(i,j) = t;
                        }
                }
            }
            break;

            // perform one qr step
            case 3:
            {
                // calculate the shift
                F32 scale;
                scale=GET_ABS(S[k])>GET_ABS(e[k])?GET_ABS(S[k]):GET_ABS(e[k]);
                scale=scale>GET_ABS(e[p-2])?scale:GET_ABS(e[p-2]);
                scale=scale>GET_ABS(S[p-2])?scale:GET_ABS(S[p-2]);
                scale=scale>GET_ABS(S[p-1])?scale:GET_ABS(S[p-1]);
                F32 sp = S[p-1] / scale;
                F32 spm1 = S[p-2] / scale;
                F32 epm1 = e[p-2] / scale;
                F32 sk = S[k] / scale;
                F32 ek = e[k] / scale;
                F32 b = ( (spm1+sp)*(spm1-sp) + epm1*epm1 ) / 2.0;
                F32 c = (sp*epm1) * (sp*epm1);
                F32 shift = 0;

                if( ( b != 0 ) || ( c != 0 ) )
                {
                    shift = sqrt( b*b+c );
                    if( b < 0 )
                        shift = -shift;
                    shift = c / ( b+shift );
                }
                F32 f = (sk+sp)*(sk-sp) + shift;
                F32 g = sk * ek;

                // chase zeros
                for( j=k; j<p-1; ++j )
                {
                    F32 t = hypot( f, g );
                    F32 cs = f / t;
                    F32 sn = g / t;
                    if( j != k )
                        e[j-1] = t;

                    f = cs*S[j] + sn*e[j];
                    e[j] = cs*e[j] - sn*S[j];
                    g = sn * S[j+1];
                    S[j+1] = cs * S[j+1];

                    if( wantv )
                        for( i=0; i<n; ++i )
                        {
                            t = cs*V(i,j) + sn*V(i,j+1);
                            V(i,j+1) = -sn*V(i,j) + cs*V(i,j+1);
                            V(i,j) = t;
                        }

                    t = hypot( f, g );
                    cs = f / t;
                    sn = g / t;
                    S[j] = t;
                    f = cs*e[j] + sn*S[j+1];
                    S[j+1] = -sn*e[j] + cs*S[j+1];
                    g = sn * e[j+1];
                    e[j+1] = cs * e[j+1];

                    if( wantu && ( j < m-1 ) )
                        for( i=0; i<m; ++i )
                        {
                            t = cs*U(i,j) + sn*U(i,j+1);
                            U(i,j+1) = -sn*U(i,j) + cs*U(i,j+1);
                            U(i,j) = t;
                        }
                }
                e[p-2] = f;
                iter = iter + 1;
            }
            break;

            // convergence
            case 4:
            {
                // Make the singular values positive.
                if( S[k] <= 0 )
                {
                    S[k] = ( S[k] < 0 ) ? -S[k] : 0;
                    if( wantv )
                        for( i=0; i<=pp; ++i )
                            V(i,k) = -V(i,k);
                }

                // Order the singular values.
                while( k < pp )
                {
                    if( S[k] >= S[k+1] )
                        break;

                    F32 t = S[k];
                    S[k] = S[k+1];
                    S[k+1] = t;

                    if( wantv && ( k < n-1 ) )
                        for( i=0; i<n; ++i )
                            std::swap( V(i,k), V(i,k+1) );

                    if( wantu && ( k < m-1 ) )
                        for( i=0; i<m; ++i )
                            std::swap( U(i,k), U(i,k+1));
                    k++;
                }
                iter = 0;
                p--;
            }
            break;
        }
    }
}
void SVD_dec(itr_math::Matrix &A)
{
    S32 m,n,p;
    m=A.GetRow();
    n=A.GetCol();
    p=m>n?n:m;

    itr_math::Matrix U(m,p);
    itr_math::Matrix V(n,p);
    itr_math::Vector S(p);
    if(m>=n)
    {
        itr_math::Matrix B(A);
        decomposition(B,U,S,V);
    }
    else
    {
        itr_math::Matrix B(n,m);
        A.Tran(B);
        decomposition(B,V,S,U);
    }
    //();
    //getchar();getchar();getchar();
    printf("VVVVVV\n");
    m=V.GetRow();
    n=V.GetCol();
    for(S32 i=0; i<m;i++)
    {   for(S32 j=0; j<n;j++)
            printf("%f\t",V(i,j));
        printf("\n");
    }
    printf("SSSSSS\n");
    m=S.GetDim();
    for(S32 j=0; j<m;j++)
            printf("%f\t",S[j]);
    printf("\n");

    printf("UUUUUU\n");
    m=U.GetRow();
    n=U.GetCol();
    for(S32 i=0; i<m;i++)
    {   for(S32 j=0; j<n;j++)
            printf("%f\t",U(i,j));
        printf("\n");
    }
}
void testSVD(itr_math::Matrix &M)
{
    SVD_dec(M);
}



int main()
{
    //Platform
    TestAssistMacro();
    TestDebugSupport();
    //TestMemoryOperation();
    TestTypedef();
    //Container
    TestCycleQueue();
    //Math
    TestMathInit();
   // TestCalculate();
    //TestNumerical();
   // TestStatistics();
    //TestVector();

    TestCalculateTest();

    //TestMatrix();
    //TestGeometry();
    //TestTransform();
    //Test Helper
   // TestGaussianGenerate();
    //TestCalcEff();
    //Finish

    TestMathdeDeinit();

    TRACE_INFO("OK All");
    return 0;
}

