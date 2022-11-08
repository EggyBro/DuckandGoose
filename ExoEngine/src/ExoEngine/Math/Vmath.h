#pragma once

#include <iostream>
#include <math.h>
#include "empch.h"

namespace EM
{
#ifdef _MSC_VER
	// Supress warning: nonstandard extension used : nameless struct/union
#pragma warning( disable : 4201 )
#endif
	typedef union vec2D
	{
		struct {
			float x;
			float y;
		};


		float m[2];

		vec2D();//default ctor
		vec2D(float _x, float _y); //para_Ctor

		//operators
		vec2D operator += (const vec2D& rhs);
		vec2D operator -= (const vec2D& rhs);
		vec2D operator *= (const vec2D& rhs);
		vec2D operator /= (const vec2D& rhs);
		vec2D operator = (const vec2D& lhs);
		vec2D& operator += (float& rhs);
		vec2D& operator -= (float& rhs);

		vec2D operator -() const;

		void Vec2Set(vec2D& curr, float x_, float y_);


		//tools


		//MATH function
		

	}Vector2D;

	vec2D operator - (const vec2D& lhs, const vec2D& rhs);
	vec2D operator + (const vec2D& lhs, const vec2D& rhs);
	vec2D operator * (const vec2D& lhs, float rhs);
	vec2D operator * (float lhs, const vec2D& rhs);
	vec2D operator / (const vec2D& lhs, float rhs);
	 void Normalize(vec2D& result, const vec2D Vec0); //normalize the vector

	 float length(const vec2D& Vec0); // return the length of the vector 

	float squarelength(const vec2D& vec0);//return the length of the vector after squaring it

	float distance(const vec2D& vec_p0, const vec2D& vec_p1);// find the distance 2 2D vector that are being treated as point 

	float squaredistance(const vec2D& vec_p0, const vec2D& vec_p1);

	float dotProduct(const vec2D& Vec0, const vec2D& Vec1);

	float crossproduct(const vec2D& Vec0, const vec2D& Vec1);

	vec2D  ADV_OrthProj(const vec2D& Vec0, const vec2D& Vec1);



}