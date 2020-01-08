#include "..\Vector2.h"

template<class T>Vector2Template<T>::Vector2Template()
{
	x = 0;
	y = 0;
}

template<class T>Vector2Template<T>::Vector2Template(T x, T y)
{
	this->x = x;
	this->y = y;
}


template<class T>Vector2Template<T>::~Vector2Template()
{
}

template<class T>
Vector2Template<T> & Vector2Template<T>::operator=(const Vector2Template & vec)
{
	x = vec.x;
	y = vec.y;
	return *this;
}

template<class T>
T & Vector2Template<T>::operator[](T i)
{
	if (i == 0)
	{
		return x;
	}
	else if (i == 1)
	{
		return y;
	}
	else
	{
		return x;
	}
}

template<class T>
bool Vector2Template<T>::operator==(const Vector2Template & vec)const
{
	return (x == vec.x) && (y == vec.y);
}

template<class T>
bool Vector2Template<T>::operator!=(const Vector2Template & vec) const
{
	return !((x == vec.x) && (y == vec.y));
}

template<class T>
bool Vector2Template<T>::operator>=(const Vector2Template & vec) const
{
	return (x >= vec.x) && (y >= vec.y);
}

template<class T>
bool Vector2Template<T>::operator>(const Vector2Template & vec) const
{
	return (x > vec.x) && (y > vec.y);
}

template<class T>
bool Vector2Template<T>::operator<=(const Vector2Template & vec) const
{
	return (x <= vec.x) && (y <= vec.y);
}

template<class T>
bool Vector2Template<T>::operator<(const Vector2Template & vec) const
{
	return (x < vec.x) && (y < vec.y);
}

template<class T>
Vector2Template<T> & Vector2Template<T>::operator+=(const Vector2Template & vec)
{
	x += vec.x;
	y += vec.y;
	return *this;
}

template<class T>
Vector2Template<T> & Vector2Template<T>::operator-=(const Vector2Template & vec)
{
	x -= vec.x;
	y -= vec.y;
	return *this;
}

template<class T>
Vector2Template<T> & Vector2Template<T>::operator*=(const Vector2Template & vec)
{
	x *= vec.x;
	y *= vec.y;
	return *this;
}

template<class T>
Vector2Template<T> & Vector2Template<T>::operator/=(const Vector2Template & vec)
{
	x /= vec.x;
	y /= vec.y;
	return *this;
}

template<class T>
Vector2Template<T> & Vector2Template<T>::operator*=(T k)
{
	x *= k;
	y *= k;
	return *this;
}

template<class T>
Vector2Template<T> & Vector2Template<T>::operator/=(T k)
{
	x /= k;
	y /= k;
	return *this;
}

template<class T>
Vector2Template<T> & Vector2Template<T>::operator+(void)const
{
	return *this;
}

template<class T>
Vector2Template<T> & Vector2Template<T>::operator-(void)const
{
	return Vector2Template<T>(-this->x, -this->y);
}

template<class T>
Vector2Template<T> operator+(const Vector2Template<T> & u, const Vector2Template<T> & v)
{
	return Vector2Template<T>(u.x + v.x , u.y + v.y);
}

template<class T>
Vector2Template<T> operator-(const Vector2Template<T> & u, const Vector2Template<T> & v)
{
	return Vector2Template<T>(u.x - v.x, u.y - v.y);
}

template<class T>
Vector2Template<T> operator*(const Vector2Template<T> & u, const Vector2Template<T> & v)
{
	return Vector2Template<T>(u.x * v.x, u.y * v.y);
}

template<class T>
Vector2Template<T> operator/(const Vector2Template<T> & u, const Vector2Template<T> & v)
{
	return Vector2Template<T>(u.x / v.x, u.y / v.y);
}

template<class T>
Vector2Template<T> operator%(const Vector2Template<T> & u, const Vector2Template<T> & v)
{
	return Vector2Template<T>(u.x % v.x, u.y % v.y);
}

template<class T>
Vector2Template<T> operator+(const Vector2Template<T> & u, T k)
{
	return Vector2Template<T>(u.x + k, u.y + k);
}

template<class T>
Vector2Template<T> operator-(const Vector2Template<T> & u, T k)
{
	return Vector2Template<T>(u.x - k, u.y - k);
}

template<class T>
Vector2Template<T> operator*(const Vector2Template<T> & u, T k)
{
	return Vector2Template<T>(u.x * k, u.y * k);
}

template<class T>
Vector2Template<T> operator*(T k, const Vector2Template<T> & u)
{
	return Vector2Template<T>(k * u.x, k * u.y);
}

template<class T>
Vector2Template<T> operator/(const Vector2Template<T> & u, T k)
{
	return Vector2Template<T>(u.x / k, u.y / k);
}

template<class T>
Vector2Template<T> operator%(const Vector2Template<T> & u, T k)
{
	return Vector2Template<T>(u.x % k, u.y % k);
}


template<class T>
Vector2Template<T> abs(const Vector2Template<T> & u)
{
	return Vector2Template<T>(abs(u.x), abs(u.y));
}
