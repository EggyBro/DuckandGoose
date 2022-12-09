#pragma once

#include <iostream>
#include <math.h>
#include "empch.h"

namespace EM
{
	class Vec3
	{
	public:
		float x{ 0 };
		float y{ 0 };
		float z{ 0 };



		//float m[2];

		Vec3();//default ctor
		Vec3(float _x, float _y, float _z); //para_Ctor

		//operators
		Vec3 operator += (const Vec3& rhs);
		Vec3 operator -= (const Vec3& rhs);
		Vec3 operator *= (const Vec3& rhs);
		Vec3 operator /= (const Vec3& rhs);
		Vec3 operator = (const Vec3& lhs);
		Vec3& operator += (float& rhs);
		Vec3& operator -= (float& rhs);

		Vec3 operator -() const;

		void Vec2Set(Vec3& curr, float x_, float y_, float z_);


		//tools


		//MATH function
		static void Normalize(Vec3& result, const Vec3 Vec0); //normalize the vector

		static float length(const Vec3& Vec0); // return the length of the vector 

		static float squarelength(const Vec3& Vec0);//return the length of the vector after squaring it

		static float distance(const Vec3& vec_p0, const Vec3& vec_p1);// find the distance 2 2D vector that are being treated as point 

		static float squaredistance(const Vec3& vec_p0, const Vec3& vec_p1);

		static float dotProduct(const Vec3& Vec0, const Vec3& Vec1);

		static Vec3 crossproduct(const Vec3& Vec0, const Vec3& Vec1);

		

	};

	Vec3 operator - (const Vec3& lhs, const Vec3& rhs);
	Vec3 operator + (const Vec3& lhs, const Vec3& rhs);
	Vec3 operator * (const Vec3& lhs, float rhs);
	Vec3 operator * (float lhs, const Vec3& rhs);
	Vec3 operator / (const Vec3& lhs, float rhs);



}