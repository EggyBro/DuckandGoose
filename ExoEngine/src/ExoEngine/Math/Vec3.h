#pragma once

#include <iostream>
#include <math.h>
#include "empch.h"
#include "Vec4.h"

#pragma warning( disable : 4201 )
namespace EM
{

	
	 union Vec3
	{
		struct {
			float x;
			float y;
			float z;
		};



		float m[3]{0,0,0};

		Vec3();//default ctor
		Vec3(float _x, float _y, float _z); //para_Ctor

		//operators
		Vec3 operator += (const Vec3& rhs);
		Vec3 operator -= (const Vec3& rhs);
		Vec3 operator *= (const Vec3& rhs);
		Vec3 operator /= (const Vec3& rhs);
		Vec3 operator = (const Vec3& lhs);
		Vec3 operator = (const Vec4& lhs);
		Vec3& operator += (float& rhs);
		Vec3& operator -= (float& rhs);

		Vec3 operator -() const;

		void Vec2Set(Vec3& curr, float x_, float y_, float z_);
	};

	Vec3 operator - (const Vec3& lhs, const Vec3& rhs);
	Vec3 operator + (const Vec3& lhs, const Vec3& rhs);
	Vec3 operator * (const Vec3& lhs, float rhs);
	Vec3 operator * (float lhs, const Vec3& rhs);
	Vec3 operator / (const Vec3& lhs, float rhs);
	void Normalize(Vec3& result, const Vec3 Vec0); //normalize the vector

	float length(const Vec3& Vec0); // return the length of the vector 

	float squarelength(const Vec3& Vec0);//return the length of the vector after squaring it

	float distance(const Vec3& vec_p0, const Vec3& vec_p1);// find the distance 2 3D vector that are being treated as point 

	float squaredistance(const Vec3& vec_p0, const Vec3& vec_p1);

	float dotProduct(const Vec3& Vec0, const Vec3& Vec1);

	Vec3 crossproduct(const Vec3& Vec0, const Vec3& Vec1);




}