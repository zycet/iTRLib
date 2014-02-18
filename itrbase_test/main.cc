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

//////////////////////////////////////////////////////////////////////
// 内部函数，由SplitUV函数调用
//////////////////////////////////////////////////////////////////////
void ppp(F32 a[], F32 e[], F32 s[], F32 v[], int m, int
                  n)
{
    int i,j,p,q;
    F32 d;

    if (m>=n)
        i=n;
    else
        i=m;

    for (j=1; j<=i-1; j++)
    {
        a[(j-1)*n+j-1]=s[j-1];
        a[(j-1)*n+j]=e[j-1];
    }

    a[(i-1)*n+i-1]=s[i-1];
    if (m<n)
        a[(i-1)*n+i]=e[i-1];

    for (i=1; i<=n-1; i++)
    {
        for (j=i+1; j<=n; j++)
        {
            p=(i-1)*n+j-1;
            q=(j-1)*n+i-1;
            d=v[p];
            v[p]=v[q];
            v[q]=d;
        }
    }
}

//////////////////////////////////////////////////////////////////////
// 内部函数，由SplitUV函数调用
//////////////////////////////////////////////////////////////////////
void sss(F32 fg[2], F32 cs[2])
{
    F32 r,d;

    if ((fabs(fg[0])+fabs(fg[1]))==0.0)
    {
        cs[0]=1.0;
        cs[1]=0.0;
        d=0.0;
    }
    else
    {
        d=sqrt(fg[0]*fg[0]+fg[1]*fg[1]);
        if (fabs(fg[0])>fabs(fg[1]))
        {
            d=fabs(d);
            if (fg[0]<0.0)
                d=-d;
        }
        if (fabs(fg[1])>=fabs(fg[0]))
        {
            d=fabs(d);
            if (fg[1]<0.0)
                d=-d;
        }

        cs[0]=fg[0]/d;
        cs[1]=fg[1]/d;
    }

    r=1.0;
    if (fabs(fg[0])>fabs(fg[1]))
        r=cs[1];
    else if (cs[0]!=0.0)
        r=1.0/cs[0];

    fg[0]=d;
    fg[1]=r;
}
//////////////////////////////////////////////////////////////////////
// 一般实矩阵的奇异值分解，分解成功后，原矩阵对角线元素就是矩阵的奇异值
//
// 参数：
// 1. CMatrix& mtxU[M*M] - 返回分解后的U矩阵
// 2. CMatrix& mtxV[n*n] - 返回分解后的V矩阵
// 3. F32 eps - 计算精度，给0为默认值0.000001
//
// 返回值：BOOL型，求解是否成功
//////////////////////////////////////////////////////////////////////
BOOL SplitUV(itr_math::Matrix &A, itr_math::Matrix& U, itr_math::Matrix& V, F32 eps /*= 0.000001*/)
{
    int i,j,k,l,it,ll,kk,mm,nn,m1,ks;//iz,ix,iy;
    F32 d,dd,t,sm,sm1,em1,sk,ek,b,c,shh,fg[2],cs[2];
    F32 *s,*e,*w;
    if(eps<=0)
        eps=0.000001;
    int m = A.GetRow();
    int n = A.GetCol();

    // 初始化U, V矩阵

    //if (! mtxU.Init(m, m) || ! mtxV.Init(n, n))
     //   return false;

    // 临时缓冲区
    int ka = m>n?m:n + 1;
    s = new F32[ka];
    e = new F32[ka];
    w = new F32[ka];

    // 指定迭代次数为60
    it=60;
    k=n;

    if (m-1<n)
        k=m-1;

    l=m;
    if (n-2<m)
        l=n-2;
    if (l<0)
        l=0;

    // 循环迭代计算
    ll=k;
    if (l>k)
        ll=l;
    if (ll>=1)
    {
        for (kk=1; kk<=ll; kk++)
        {
            if (kk<=k)
            {
                d=0.0;
                for (i=kk; i<=m; i++)
                {
                   // ix=(i-1)*n+kk-1;

                    //d=d+m_pData[ix]*m_pData[ix];
                    d+=A(i-1,kk-1)*A(i-1,kk-1);
                }

                s[kk-1]=sqrt(d);
                if (s[kk-1]!=0.0)
                {
                    //ix=(kk-1)*n+kk-1;
                    if (A(kk-1,kk-1)!=0.0)//m_pData[ix]!=0.0)
                    {
                        s[kk-1]=fabs(s[kk-1]);
                        if (A(kk-1,kk-1)<0.0)
                            s[kk-1]=-s[kk-1];
                    }

                    for (i=kk; i<=m; i++)
                    {
                        //iy=(i-1)*n+kk-1;
                        A(i-1,kk-1)=A(i-1,kk-1)/s[kk-1];
                    }

                    A(kk-1,kk-1)=1.0+A(kk-1,kk-1);
                }

                s[kk-1]=-s[kk-1];
            }

            if (n>=kk+1)
            {
                for (j=kk+1; j<=n; j++)
                {
                    if ((kk<=k)&&(s[kk-1]!=0.0))
                    {
                        d=0.0;
                        for (i=kk; i<=m; i++)
                        {
                            //ix=(i-1)*n+kk-1;
                            //iy=(i-1)*n+j-1;
                            //d=d+m_pData[ix]*m_pData[iy];
                            d+=A(i-1,kk-1)*A(i-1,j-1);
                        }

                        //d=-d/m_pData[(kk-1)*n+kk-1];
                        d=-d/A(kk-1,kk-1);
                        for (i=kk; i<=m; i++)
                        {
                            //ix=(i-1)*n+j-1;
                            //iy=(i-1)*n+kk-1;
                           // m_pData[ix]=m_pData[ix]+d*m_pData[iy];
                           A(i-1,j-1)+=d*A(i-1,kk-1);
                        }
                    }

                    //e[j-1]=m_pData[(kk-1)*n+j-1];
                    e[j-1]=A(kk-1,j-1);
                }
            }

            if (kk<=k)
            {
                for (i=kk; i<=m; i++)
                {
                   // ix=(i-1)*m+kk-1;
                    //iy=(i-1)*n+kk-1;
                    //mtxU.m_pData[ix]=m_pData[iy];
                    U(i-1,kk-1)=A(i-1,kk-1);
                }
            }

            if (kk<=l)
            {
                d=0.0;
                for (i=kk+1; i<=n; i++)
                    d=d+e[i-1]*e[i-1];

                e[kk-1]=sqrt(d);
                if (e[kk-1]!=0.0)
                {
                    if (e[kk]!=0.0)
                    {
                        e[kk-1]=fabs(e[kk-1]);
                        if (e[kk]<0.0)
                            e[kk-1]=-e[kk-1];
                    }

                    for (i=kk+1; i<=n; i++)
                        e[i-1]=e[i-1]/e[kk-1];

                    e[kk]=1.0+e[kk];
                }

                e[kk-1]=-e[kk-1];
                if ((kk+1<=m)&&(e[kk-1]!=0.0))
                {
                    for (i=kk+1; i<=m; i++)
                        w[i-1]=0.0;

                    for (j=kk+1; j<=n; j++)
                        for (i=kk+1; i<=m; i++)

                           // w[i-1]=w[i-1]+e[j-1]*m_pData[(i-1)*n+j-1];
                            w[i-1]=w[i-1]+e[j-1]*A(i-1,j-1);

                        for (j=kk+1; j<=n; j++)
                        {
                            for (i=kk+1; i<=m; i++)
                            {
                                //ix=(i-1)*n+j-1;
                                A(i-1,j-1)=A(i-1,j-1)-w[i-1]*e[j-1]/e[kk];
                                //m_pData[ix]=m_pData[ix]-w[i-1]*e[j-1]/e[kk];
                            }
                        }
                }

                for (i=kk+1; i<=n; i++)
                    //mtxV.m_pData[(i-1)*n+kk-1]=e[i-1];
                    V(i-1,kk-1)=e[i-1];
            }
        }
    }

    mm=n;
    if (m+1<n)
        mm=m+1;
    if (k<n)
        //s[k]=m_pData[k*n+k];
        s[k]=A(k,k);
    if (m<mm)
        s[mm-1]=0.0;
    if (l+1<mm)
        //e[l]=m_pData[l*n+mm-1];
        e[l]=A(l,mm-1);

    e[mm-1]=0.0;
    nn=m;
    if (m>n)
        nn=n;
    if (nn>=k+1)
    {
        for (j=k+1; j<=nn; j++)
        {
            for (i=1; i<=m; i++)
                //mtxU.m_pData[(i-1)*m+j-1]=0.0;
                U(i-1,j-1)=0.0;
            //mtxU.m_pData[(j-1)*m+j-1]=1.0;
            U(j-1,j-1)=1.0;
        }
    }

    if (k>=1)
    {
        for (ll=1; ll<=k; ll++)
        {
            kk=k-ll+1;
            //iz=(kk-1)*m+kk-1;
            if (s[kk-1]!=0.0)
            {
                if (nn>=kk+1)
                {
                    for (j=kk+1; j<=nn; j++)
                    {
                        d=0.0;
                        for (i=kk; i<=m; i++)
                        {
                            //ix=(i-1)*m+kk-1;
                           //iy=(i-1)*m+j-1;

                            //d=d+mtxU.m_pData[ix]*mtxU.m_pData[iy]/mtxU.m_pData[iz];
                            d=d+U(i-1,kk-1)*U(i-1,j-1)/U(kk-1,kk-1);
                        }

                        d=-d;
                        for (i=kk; i<=m; i++)
                        {
                           // ix=(i-1)*m+j-1;
                           // iy=(i-1)*m+kk-1;

                            //mtxU.m_pData[ix]=mtxU.m_pData[ix]+d*mtxU.m_pData[iy];
                            U(i-1,j-1)=U(i-1,j-1)+d*U(i-1,kk-1);
                        }
                    }
                }

                for (i=kk; i<=m; i++)
                {
                    //ix=(i-1)*m+kk-1;
                   // mtxU.m_pData[ix]=-mtxU.m_pData[ix];
                    U(i-1,kk-1)=-U(i-1,kk-1);
                }

               // mtxU.m_pData[iz]=1.0+mtxU.m_pData[iz];
                U(kk-1,kk-1)=1.0+U(kk-1,kk-1);
                if (kk-1>=1)
                {
                    for (i=1; i<=kk-1; i++)

                        //mtxU.m_pData[(i-1)*m+kk-1]=0.0;
                        U(i-1,kk-1)=0.0;
                }
            }
            else
            {
                for (i=1; i<=m; i++)
                    //mtxU.m_pData[(i-1)*m+kk-1]=0.0;
                    U(i-1,kk-1)=0.0;
               // mtxU.m_pData[(kk-1)*m+kk-1]=1.0;
                U(kk-1,kk-1)=1.0;
            }
        }
    }

    for (ll=1; ll<=n; ll++)
    {
        kk=n-ll+1;
        //iz=kk*n+kk-1;

        if ((kk<=l)&&(e[kk-1]!=0.0))
        {
            for (j=kk+1; j<=n; j++)
            {
                d=0.0;
                for (i=kk+1; i<=n; i++)
                {
                    //ix=(i-1)*n+kk-1;
                    //iy=(i-1)*n+j-1;
                    //d=d+mtxV.m_pData[ix]*mtxV.m_pData[iy]/mtxV.m_pData[iz];
                    d=d+V(i-1,kk-1)*V(i-1,j-1)/V(kk,kk-1);
                }

                d=-d;
                for (i=kk+1; i<=n; i++)
                {
                    //ix=(i-1)*n+j-1;
                    //iy=(i-1)*n+kk-1;
                   // mtxV.m_pData[ix]=mtxV.m_pData[ix]+d*mtxV.m_pData[iy];
                    V(i-1,j-1)=V(i-1,j-1)+d*V(i-1,kk-1);
                }
            }
        }

        for (i=1; i<=n; i++)
            //mtxV.m_pData[(i-1)*n+kk-1]=0.0;
            V(i-1,kk-1)=0.0;

        //mtxV.m_pData[iz-n]=1.0;
        V(kk-1,kk-1)=1.0;
    }

    for (i=1; i<=m; i++)
        for (j=1; j<=n; j++)
            //m_pData[(i-1)*n+j-1]=0.0;
            A(i-1,j-1)=0.0;

        m1=mm;
        it=60;
        while (true)
        {
            if (mm==0)
            {
                ppp(A.GetData(),e,s,V.GetData(),m,n);
                return true;
            }
            if (it==0)
            {
                ppp(A.GetData(),e,s,V.GetData(),m,n);
                return false;
            }

            kk=mm-1;
            while ((kk!=0)&&(fabs(e[kk-1])!=0.0))
            {
                d=fabs(s[kk-1])+fabs(s[kk]);
                dd=fabs(e[kk-1]);
                if (dd>eps*d)
                    kk=kk-1;
                else
                    e[kk-1]=0.0;
            }

            if (kk==mm-1)
            {
                kk=kk+1;
                if (s[kk-1]<0.0)
                {
                    s[kk-1]=-s[kk-1];
                    for (i=1; i<=n; i++)
                    {
                        //ix=(i-1)*n+kk-1;
                        //mtxV.m_pData[ix]=-mtxV.m_pData[ix];
                        V(i-1,kk-1)=-V(i-1,kk-1);
                    }
                }

                while ((kk!=m1)&&(s[kk-1]<s[kk]))
                {
                    d=s[kk-1];
                    s[kk-1]=s[kk];
                    s[kk]=d;
                    if (kk<n)
                    {
                        for (i=1; i<=n; i++)
                        {
                            //ix=(i-1)*n+kk-1;
                            //iy=(i-1)*n+kk;
                            //d=mtxV.m_pData[ix];
                            d=V(i-1,kk-1);
                            //mtxV.m_pData[ix]=mtxV.m_pData[iy];
                            V(i-1,kk-1)=V(i-1,kk);
                            //mtxV.m_pData[iy]=d;
                            V(i-1,kk)=d;
                        }
                    }

                    if (kk<m)
                    {
                        for (i=1; i<=m; i++)
                        {
                            //ix=(i-1)*m+kk-1;
                            //iy=(i-1)*m+kk;
                            //d=mtxU.m_pData[ix];
                            d=U(i-1,kk-1);
                            U(i-1,kk-1)=U(i-1,kk);
                            U(i-1,kk)=d;
                            //mtxU.m_pData[ix]=mtxU.m_pData[iy];
                            //mtxU.m_pData[iy]=d;
                        }
                    }

                    kk=kk+1;
                }

                it=60;
                mm=mm-1;
            }
            else
            {
                ks=mm;
                while ((ks>kk)&&(fabs(s[ks-1])!=0.0))
                {
                    d=0.0;
                    if (ks!=mm)
                        d=d+fabs(e[ks-1]);
                    if (ks!=kk+1)
                        d=d+fabs(e[ks-2]);

                    dd=fabs(s[ks-1]);
                    if (dd>eps*d)
                        ks=ks-1;
                    else
                        s[ks-1]=0.0;
                }

                if (ks==kk)
                {
                    kk=kk+1;
                    d=fabs(s[mm-1]);
                    t=fabs(s[mm-2]);
                    if (t>d)
                        d=t;

                    t=fabs(e[mm-2]);
                    if (t>d)
                        d=t;

                    t=fabs(s[kk-1]);
                    if (t>d)
                        d=t;

                    t=fabs(e[kk-1]);
                    if (t>d)
                        d=t;

                    sm=s[mm-1]/d;
                    sm1=s[mm-2]/d;
                    em1=e[mm-2]/d;
                    sk=s[kk-1]/d;
                    ek=e[kk-1]/d;
                    b=((sm1+sm)*(sm1-sm)+em1*em1)/2.0;
                    c=sm*em1;
                    c=c*c;
                    shh=0.0;

                    if ((b!=0.0)||(c!=0.0))
                    {
                        shh=sqrt(b*b+c);
                        if (b<0.0)
                            shh=-shh;

                        shh=c/(b+shh);
                    }

                    fg[0]=(sk+sm)*(sk-sm)-shh;
                    fg[1]=sk*ek;
                    for (i=kk; i<=mm-1; i++)
                    {
                        sss(fg,cs);
                        if (i!=kk)
                            e[i-2]=fg[0];

                        fg[0]=cs[0]*s[i-1]+cs[1]*e[i-1];
                        e[i-1]=cs[0]*e[i-1]-cs[1]*s[i-1];
                        fg[1]=cs[1]*s[i];
                        s[i]=cs[0]*s[i];

                        if ((cs[0]!=1.0)||(cs[1]!=0.0))
                        {
                            for (j=1; j<=n; j++)
                            {
                                //ix=(j-1)*n+i-1;
                                //iy=(j-1)*n+i;

                               // d=cs[0]*mtxV.m_pData[ix]+cs[1]*mtxV.m_pData[iy];
                                d=cs[0]*V(j-1,i-1)+cs[1]*V(j-1,i);
                               // mtxV.m_pData[iy]=-cs[1]*mtxV.m_pData[ix]+cs[0]*mtxV.m_pData[iy];
                                V(j-1,i)=-cs[1]*V(j-1,i-1)+cs[0]*V(j-1,i);
                               // mtxV.m_pData[ix]=d;
                                V(j-1,i-1)=d;
                            }
                        }

                        sss(fg,cs);
                        s[i-1]=fg[0];
                        fg[0]=cs[0]*e[i-1]+cs[1]*s[i];
                        s[i]=-cs[1]*e[i-1]+cs[0]*s[i];
                        fg[1]=cs[1]*e[i];
                        e[i]=cs[0]*e[i];

                        if (i<m)
                        {
                            if
                                ((cs[0]!=1.0)||(cs[1]!=0.0))
                            {
                                for (j=1; j<=m; j++)
                                {

                                    //ix=(j-1)*m+i-1;
                                    //iy=(j-1)*m+i;

                                    //d=cs[0]*mtxU.m_pData[ix]+cs[1]*mtxU.m_pData[iy];
                                    d=cs[0]*U(j-1,i-1)+cs[1]*U(j-1,i);
                                    //mtxU.m_pData[iy]=-cs[1]*mtxU.m_pData[ix]+cs[0]*mtxU.m_pData[iy];
                                    U(j-1,i)=-cs[1]*U(j-1,i-1)+cs[0]*U(j-1,i);
                                    U(j-1,i-1)=d;
                                }
                            }
                        }
                    }

                    e[mm-2]=fg[0];
                    it=it-1;
                }
                else
                {
                    if (ks==mm)
                    {
                        kk=kk+1;
                        fg[1]=e[mm-2];
                        e[mm-2]=0.0;
                        for (ll=kk; ll<=mm-1; ll++)
                        {
                            i=mm+kk-ll-1;
                            fg[0]=s[i-1];
                            sss(fg,cs);
                            s[i-1]=fg[0];
                            if (i!=kk)
                            {
                                fg[1]=-cs[1]*e[i-2];
                                e[i-2]=cs[0]*e[i-2];
                            }

                            if
                                ((cs[0]!=1.0)||(cs[1]!=0.0))
                            {
                                for (j=1; j<=n; j++)
                                {

                                    //ix=(j-1)*n+i-1;

                                    //iy=(j-1)*n+mm-1;

                                    //d=cs[0]*mtxV.m_pData[ix]+cs[1]*mtxV.m_pData[iy];
                                    d=cs[0]*V(j-1,i-1)+cs[1]*V(j-1,mm-1);
                                    //mtxV.m_pData[iy]=-cs[1]*mtxV.m_pData[ix]+cs[0]*mtxV.m_pData[iy];
                                    V(j-1,mm-1)=-cs[1]*V(j-1,i-1)+cs[0]*V(j-1,mm-1);
                                    V(j-1,i-1)=d;
                                }
                            }
                        }
                    }
                    else
                    {
                        kk=ks+1;
                        fg[1]=e[kk-2];
                        e[kk-2]=0.0;
                        for (i=kk; i<=mm; i++)
                        {
                            fg[0]=s[i-1];
                            sss(fg,cs);
                            s[i-1]=fg[0];
                            fg[1]=-cs[1]*e[i-1];
                            e[i-1]=cs[0]*e[i-1];
                            if ((cs[0]!=1.0)||(cs[1]!=0.0))
                            {
                                for (j=1; j<=m; j++)
                                {

                                    //ix=(j-1)*m+i-1;

                                   // iy=(j-1)*m+kk-2;

                                    //d=cs[0]*mtxU.m_pData[ix]+cs[1]*mtxU.m_pData[iy];
                                    d=cs[0]*U(j-1,i-1)+cs[1]*U(j-1,kk-2);
                                    //mtxU.m_pData[iy]=-cs[1]*mtxU.m_pData[ix]+cs[0]*mtxU.m_pData[iy];
                                    U(j-1,kk-2)=-cs[1]*U(j-1,i-1)+cs[0]*U(j-1,kk-2);
                                    U(j-1,i-1)=d;
                                }
                            }
                        }
                    }
                }
        }
    }

    return true;
}
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
    //Finish    */
    /*************************************/
    itr_math::Matrix M(3,4),A(3,4),S(3,4);
    itr_math::Matrix U(3,3);
    itr_math::Matrix V(4,4),Vt(4,4);
    itr_math::Vector W(4);
    /*M(0,0)=1;   M(0,1)=3;    M(0,2)=5;    M(0,3)=7;
    M(1,0)=2;   M(1,1)=4;    M(1,2)=6;    M(1,3)=8;*/
    //M.Init(2,4);
   // M(0,0)=1;   M(0,1)=3;    M(0,2)=5;    M(0,3)=7;    M(0,4)=9;   M(0,5)=11;    M(0,6)=13;    M(0,7)=15;  M(0,8)=17;
    //M(1,0)=2;   M(1,1)=4;    M(1,2)=6;    M(1,3)=8;    M(1,4)=10;  M(1,5)=12;    M(1,6)=14;    M(1,7)=16;  M(1,8)=18;
   // M(2,0)=2;   M(2,1)=4;    M(2,2)=6;    M(2,3)=8;    M(2,4)=10;  M(2,5)=12;    M(2,6)=14;    M(2,7)=16;  M(2,8)=18;
   // M(3,0)=1;   M(3,1)=3;    M(3,2)=5;    M(3,3)=7;    M(3,4)=9;   M(3,5)=11;    M(3,6)=13;    M(3,7)=15;  M(3,8)=17;
    //M(1,1)=1;   M(1,2)=3;    M(1,3)=5;    M(1,4)=7;    M(2,1)=2;   M(2,2)=4;    M(2,3)=6;    M(2,4)=8;
    M(0,0)=1;   M(0,1)=1;    M(0,2)=-1;  M(0,3)=-1;
    M(1,0)=2;   M(1,1)=1;    M(1,2)=0;   M(1,3)=2;
    M(2,0)=1;  M(2,1)=-1;    M(2,2)=0;   M(2,3)=1;

       svdcmp(M,W,V);

        printf("*********** version 1 *****************:\n");
        printf("Matrix\tV :\n");
        S32 m=V.GetRow();
        S32 n=V.GetCol();
        for(S32 i=0; i<m;i++)
        {   for(S32 j=0; j<n;j++)
                printf("%f\t",V(i,j));
            printf("\n");
        }
    V.Tran(Vt);
    printf("Matrix\tV' :\n");
        m=Vt.GetRow();
        n=Vt.GetCol();
        for(S32 i=0; i<m;i++)
        {   for(S32 j=0; j<n;j++)
                printf("%f\t",Vt(i,j));
            printf("\n");
        }
        S.Set(0);
        S32 q=0;
        while(W[q]!=0)
        {
            q++;
        }
        for(S32 i=0;i<q;i++)
            S(i,i)=W[i];
        printf("Matrix\tS :\n");
        m=S.GetRow();
        n=S.GetCol();
        for(S32 i=0; i<m;i++)
        {   for(S32 j=0; j<n;j++)
                printf("%f\t",S(i,j));
            printf("\n");
        }
        printf("Matrix\tU :\n");
        m=3;
        n=3;
        for(S32 i=0; i<m;i++)
        {   for(S32 j=0; j<n;j++)
                printf("%f\t",M(i,j));
            printf("\n");
        }

        U(0,0)=M(0,0);   U(0,1)=M(0,1);    U(0,2)=M(0,2);
        U(1,0)=M(1,0);   U(1,1)=M(1,1);    U(1,2)=M(1,2);
        U(2,0)=M(2,0);  U(2,1)=M(2,1);    U(2,2)=M(2,2);
        A=U*S;
        printf("Matrix\tA. :\n");
        m=A.GetRow();
        n=A.GetCol();
        for(S32 i=0; i<m;i++)
        {   for(S32 j=0; j<n;j++)
                printf("%f\t",A(i,j));
            printf("\n");
        }
        A=A*Vt;

        printf("Matrix\tA :\n");
        m=A.GetRow();
        n=A.GetCol();
        for(S32 i=0; i<m;i++)
        {   for(S32 j=0; j<n;j++)
                printf("%f\t",A(i,j));
            printf("\n");
        }
    M(0,0)=1;   M(0,1)=1;    M(0,2)=-1;  M(0,3)=-1;
    M(1,0)=2;   M(1,1)=1;    M(1,2)=0; M(1,3)=2;
    M(2,0)=1;  M(2,1)=-1;    M(2,2)=0;  M(2,3)=1;
        SplitUV(M, U, V, 0);
        V.Tran(V);
        printf("*********** version 2 *****************\n");
        printf("Matrix\tV :\n");
         m=V.GetRow();
         n=V.GetCol();
        for(S32 i=0; i<m;i++)
        {   for(S32 j=0; j<n;j++)
                printf("%f\t",V(i,j));
            printf("\n");
        }
        printf("Matrix\tS :\n");
        m=M.GetRow();
        n=M.GetCol();
        for(S32 i=0; i<m;i++)
        {   for(S32 j=0; j<n;j++)
                printf("%f\t",M(i,j));
            printf("\n");
        }

        printf("Matrix\tU :\n");
        m=U.GetRow();
        n=U.GetCol();
        for(S32 i=0; i<m;i++)
        {   for(S32 j=0; j<n;j++)
                printf("%f\t",U(i,j));
            printf("\n");
        }

    TestMathdeDeinit();
    /*************************************/
    TRACE_INFO("OK All");
    return 0;
}

