/*
	精简矩阵计算库
	BUAA 薛骋豪
	2010-1
	BUAA 张以成
	2012-8-24
*/

#ifndef _MATRIX_H
#define _MATRIX_H

#include ".\..\Basic\Basic.h"

#define	VNULL	((VEC *)Null)
#define	MNULL	((MAT *)Null)

#define EXCEPTION True
typedef F32 Real;

typedef struct
{
	U16 Dim;//维数
	Real* Data;
} VEC;

//先M(竖向个数)后N(横向个数)
typedef struct
{
	U16 M, N;
	Real** Data;
	Real* Base;

	//属性:0 普通，1对角，2对称
	U8 Property;
} MAT;

//内存分配
void* _BL_MatrixMemAllocate(int Size);
U8 _BL_CheckVec(VEC* Vec);
//建立向量(自动分配位置)
VEC BL_VecCreate(U16 Dim);
//建立向量(手动分配位置)
void BL_VecAllocate(VEC* Vec, U16 Dim);
//回收数据空间
void BL_VecFree(VEC* Vec);
//强制设置数据位置(需自行进行内存管理)
U8 BL_VecSetData(VEC* Vec, Real* Data, U16 Dim);
//设置向量值为一同一数值
void BL_VecSetValue(VEC* Vec, Real Value);
//从数组中复制数据到向量中
U8 BL_VecCopyFromArray(VEC* VecDst, Real* ArraySrc);
//将VecSrc的数据复制到VecDst中
U8 BL_VecCopy(VEC* VecDst, VEC VecSrc);
//复制指定位置的向量数据到另一向量的指定位置
U8 BL_VecIndexCopy(VEC* VecDst, U16 IndexDst, VEC VecSrc, U16 IndexSrc, U16 Length);
//向量相加
//VecDst=VecSrc1+VecSrc2
U8 BL_VecAdd(VEC* VecDst, VEC VecSrc1, VEC VecSrc2);
//向量相减
//VecDst=VecSrc1-VecSrc2
U8 BL_VecSub(VEC* VecDst, VEC VecSrc1, VEC VecSrc2);
//向量叉乘浮点值
//VecDst=VecSrc*Value
U8 BL_VecXReal(VEC* VecDst, VEC VecSrc, Real Value);
//向量自叉乘浮点值
//Vec=Vec*Value
U8 BL_VecSelfXReal(VEC* Vec, Real Value);
//求向量平方长度
Real BL_VecSquareLength(VEC* Vec);
//向量单位化
U8 BL_VecUnit(VEC* VecDst, VEC* VecSrc);
//向量自单位化
U8 BL_VecUnitSelf(VEC* Vec);
//三维向量叉积
void  BL_Vec3DimX(VEC* VecDst, VEC VecSrc1,  VEC VecSrc2);
//向量相乘求值
//R=Vec1*Vec2
Real  BL_VecXVec(VEC Vec1,  VEC Vec2);
//求多项式值(高次系数在前)
//aX^2+bX+c...
Real BL_VecCalcEq(VEC* Vec, Real X);
//向量值求和
Real BL_VecSumValue(VEC vec);
//建立矩阵(自动分配位置)
MAT BL_MatCreate(U16 M, U16 N);
//建立矩阵(手动分配位置)
void BL_MatAllocate(MAT* Mat, U16 M, U16 N);
//空返回FALSE
U8 BL_IsMatUnEmpty(MAT* Mat);
//回收矩阵数据空间
void BL_MatFree(MAT* Mat);
//把矩阵里面所有的值设为同一值
U8 BL_MatSetValue(MAT* Mat, Real Value);
//复制矩阵
//MatDst = MatSrc
U8 BL_MatCopy(MAT* MatDst, MAT MatSrc);
//把MatSrc矩阵复制到MatDst[a][b]处
U8 BL_MatIndexCopy(MAT* MatDst, U16 A, U16 B, MAT MatSrc);
//设Mat的每一列为Vec
U8 BL_MatRowSetVec(MAT* Mat, VEC Vec);
//把Mat设为对角阵Mat[i][i] = value
U8 BL_MatEye(MAT* Mat, Real Value);
//求矩阵的转置
//MatDst = (MatSrc)T
U8 BL_MatTran(MAT* MatDst, MAT MatSrc);
//矩阵相加
//MatDst = MatSrc1 + MatSrc2
U8 BL_MatAdd(MAT* MatDst, MAT MatSrc1, MAT MatSrc2);
//矩阵相减
//MatDst = MatSrc1 - MatSrc2
U8 BL_MatSub(MAT* MatDst, MAT MatSrc1, MAT MatSrc2);
//矩阵求逆
//MatDst = inv(MatSrc)
//MatTemp为操作用临时阵要保证足够大
U8 BL_MatInv(MAT* MatDst, MAT MatSrc, MAT MatTemp);
//矩阵相乘
//MatDst = MatSrc1 * MatSrc2
U8 BL_MatMul(MAT* MatDst, MAT MatSrc1, MAT MatSrc2);
//矩阵乘以实数
//MatDst = MatSrc * Value
U8 BL_MatXReal(MAT* MatDst, MAT MatSrc, Real Value);
//矩阵乘以实数
//Mat = Mat * Value
U8 BL_MatSelfXReal(MAT* Mat, Real Value);
//矩阵乘以向量
//VecDst = MatSrc * Vec
U8 BL_MatXVec(VEC* VecDst, MAT MatSrc, VEC VecSrc);
//向量乘以矩阵
//VecDst = VecSrc * MatSrc
U8 BL_VecXMat(VEC* VecDst, VEC VecSrc, MAT MatSrc);
//绑定地址为指定矩阵的指定子位置
U8 BL_MatBindAddress(MAT* MatDst, U16 MNew, U16 NNew, MAT MatSrc, U16 MStart, U16 NStart);
//转化为对称矩阵
U8 BL_MatSetSym(MAT* Mat);
//将非对角线上的数据清零
U8 BL_MatSetEye(MAT* Mat);
//求矩阵数值和
Real BL_MatSumValue(MAT Mat);

#endif
