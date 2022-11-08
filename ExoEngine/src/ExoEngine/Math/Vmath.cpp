#include "Vmath.h"


namespace EM
{
	vec2D::vec2D()///defualt cotr
	{
		x = 0.0f;
		y = 0.0f;
	}

	vec2D::vec2D(float _x, float _y)
	{
		x = _x;
		y = _y;
		
	}

	

	//operators
	vec2D vec2D::operator += (const vec2D& rhs) ///function to add vector together
	{
		x += rhs.x;
		y += rhs.y;

		return *this;
	}


	vec2D vec2D::operator -= (const vec2D& rhs)/// function to subtract vectors
	{
		{
			x -= rhs.x;
			y -= rhs.y;

			return *this;
		}
		
	}
	vec2D  vec2D::operator *= (const vec2D& rhs) ///function to multiply vectors
	{
		x *= rhs.x;
		y *= rhs.y;

		return *this;
	}
	vec2D  vec2D::operator /= (const vec2D& rhs) ///functions to divide vectors
	{
		x /= rhs.x;
		y /= rhs.y;

		return *this;
	}

	vec2D vec2D::operator = (const vec2D& lhs)
	{
		x = lhs.x;
		y = lhs.y;
		return *this;
	}

	vec2D& vec2D::operator+=(float& rhs)
	{
		x += rhs;
		y += rhs;
		return *this;
	}

	vec2D& vec2D::operator-=(float& rhs)
	{
		x -= rhs;
		y -= rhs;
		return *this;
	}


	vec2D  vec2D::operator -() const /// function to make vector into negative
	{
		return vec2D(-x, -y);
	}

	vec2D operator + (const vec2D& lhs, const vec2D& rhs)///adding 2 vector together
	{
		return vec2D(lhs.x + rhs.x, lhs.y + rhs.y);// return a vector created by the elements from computing the sum of each individual elements of the vector

	}
	vec2D operator - (const vec2D& lhs, const vec2D& rhs) ///subtractiong 2 vector
	{
		return vec2D(lhs.x - rhs.x, lhs.y - rhs.y);//return a vector created by the elements from computing the diffrence of each
	}

	vec2D operator * (const vec2D& lhs, float rhs) ///multiplying 2 vector
	{
		return vec2D(lhs.x * rhs, lhs.y * rhs);//return a vector created by the elements that result from the multiplication of the lhs vector 
												  // and the rhs float
	}

	vec2D operator*(float lhs, const vec2D& rhs) ///multiplying a vector with a float
	{
		return vec2D(rhs.x * lhs, rhs.y * lhs);//return a vector created by the elements that result from the multiplication of the rhs vector 
												  // and the lhs float
	}

	vec2D operator / (const vec2D& lhs, float rhs) ///dividing a float from a vector
	{
		return vec2D(lhs.x / rhs, lhs.y / rhs);//return a vector created by the elements that result from the division of the lhs vector with the rhs float
	}

	// Tool functions
	void Vec2Set(vec2D& curr, float x_, float y_) ///set value for current vector
	{
		curr.x = x_;
		curr.y = y_;
	}


	void  Normalize(vec2D& result, const vec2D Vec0)///normaize the current vector
	{
		float mag = sqrtf((Vec0.x * Vec0.x) + (Vec0.y * Vec0.y));
		result.x = Vec0.x / mag;
		result.y = Vec0.y / mag;
	}//normalize the vector

	float  length(const vec2D& Vec0) ///calculate the length of the vector
	{
		return (float)(sqrt(powf(Vec0.x, 2.0f) + powf(Vec0.y, 2.0f)));
	}

	float  squarelength(const vec2D& Vec0) ///calculate the square length of the vector 
	{
		return (float)(powf(Vec0.x, 2.0f) + powf(Vec0.y, 2.0f));
	}

	float  distance(const vec2D& vec_p0, const vec2D& vec_p1) ///find the distance between 2 point
	{
		vec2D temp = vec_p1 - vec_p0;//find the vector between the 2 point

		return length(temp);
	}

	float  squaredistance(const vec2D& vec_p0, const vec2D& vec_p1) ///find the square distance between 2 point
	{
		vec2D temp = vec_p1 - vec_p0;//find the vector between the 2 point

		return powf(length(temp),2.0f);

	}

	float  dotProduct(const vec2D& Vec0, const vec2D& Vec1) ///calculate the dot product of 2 vectors
	{
		return (Vec0.x * Vec1.x + Vec0.y * Vec1.y);
	}

	float  crossproduct(const vec2D& Vec0, const vec2D& Vec1) ///calculate the cross product between 2 vectors
	{
		return (Vec0.x * Vec1.y - Vec0.y * Vec1.x);
	}

	vec2D   ADV_OrthProj(const vec2D& Vec0, const vec2D& Vec1)
	{
		float dot_prod = dotProduct(Vec0, Vec1);
		float Vec1_length = squaredistance(Vec0, Vec1);
		float temp = dot_prod / Vec1_length;
		return (temp * Vec1);
	}

}