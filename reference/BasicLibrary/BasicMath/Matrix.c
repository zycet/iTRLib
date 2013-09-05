/*
	精简矩阵计算库
	BUAA 薛骋豪
	2010-1
	BUAA 张以成
	2012-8-24
*/

#include <stdlib.h>
#include <string.h>
//#include <malloc.h>
#include <math.h>
#include ".\..\Basic\Basic.h"
#include "BasicMath.h"
#include ".\Matrix.h"

//内存分配
void* _BL_MatrixMemAllocate(int Size)
{
	//return malloc(Size);
	return BL_MemAllocEx(Size);
}

U8 _BL_CheckVec(VEC* Vec)
{
	if(Vec->Dim != 0 && Vec->Data == Null)
		return False;
	return True;
}

//建立向量(自动分配位置)
VEC BL_VecCreate(U16 Dim)
{
	VEC vec;
	vec.Dim = Dim;
	vec.Data = (Real*)_BL_MatrixMemAllocate(Dim * sizeof(Real));
	assert(vec.Data);
	memset(vec.Data, 0, Dim * sizeof(Real));
	return vec;
}

//建立向量(手动分配位置)
void BL_VecAllocate(VEC* Vec, U16 Dim)
{
	Vec->Dim = Dim;
	Vec->Data = (Real*)_BL_MatrixMemAllocate(Dim * sizeof(Real));
	assert(Vec->Data);
	memset(Vec->Data, 0, Dim * sizeof(Real));
}

//回收数据空间
void BL_VecFree(VEC* Vec)
{
	assert(Vec->Data);
	free(Vec->Data);
	Vec->Dim = 0;
}

//强制设置数据位置(需自行进行内存管理)
U8 BL_VecSetData(VEC* Vec, Real* Data, U16 Dim)
{
	assert(Data);
	Vec->Data = Data;
	Vec->Dim = Dim;
	return True;
}

//设置向量值为一同一数值
void BL_VecSetValue(VEC* Vec, Real Value)
{
	U16 i;
	assert(_BL_CheckVec(Vec));
	for(i = 0; i < Vec->Dim; i++)
		Vec->Data[i] = Value;
}

//从数组中复制数据到向量中
U8 BL_VecCopyFromArray(VEC* VecDst, Real* ArraySrc)
{
#if EXCEPTION
	if(VecDst->Dim == 0)
	{
		return False;
	}
	else
#endif

		memcpy((void*)VecDst->Data, (void*)ArraySrc, VecDst->Dim * sizeof(Real));
	return True;
}

//将VecSrc的数据复制到VecDst中
U8 BL_VecCopy(VEC* VecDst, VEC VecSrc)
{

#if EXCEPTION

#endif

	memcpy((void*)VecDst->Data, (void*)VecSrc.Data, VecSrc.Dim * sizeof(Real));
	return True;
}

//复制指定位置的向量数据到另一向量的指定位置
U8 BL_VecIndexCopy(VEC* VecDst, U16 IndexDst, VEC VecSrc, U16 IndexSrc, U16 Length)
{
	//	U16 i;
#if EXCEPTION

#endif

	memcpy((void*)&(VecDst->Data[IndexDst]), (void*)&(VecSrc.Data[IndexSrc]), Length * sizeof(Real));
	return True;
}

//向量相加
//VecDst=VecSrc1+VecSrc2
U8 BL_VecAdd(VEC* VecDst, VEC VecSrc1, VEC VecSrc2)
{
	U16 i;
#if EXCEPTION

#endif
	for(i = 0; i < VecSrc1.Dim; i++)
		VecDst->Data[i] = VecSrc1.Data[i] + VecSrc2.Data[i];
	return True;
}

//向量相减
//VecDst=VecSrc1-VecSrc2
U8 BL_VecSub(VEC* VecDst, VEC VecSrc1, VEC VecSrc2)
{
	U16 i;
#if EXCEPTION

#endif
	for(i = 0; i < VecSrc1.Dim; i++)
		VecDst->Data[i] = VecSrc1.Data[i] - VecSrc2.Data[i];
	return True;
}

//向量叉乘浮点值
//VecDst=VecSrc*Value
U8 BL_VecXReal(VEC* VecDst, VEC VecSrc, Real Value)
{
	U8 i;
#if EXCEPTION

#endif
	for(i = 0; i < VecSrc.Dim; i++)
		VecDst->Data[i] = Value  * VecSrc.Data[i];
	return True;
}

//向量自叉乘浮点值
//Vec=Vec*Value
U8 BL_VecSelfXReal(VEC* Vec, Real Value)
{
	U8 i;
#if EXCEPTION

#endif
	for(i = 0; i < Vec->Dim; i++)
		Vec->Data[i] = Value  * Vec->Data[i];
	return True;
}

//求向量平方长度
Real BL_VecSquareLength(VEC* Vec)
{
	U8 i;
	Real len = 0;
#if EXCEPTION

#endif
	for(i = 0; i < Vec->Dim; i++)
		len += BL_Square(Vec->Data[i]);
	return len;
}

//向量单位化
U8 BL_VecUnit(VEC* VecDst, VEC* VecSrc)
{
	U8 i;
	Real len = 0;
#if EXCEPTION

#endif
	len = BL_VecSquareLength(VecSrc);
	if(len < EPSINON)
		return False;
	len = sqrt(len);
	for(i = 0; i < VecSrc->Dim; i++)
		VecDst->Data[i] = VecSrc->Data[i] / len;
	return True;
}

//向量自单位化
U8 BL_VecUnitSelf(VEC* Vec)
{
	U8 i;
	Real len = 0;
#if EXCEPTION

#endif
	len = BL_VecSquareLength(Vec);
	if(len < EPSINON)
		return False;
	len = sqrt(len);
	for(i = 0; i < Vec->Dim; i++)
		Vec->Data[i] = Vec->Data[i] / len;
	return True;
}

//三维向量叉积
void  BL_Vec3DimX(VEC* VecDst, VEC VecSrc1,  VEC VecSrc2)
{
	//Assert
	VecDst->Data[0] = VecSrc1.Data[1] * VecSrc2.Data[2] - VecSrc1.Data[2] * VecSrc2.Data[1];
	VecDst->Data[1] = VecSrc1.Data[2] * VecSrc2.Data[0] - VecSrc1.Data[0] * VecSrc2.Data[2];
	VecDst->Data[2] = VecSrc1.Data[0] * VecSrc2.Data[1] - VecSrc1.Data[1] * VecSrc2.Data[0];
}

//向量相乘求值
//R=Vec1*Vec2
Real  BL_VecXVec(VEC Vec1,  VEC Vec2)
{
	S32 i;
	Real r = 0;
	for(i = 0; i < Vec1.Dim && i < Vec2.Dim; i++)
	{
		r += Vec1.Data[i] * Vec2.Data[i];
	}
	return r;
}

//求多项式值(高次系数在前)
//aX^2+bX+c...
Real BL_VecCalcEq(VEC* Vec, Real X)
{
	S32 i;
	Real r = 0;
	Real x = 1;
	for(i = 0; i < Vec->Dim; i++)
	{
		r += Vec->Data[Vec->Dim-1-i] * x;
		x *= X;
	}
	return r;
}

//向量值求和
Real BL_VecSumValue(VEC vec)
{
	U16 i;
	Real value = 0;
	for(i = 0; i < vec.Dim; i++)
		value += vec.Data[i];
	return value;
}

//建立矩阵(自动分配位置)
MAT BL_MatCreate(U16 M, U16 N)
{
	U16 i;
	MAT mat;
	mat.M = M;
	mat.N = N;
	mat.Data = (Real**)_BL_MatrixMemAllocate(M * sizeof(Real*));
	mat.Base = (Real*)_BL_MatrixMemAllocate(M * N * sizeof(Real));
	memset(mat.Base, 0, M * N * sizeof(Real));
	for(i = 0; i < M; i++)
		mat.Data[i] = mat.Base + i * N;
	return mat;
}

//建立矩阵(手动分配位置)
void BL_MatAllocate(MAT* Mat, U16 M, U16 N)
{
	U16 i;
	Mat->M = M;
	Mat->N = N;
	Mat->Data = (Real**)_BL_MatrixMemAllocate(M * sizeof(Real*));
	Mat->Base = (Real*)_BL_MatrixMemAllocate(M * N * sizeof(Real));
	memset(Mat->Base, 0, M * N * sizeof(Real));
	for(i = 0; i < M; i++)
		Mat->Data[i] = Mat->Base + i * N;
}

//空返回FALSE
U8 BL_IsMatUnEmpty(MAT* Mat)
{
	if(Mat->M + Mat->N < 2)
		return False;
	else
		return True;
}

//回收矩阵数据空间
void BL_MatFree(MAT* Mat)
{
	free(Mat->Data);
	free(Mat->Base);
	Mat->M = 0;
	Mat->N = 0;
}

//把矩阵里面所有的值设为同一值
U8 BL_MatSetValue(MAT* Mat, Real Value)
{
	U16 i, j;
#if EXCEPTION
	if(BL_IsMatUnEmpty(Mat) == False)
		return False;
#endif
	for(i = 0; i < Mat->M; i++)
		for(j = 0; j < Mat->N; j++)
			Mat->Data[i][j] = Value;
	return True;
}

//复制矩阵
//MatDst = MatSrc
U8 BL_MatCopy(MAT* MatDst, MAT MatSrc)
{
	U16 i;
#if EXCEPTION
	if(MatDst->M != MatSrc.M || MatDst->N != MatSrc.N)
	{
		return False;
	}
#endif
	for(i = 0; i < MatDst->M; i++)
		memcpy((void*)MatDst->Data[i], (void*)MatSrc.Data[i], MatSrc.N * sizeof(Real));
	return True;
}

//把MatSrc矩阵复制到MatDst[a][b]处
U8 BL_MatIndexCopy(MAT* MatDst, U16 A, U16 B, MAT MatSrc)
{
	U16 i;
#if EXCEPTION
	if(MatDst->M < (A + MatSrc.M) || MatDst->N < (B + MatSrc.N))
	{
		return False;
	}
#endif
	for(i = 0; i < MatSrc.M; i++)
		memcpy((void*)&(MatDst->Data[i+A][B]), (void*)MatSrc.Data[i], MatSrc.N * sizeof(Real));
	return True;
}

//设Mat的每一列为Vec
U8 BL_MatRowSetVec(MAT* Mat, VEC Vec)
{
	U16 i, j;
#if EXCEPTION
	if(BL_IsMatUnEmpty(Mat) == False || Vec.Dim != Mat->M)
	{
		//SendMessage('A', "MatRowSetVecError!\n");
		return False;
	}
#endif
	for(i = 0; i < Mat->M; i++)
		for(j = 0; j < Mat->N; j++)
			Mat->Data[i][j] = Vec.Data[i];
	return True;
}

//把Mat设为对角阵Mat[i][i] = value
U8 BL_MatEye(MAT* Mat, Real Value)
{
	U16 i, j;
#if EXCEPTION
	if(Mat->M != Mat->N)
	{
		return False;
	}
#endif
	for(i = 0; i < Mat->M; i++)
		for(j = 0; j < Mat->N; j++)
		{
			if(i == j)
				Mat->Data[i][j] = Value;
			else
				Mat->Data[i][j] = 0;
		}
	return True;
}

//求矩阵的转置
//MatDst = (MatSrc)T
U8 BL_MatTran(MAT* MatDst, MAT MatSrc)
{
	U8 i, j;
#if EXCEPTION
	if(MatDst->M != MatSrc.N || MatDst->N != MatSrc.M)
	{
		return False;
	}
#endif
	for(i = 0; i < MatSrc.M; i++)
	{
		for(j = 0; j < MatSrc.N; j++)
			MatDst->Data[j][i] = MatSrc.Data[i][j];
	}
	return True;
}

//矩阵相加
//MatDst = MatSrc1 + MatSrc2
U8 BL_MatAdd(MAT* MatDst, MAT MatSrc1, MAT MatSrc2)
{
	U8 i, j;

#if EXCEPTION
	if(BL_IsMatUnEmpty(&MatSrc1) + BL_IsMatUnEmpty(&MatSrc2) + BL_IsMatUnEmpty(MatDst) != 3)
	{
		return False;
	}
#endif
	if(MatSrc2.Property == 1)
	{
		for(i = 0; i < MatSrc1.M; i++)
			MatDst->Data[i][i] = MatSrc1.Data[i][i] + MatSrc2.Data[i][i];
	}
	else
	{
		for(i = 0; i < MatSrc1.M; i++)
			for(j = 0; j < MatSrc1.N; j++)
				MatDst->Data[i][j] = MatSrc1.Data[i][j] + MatSrc2.Data[i][j];
	}
	return True;
}

//矩阵相减
//MatDst = MatSrc1 - MatSrc2
U8 BL_MatSub(MAT* MatDst, MAT MatSrc1, MAT MatSrc2)
{
	U8 i, j;

#if EXCEPTION
	if(BL_IsMatUnEmpty(&MatSrc1) + BL_IsMatUnEmpty(&MatSrc2) + BL_IsMatUnEmpty(MatDst) != 3)
	{
		//SendMessage('A', "MatMinError!\n");
		return False;
	}
#endif

	for(i = 0; i < MatSrc1.M; i++)
		for(j = 0; j < MatSrc1.N; j++)
			MatDst->Data[i][j] = MatSrc1.Data[i][j] - MatSrc2.Data[i][j];
	return True;
}

//矩阵求逆
//MatDst = inv(MatSrc)
//MatTemp为操作用临时阵要保证足够大
U8 BL_MatInv(MAT* MatDst, MAT MatSrc, MAT MatTemp)
{
	U16 i, j, k;
	Real lMax, temp;
	U16 tempM, tempN;
	//	if(InvFlag == 0)
	//	{
	//		MatTemp= BL_MatCreate(20,20);
	//		InvFlag = 1;
	//	}
#if EXCEPTION

#endif
	tempM = MatTemp.M;
	tempN = MatTemp.N;
	MatTemp.M = MatSrc.M;
	MatTemp.N = MatSrc.N;
	BL_MatCopy(&MatTemp, MatSrc);

	BL_MatEye(MatDst, 1.0);
	for(i = 0; i < MatSrc.M; i++)
	{
		//寻找主元
		lMax = MatTemp.Data[i][i];
		k = i;
		for(j = i + 1; j < MatSrc.M; j++) //扫描从i+1到n的各行
		{
			if( fabs(MatTemp.Data[j][i]) > fabs(lMax))
			{
				lMax = MatTemp.Data[j][i];
				k = j;
			}
		}
		//如果主元所在行不是第i行，进行行交换
		if(k != i)
		{
			for(j = 0; j < MatSrc.M; j++)
			{
				temp = MatTemp.Data[i][j] ;
				MatTemp.Data[i][j] = MatTemp.Data[k][j];
				MatTemp.Data[k][j] = temp;
				//mat1伴随计算
				temp = MatDst->Data[i][j];
				MatDst->Data[i][j] = MatDst->Data[k][j];
				MatDst->Data[k][j] = temp;
			}
		}
		//判断主元是否是0，如果是，则矩阵mat2不是满秩矩阵，不存在逆矩阵
		if(MatTemp.Data[i][i] == 0)
		{
			//BL_MatFree(&MatTemp);
			//SendMessage('A', "MatInvError!\n");
			return False;
		}
		//消去mat2的第i列除去i行以外的各行元素
		temp = MatTemp.Data[i][i];
		for(j = 0; j < MatSrc.M; j++)
		{
			MatTemp.Data[i][j] = MatTemp.Data[i][j] / temp; //主对角线上元素变成1
			MatDst->Data[i][j] = MatDst->Data[i][j] / temp; //伴随计算
		}

		for(j = 0; j < MatSrc.M; j++) //行 0 -> n
		{
			if(j != i) //不是第i行
			{
				temp = MatTemp.Data[j][i];
				for(k = 0; k < MatSrc.M; k++) // j行元素 - i行元素* j行i列元素
				{
					MatTemp.Data[j][k] = MatTemp.Data[j][k] - MatTemp.Data[i][k] * temp;
					MatDst->Data[j][k] = MatDst->Data[j][k] - MatDst->Data[i][k] * temp;
				}
			}
		}
	}
	//	BL_MatFree(&MatTemp);
	MatTemp.M = tempM;
	MatTemp.N = tempN;
	return True;
}

//矩阵相乘
//MatDst = MatSrc1 * MatSrc2
U8 BL_MatMul(MAT* MatDst, MAT MatSrc1, MAT MatSrc2)
{
	U8 i, j, k;
	Real temp = 0;
#if EXCEPTION
	if(MatSrc1.N != MatSrc2.M || MatDst->M != MatSrc1.M || MatDst->N != MatSrc2.N)
	{
		return False;
	}
#endif

	for(i = 0; i < MatSrc1.M; i++)
		for(j = 0; j < MatSrc2.N; j++)
		{
			temp = 0;
			for(k = 0; k < MatSrc1.N; k++)
				temp += MatSrc1.Data[i][k] * MatSrc2.Data[k][j];
			MatDst->Data[i][j] = temp;
		}
	return True;
}

//矩阵乘以实数
//MatDst = MatSrc * Value
U8 BL_MatXReal(MAT* MatDst, MAT MatSrc, Real Value)
{
	U8 i, j;
#if EXCEPTION

#endif
	for(i = 0; i < MatSrc.M; i++)
		for(j = 0; j < MatSrc.N; j++)
			MatDst->Data[i][j] = Value  * MatSrc.Data[i][j];
	return True;
}

//矩阵乘以实数
//Mat = Mat * Value
U8 BL_MatSelfXReal(MAT* Mat, Real Value)
{
	U8 i, j;
#if EXCEPTION

#endif
	for(i = 0; i < Mat->M; i++)
		for(j = 0; j < Mat->N; j++)
			Mat->Data[i][j] = Value  * Mat->Data[i][j];
	return True;
}

//矩阵乘以向量
//VecDst = MatSrc * Vec
U8 BL_MatXVec(VEC* VecDst, MAT MatSrc, VEC VecSrc)
{
	U8 i, j;
	Real temp;
#if EXCEPTION
	if(MatSrc.N != VecSrc.Dim)
	{
		return False;
	}
#endif
	for(i = 0; i < MatSrc.M; i++)
	{
		temp = 0;
		for(j = 0; j < MatSrc.N; j++)
			temp += MatSrc.Data[i][j] * VecSrc.Data[j];
		VecDst->Data[i] = temp;
	}
	return True;
}

//向量乘以矩阵
//VecDst = VecSrc * MatSrc
U8 BL_VecXMat(VEC* VecDst, VEC VecSrc, MAT MatSrc)
{
	U8 i, j;
	Real temp;
#if EXCEPTION
	if(MatSrc.M != VecSrc.Dim)
	{
		return False;
	}
#endif
	for(j = 0; j < MatSrc.N; j++)
	{
		temp = 0;
		for(i = 0; i < VecSrc.Dim; i++)
			temp += VecSrc.Data[i] * MatSrc.Data[i][j];
		VecDst->Data[j] = temp;
	}
	return True;
}

//绑定地址为指定矩阵的指定子位置
U8 BL_MatBindAddress(MAT* MatDst, U16 MNew, U16 NNew, MAT MatSrc, U16 MStart, U16 NStart)
{
	U16 i;
#if EXCEPTION

#endif
	MatDst->M = MNew;
	MatDst->N = NNew;
	for(i = 0; i < MatDst->M; i++)
		MatDst ->Data[i] = &(MatSrc.Data[MStart+i][NStart]);
	return True;
}

//转化为对称矩阵
U8 BL_MatSetSym(MAT* Mat)
{
	U16 i, j;
#if EXCEPTION

#endif
	for(i = 0; i < Mat->M; i++)
	{
		for(j = i; j < Mat->N; j++)
		{
			if(Mat->Data[i][j] != Mat->Data[j][i])//TODO:Del
				Mat->Data[j][i] = Mat->Data[i][j];
		}
	}
	return True;
}

//将非对角线上的数据清零
U8 BL_MatSetEye(MAT* Mat)
{
	U16 i, j;
#if EXCEPTION

#endif
	for(i = 0; i < Mat->M; i++)
	{
		for(j = 0; j < Mat->N; j++)
		{
			if(i != j)
				Mat->Data[i][j] = 0;
		}
	}
	return True;
}

//求矩阵数值和
Real BL_MatSumValue(MAT Mat)
{
	U16 i, j;
	Real value = 0;
#if EXCEPTION

#endif
	for(i = 0; i < Mat.M; i++)
		for(j = 0; j < Mat.N; j++)
			value += Mat.Data[i][j];
	return value;
}

