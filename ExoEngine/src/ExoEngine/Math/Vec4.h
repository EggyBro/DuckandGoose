#pragma once

#include <iostream>
#include <math.h>
#include "empch.h"

#pragma warning( disable : 4201 )
namespace EM
{


	 union Vec4
	{
		struct {
			float x;
			float y;
			float z;
			float w;
			
		};



		float m[4];

		Vec4();//default ctor
		Vec4(float _x, float _y, float _z, float _w); //para_Ctor

		//operators
		Vec4 operator += (const Vec4& rhs);
		Vec4 operator -= (const Vec4& rhs);	
		Vec4 operator *= (const Vec4& rhs);
		Vec4 operator /= (const Vec4& rhs);
		Vec4 operator = (const Vec4& lhs);
		Vec4& operator += (float& rhs);
		Vec4& operator -= (float& rhs);

		Vec4 operator -() const;

		void Vec4Set(Vec4& curr, float x_, float y_, float z_, float w_	);
	};

	Vec4 operator - (const Vec4& lhs, const Vec4& rhs);
	Vec4 operator + (const Vec4& lhs, const Vec4& rhs);
	Vec4 operator * (const Vec4& lhs, float rhs);
	Vec4 operator * (float lhs, const Vec4& rhs);
	Vec4 operator / (const Vec4& lhs, float rhs);
}