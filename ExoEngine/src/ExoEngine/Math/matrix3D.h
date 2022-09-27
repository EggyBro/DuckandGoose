#pragma once
#include "Vmath.h"

namespace EM
{
	typedef union Mat3D
	{
		struct matrix_val
		{
			float m00, m01, m02;
			float m10, m11, m12;
			float m20, m21, m22;
		} value;

		float m[9];

		Mat3D();
		Mat3D(const float* pArray);
		Mat3D(float _00, float _01, float _02,
			float _10, float _11, float _12,
			float _20, float _21, float _22);

		Mat3D& operator=(const Mat3D& rhs);

		Mat3D& operator *= (const Mat3D& rhs);
	}Mat3D, Mtx33, MTX;

	//operator 
	Mat3D operator * (const Mat3D& lhs, const Mat3D& rhs);
	vec2D  operator * (const Mat3D& pMtx, const vec2D& rhs);

	void Identity(Mat3D& pResult);
	void Translate(Mat3D& pResult, float x, float y);
	void Scale(Mat3D& pResult, float x, float y);
	void RotRad(Mat3D& pResult, float angle);
	void RotDeg(Mat3D& pResult, float angle);
	void Transpose(Mat3D& pResult, const Mat3D& pMtx);
	void Mtx33Inverse(Mat3D* pResult, float* determinant, const Mat3D& pMtx);



}