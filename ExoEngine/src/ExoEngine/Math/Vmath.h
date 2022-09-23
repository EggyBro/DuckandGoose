#pragma once

#include<iostream>
#include <math.h>

namespace Framework
{
	typedef union vec2D
	{
		struct vec_mem {
			float x;
			float y;
		} vector, value;


		float m[2];

		vec2D();//default ctor
		vec2D(float _x, float _y); //para_Ctor

		//operators
		vec2D operator += (const vec2D& rhs);
		vec2D operator -= (const vec2D& rhs);
		vec2D operator *= (const vec2D& rhs);
		vec2D operator /= (const vec2D& rhs);
		vec2D operator = (const vec2D& lhs);

		vec2D operator -() const;

	} vec2D, Vec2, Point2D, Pt2;

	/*
	inline void StreamRead(ISerializer& stream, Vec2& v)
	{
		StreamRead(stream, v.value.x);
		StreamRead(stream, v.value.y);
	}
	*/

	//tools
	void Vec2Set(Vec2& curr, float x_, float y_);

	vec2D operator - (const vec2D& lhs, const vec2D& rhs);
	vec2D operator + (const vec2D& lhs, const vec2D& rhs);
	vec2D operator * (const vec2D& lhs, float rhs);
	vec2D operator * (float lhs, const vec2D& rhs);
	vec2D operator / (const vec2D& lhs, float rhs);


	//MATH function
	void Normalize(vec2D& result, const vec2D Vec0); //normalize the vector

	float length(const vec2D& Vec0); // return the length of the vector 

	float squarelength(const vec2D& vec0);//return the length of the vector after squaring it

	float distance(const vec2D& vec_p0, const vec2D& vec_p1);// find the distance 2 2D vector that are being treated as point 

	float squaredistance(const vec2D& vec_p0, const vec2D& vec_p1);

	float dotProduct(const vec2D& Vec0, const vec2D& Vec1);

	float crossproduct(const vec2D& Vec0, const vec2D& Vec1);
}