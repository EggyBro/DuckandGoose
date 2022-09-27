#include "matrix3D.h"

namespace EM
{
	Mat3D::Mat3D() :value{ 0.0f, 0.0f, 0.0f ,
								   0.0f, 0.0f, 0.0f ,
								   0.0f, 0.0f, 0.0f }
	{}

	Mat3D::Mat3D(const float* pArray) : value{ pArray[0], pArray[1], pArray[2],
													  pArray[3], pArray[4], pArray[5],
													  pArray[3], pArray[4], pArray[5], } {}///initialized each data of the matrix 

	Mat3D::Mat3D(float _00, float _01, float _02,
		float _10, float _11, float _12,
		float _20, float _21, float _22) :
		value{ _00, _01, _02,
			   _10, _11, _12,
			   _20, _21, _22 }
	{} ///initialized each data of the matrix to the respective float given

	Mat3D& Mat3D::operator=(const Mat3D& rhs) //copy ctor
	{
		value.m00 = rhs.value.m00;
		value.m01 = rhs.value.m01;
		value.m02 = rhs.value.m02;
		value.m10 = rhs.value.m10;
		value.m11 = rhs.value.m11;
		value.m12 = rhs.value.m12;
		value.m20 = rhs.value.m20;
		value.m21 = rhs.value.m21;
		value.m22 = rhs.value.m22;
		return *this;
	}

	Mat3D& Mat3D::operator*=(const Mat3D& rhs) ///multiply the matrix
	{
		Mat3D temp;
		temp.value.m00 = (value.m00 * rhs.value.m00) + (value.m01 * rhs.value.m10) + (value.m02 * rhs.value.m20);
		temp.value.m01 = (value.m00 * rhs.value.m01) + (value.m01 * rhs.value.m11) + (value.m02 * rhs.value.m21);
		temp.value.m02 = (value.m00 * rhs.value.m02) + (value.m01 * rhs.value.m12) + (value.m02 * rhs.value.m22);

		temp.value.m10 = (value.m10 * rhs.value.m00) + (value.m11 * rhs.value.m10) + (value.m12 * rhs.value.m20);
		temp.value.m11 = (value.m10 * rhs.value.m01) + (value.m11 * rhs.value.m11) + (value.m12 * rhs.value.m21);
		temp.value.m12 = (value.m10 * rhs.value.m02) + (value.m11 * rhs.value.m12) + (value.m12 * rhs.value.m22);

		temp.value.m20 = (value.m20 * rhs.value.m00) + (value.m21 * rhs.value.m10) + (value.m22 * rhs.value.m20);
		temp.value.m21 = (value.m20 * rhs.value.m01) + (value.m21 * rhs.value.m11) + (value.m22 * rhs.value.m21);
		temp.value.m22 = (value.m20 * rhs.value.m02) + (value.m21 * rhs.value.m12) + (value.m22 * rhs.value.m22);

		return *this = temp;
	}

	Mat3D operator*(const Mat3D& lhs, const Mat3D& rhs) ///multiply 2 matrix using the * operator
	{
		Mat3D temp;

		temp.value.m00 = lhs.value.m00 * rhs.value.m00 + lhs.value.m01 * rhs.value.m10 + lhs.value.m02 * rhs.value.m20;
		temp.value.m01 = lhs.value.m00 * rhs.value.m01 + lhs.value.m01 * rhs.value.m11 + lhs.value.m02 * rhs.value.m21;
		temp.value.m02 = lhs.value.m00 * rhs.value.m02 + lhs.value.m01 * rhs.value.m12 + lhs.value.m02 * rhs.value.m22;

		temp.value.m10 = lhs.value.m10 * rhs.value.m00 + lhs.value.m11 * rhs.value.m10 + lhs.value.m12 * rhs.value.m20;
		temp.value.m11 = lhs.value.m10 * rhs.value.m01 + lhs.value.m11 * rhs.value.m11 + lhs.value.m12 * rhs.value.m21;
		temp.value.m12 = lhs.value.m10 * rhs.value.m02 + lhs.value.m11 * rhs.value.m12 + lhs.value.m12 * rhs.value.m22;

		temp.value.m20 = lhs.value.m20 * rhs.value.m00 + lhs.value.m21 * rhs.value.m10 + lhs.value.m22 * rhs.value.m20;
		temp.value.m21 = lhs.value.m20 * rhs.value.m01 + lhs.value.m21 * rhs.value.m11 + lhs.value.m22 * rhs.value.m21;
		temp.value.m22 = lhs.value.m20 * rhs.value.m02 + lhs.value.m21 * rhs.value.m12 + lhs.value.m22 * rhs.value.m22;

		return temp;
	}

	vec2D  operator * (const Mat3D& pMtx, const vec2D& rhs) ///multiply a matrix and a vector using the * operator
	{
		vec2D temp;
		temp.value.x = pMtx.value.m00 * rhs.value.x + pMtx.value.m01 * rhs.value.y + pMtx.value.m02; //find the X value and pass it into the x parameter of temp
		temp.value.y = pMtx.value.m10 * rhs.value.x + pMtx.value.m11 * rhs.value.y + pMtx.value.m12;  //find the y value and pass it into the y parameter of temp
		return temp;
	}

	void Identity(Mat3D& Result) /// turn current matrix into an identity matrix
	{
		Result.value.m00 = 1.0f;
		Result.value.m01 = 0.0f;
		Result.value.m02 = 0.0f;

		Result.value.m10 = 0.0f;
		Result.value.m11 = 1.0f;
		Result.value.m12 = 0.0f;

		Result.value.m20 = 0.0f;
		Result.value.m21 = 0.0f;
		Result.value.m22 = 1.0f;
	}

	void Translate(Mat3D& Result, float x, float y) /// turn current matrix into a translation matrix
	{
		Result.value.m00 = 1.0f;
		Result.value.m01 = 0.0f;
		Result.value.m02 = x;

		Result.value.m10 = 0.0f;
		Result.value.m11 = 1.0f;
		Result.value.m12 = y;

		Result.value.m20 = 0.0f;
		Result.value.m21 = 0.0f;
		Result.value.m22 = 1.0f;
	}

	void Scale(Mat3D& Result, float x, float y) /// turn current matrix into a scaling matrix
	{
		Result.value.m00 = x;
		Result.value.m01 = 0.0f;
		Result.value.m02 = 0.0f;

		Result.value.m10 = 0.0f;
		Result.value.m11 = y;
		Result.value.m12 = 0.0f;

		Result.value.m20 = 0.0f;
		Result.value.m21 = 0.0f;
		Result.value.m22 = 1.0f;
	}

	void RotRad(Mat3D& Result, float angle) /// turn current matrix into a rotation matrix by radian
	{
		Result.value.m00 = cosf(angle);
		Result.value.m01 = -sinf(angle);
		Result.value.m02 = 0.0f;

		Result.value.m10 = sinf(angle);
		Result.value.m11 = cosf(angle);
		Result.value.m12 = 0.0f;

		Result.value.m20 = 0.0f;
		Result.value.m21 = 0.0f;
		Result.value.m22 = 1.0f;
	}

	void RotDeg(Mat3D& Result, float angle) /// turn current matrix into a rotation matrix by degree
	{
		Result.value.m00 = cosf(angle * 3.14159265359f / 180);
		Result.value.m01 = -sinf(angle * 3.14159265359f / 180);
		Result.value.m02 = 0.0f;

		Result.value.m10 = sinf(angle * 3.14159265359f / 180);
		Result.value.m11 = cosf(angle * 3.14159265359f / 180);
		Result.value.m12 = 0.0f;

		Result.value.m20 = 0.0f;
		Result.value.m21 = 0.0f;
		Result.value.m22 = 1.0f;
	}

	void Transpose(Mat3D& Result, const Mat3D& pMtx) /// turn current matrix into a transpose matrix
	{
		Result.value.m00 = pMtx.value.m00;
		Result.value.m01 = pMtx.value.m10;
		Result.value.m02 = pMtx.value.m20;

		Result.value.m10 = pMtx.value.m01;
		Result.value.m11 = pMtx.value.m11;
		Result.value.m12 = pMtx.value.m12;

		Result.value.m20 = pMtx.value.m20;
		Result.value.m21 = pMtx.value.m21;
		Result.value.m22 = pMtx.value.m22;
	}


	void Mtx33Inverse(Mat3D* Result, float* determinant, const Mat3D& pMtx)///inverse the matrix 
	{
		Mat3D temp;

		*determinant = pMtx.value.m00 * (pMtx.value.m11 * pMtx.value.m22 - pMtx.value.m12 * pMtx.value.m21)
			- pMtx.value.m01 * (pMtx.value.m10 * pMtx.value.m22 - pMtx.value.m12 * pMtx.value.m20)
			+ pMtx.value.m02 * (pMtx.value.m10 * pMtx.value.m21 - pMtx.value.m11 * pMtx.value.m20);

		if (*determinant == 0.0f)
		{
			Result = NULL;
		}

		else
		{
			temp.value.m00 = (pMtx.value.m11 * pMtx.value.m22 - pMtx.value.m12 * pMtx.value.m21) / *determinant;
			temp.value.m01 = (pMtx.value.m21 * pMtx.value.m02 - pMtx.value.m22 * pMtx.value.m01) / *determinant;
			temp.value.m02 = (pMtx.value.m01 * pMtx.value.m12 - pMtx.value.m02 * pMtx.value.m11) / *determinant;

			temp.value.m10 = (pMtx.value.m20 * pMtx.value.m12 - pMtx.value.m10 * pMtx.value.m22) / *determinant;
			temp.value.m11 = (pMtx.value.m00 * pMtx.value.m22 - pMtx.value.m20 * pMtx.value.m02) / *determinant;
			temp.value.m12 = (pMtx.value.m10 * pMtx.value.m02 - pMtx.value.m00 * pMtx.value.m12) / *determinant;

			temp.value.m20 = (pMtx.value.m10 * pMtx.value.m21 - pMtx.value.m11 * pMtx.value.m20) / *determinant;
			temp.value.m21 = (pMtx.value.m20 * pMtx.value.m01 - pMtx.value.m00 * pMtx.value.m21) / *determinant;
			temp.value.m22 = (pMtx.value.m00 * pMtx.value.m11 - pMtx.value.m01 * pMtx.value.m10) / *determinant;

			*Result = temp;
		}
	}
}