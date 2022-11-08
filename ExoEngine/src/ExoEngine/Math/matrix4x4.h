#pragma once
#include "Vmath.h"
#include "empch.h"
#include "Vec3.h"
#include <glm/gtc/matrix_transform.hpp>

namespace EM
{
	typedef union Mat4x4
	{
		struct 
		{

			float m00, m01, m02, m03,
			m10, m11, m12, m13,
			 m20, m21, m22, m23,
			 m30, m31, m32, m33;
		};

		float m[4][4];

		Mat4x4();
		Mat4x4(float _00, float _01, float _02, float _03,
			   float _10, float _11, float _12, float _13,
			   float _20, float _21, float _22, float _23,
			   float _30, float _31, float _32, float _33);

		Mat4x4(const float value);

		Mat4x4& operator=(const Mat4x4& rhs);

		Mat4x4& operator*= (const Mat4x4& rhs);
		

		
	}Matrix4x4;
	 void Identity4x4(Mat4x4& pResult);
	 void Translate4x4(Mat4x4& pResult, float x, float y, float z);
	 void Scale4x4(Mat4x4& pResult, float x, float y, float z);

	 void XRotRad4x4(Mat4x4& Result, float angle);
	 void YRotRad4x4(Mat4x4& Result, float angle);
	 void ZRotRad4x4(Mat4x4& Result, float angle);

	 void RotRad4x4(Mat4x4& Result, float angle, Vec3 dir);
	 void RotRad4x4(Mat4x4& Result, Vec3 rhs);

	 void XRotDeg4x4(Mat4x4& Result, float angle);
	 void YRotDeg4x4(Mat4x4& Result, float angle);
	 void ZRotDeg4x4(Mat4x4& Result, float angle);
	 void RotDeg4x4(Mat4x4& Result, Vec3 rhs);

	 void RotDeg4x4(Mat4x4& Result, float angle, Vec3 dir);

	 void Transpose4x4(Mat4x4& pResult, const Mat4x4& pMtx);
	 void Mtx33Inverse4x4(Mat4x4* pResult, float* determinant, const Mat4x4& pMtx);
	Mat4x4 operator * (const Mat4x4& lhs, const Mat4x4& rhs);
	Vec3 operator * (const Mat4x4& pMtx, const Vec3& rhs);

	glm::mat4 mtx_adapter(Mat4x4& rhs);

	//operator 
	



}