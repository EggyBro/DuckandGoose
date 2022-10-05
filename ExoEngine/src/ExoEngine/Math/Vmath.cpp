#include "Vmath.h"


namespace EM
{
	vec2D::vec2D() : vector{ 0,0 } ///defualt cotr
	{

	}

	vec2D::vec2D(float _x, float _y) : value{ _x, _y }///para ctor
	{
	}

	//operators
	vec2D vec2D::operator += (const vec2D& rhs) ///function to add vector together
	{
		value.x += rhs.value.x;
		value.y += rhs.value.y;

		return *this;
	}


	vec2D vec2D::operator -= (const vec2D& rhs)/// function to subtract vectors
	{
		{
			value.x -= rhs.value.x;
			value.y -= rhs.value.y;

			return *this;
		}
	}
	vec2D  vec2D::operator *= (const vec2D& rhs) ///function to multiply vectors
	{
		value.x *= rhs.value.x;
		value.y *= rhs.value.y;

		return *this;
	}
	vec2D  vec2D::operator /= (const vec2D& rhs) ///functions to divide vectors
	{
		value.x /= rhs.value.x;
		value.y /= rhs.value.y;

		return *this;
	}

	vec2D vec2D::operator = (const vec2D& lhs)
	{
		value.x = lhs.value.x;
		value.y = lhs.value.y;
		return *this;
	}

	vec2D& vec2D::operator+=(float& rhs)
	{
		value.x += rhs;
		value.y += rhs;
		return *this;
	}

	vec2D& vec2D::operator-=(float& rhs)
	{
		value.x -= rhs;
		value.y -= rhs;
		return *this;
	}


	vec2D  vec2D::operator -() const /// function to make vector into negative
	{
		return vec2D(-value.x, -value.y);
	}

	vec2D operator + (const vec2D& lhs, const vec2D& rhs)///adding 2 vector together
	{
		return vec2D(lhs.value.x + rhs.value.x, lhs.value.y + rhs.value.y);// return a vector created by the elements from computing the sum of each individual elements of the vector

	}
	vec2D operator - (const vec2D& lhs, const vec2D& rhs) ///subtractiong 2 vector
	{
		return vec2D(lhs.value.x - rhs.value.x, lhs.value.y - rhs.value.y);//return a vector created by the elements from computing the diffrence of each
	}

	vec2D operator * (const vec2D& lhs, float rhs) ///multiplying 2 vector
	{
		return vec2D(lhs.value.x * rhs, lhs.value.y * rhs);//return a vector created by the elements that result from the multiplication of the lhs vector 
												  // and the rhs float
	}

	vec2D operator*(float lhs, const vec2D& rhs) ///multiplying a vector with a float
	{
		return vec2D(rhs.value.x * lhs, rhs.value.y * lhs);//return a vector created by the elements that result from the multiplication of the rhs vector 
												  // and the lhs float
	}

	vec2D operator / (const vec2D& lhs, float rhs) ///dividing a float from a vector
	{
		return vec2D(lhs.value.x / rhs, lhs.value.y / rhs);//return a vector created by the elements that result from the division of the lhs vector with the rhs float
	}

	// Tool functions
	void Vec2Set(Vec2& curr, float x_, float y_) ///set value for current vector
	{
		curr.value.x = x_;
		curr.value.y = y_;
	}


	void Normalize(vec2D& result, const vec2D Vec0)///normaize the current vector
	{
		float mag = sqrtf((Vec0.value.x * Vec0.value.x) + (Vec0.value.y * Vec0.value.y));
		result.value.x = Vec0.value.x / mag;
		result.value.y = Vec0.value.y / mag;
	}//normalize the vector

	float length(const vec2D& Vec0) ///calculate the length of the vector
	{
		return (float)(sqrt(powf(Vec0.value.x, 2.0f) + powf(Vec0.value.y, 2.0f)));
	}

	float squarelength(const vec2D& Vec0) ///calculate the square length of the vector 
	{
		return (float)(powf(Vec0.value.x, 2.0f) + powf(Vec0.value.y, 2.0f));
	}

	float distance(const vec2D& vec_p0, const vec2D& vec_p1) ///find the distance between 2 point
	{
		vec2D temp = vec_p1 - vec_p0;//find the vector between the 2 point

		return length(temp);//return the result after running the temp value through Vector2DLength();
	}

	float squaredistance(const vec2D& vec_p0, const vec2D& vec_p1) ///find the square distance between 2 point
	{
		vec2D temp = vec_p1 - vec_p0;//find the vector between the 2 point

		return length(temp);//return the result after running the temp value through Vector2DLength();

	}

	float dotProduct(const vec2D& Vec0, const vec2D& Vec1) ///calculate the dot product of 2 vectors
	{
		return (Vec0.value.x * Vec1.value.x + Vec0.value.y * Vec1.value.y);
	}

	float crossproduct(const vec2D& Vec0, const vec2D& Vec1) ///calculate the cross product between 2 vectors
	{
		return (Vec0.value.x * Vec1.value.y - Vec0.value.y * Vec1.value.x);
	}
}