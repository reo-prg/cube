#pragma once

template<class T> class Vector2Template
{
public:
	Vector2Template();
	Vector2Template(T x, T y);
	~Vector2Template();
	T x;
	T y;

	// ������Z�q
	Vector2Template<T> & operator= (const Vector2Template<T> & vec);

	// �Y�������Z�q
	T & operator[](T i);

	// ��r���Z�q
	bool operator == (const Vector2Template<T> & vec)const;
	bool operator != (const Vector2Template<T> & vec)const;
	bool operator >= (const Vector2Template<T> & vec)const;
	bool operator >  (const Vector2Template<T> & vec)const;
	bool operator <= (const Vector2Template<T> & vec)const;
	bool operator <  (const Vector2Template<T> & vec)const;

	// �P�����Z�q
	Vector2Template<T> & operator+= (const Vector2Template<T> & vec);
	Vector2Template<T> & operator-= (const Vector2Template<T> & vec);
	Vector2Template<T> & operator*= (const Vector2Template<T> & vec);
	Vector2Template<T> & operator/= (const Vector2Template<T> & vec);

	Vector2Template<T> & operator*= (T k);
	Vector2Template<T> & operator/= (T k);

	Vector2Template<T> & operator+ (void)const;
	Vector2Template<T> & operator- (void)const;
};

// �x�N�g���̉��Z

// Vector2 + Vector2
template<class T> class Vector2Template<T> operator+(const Vector2Template<T>& u, const Vector2Template<T>& v);

// Vector2 - Vector2
template<class T> class Vector2Template<T> operator-(const Vector2Template<T>& u, const Vector2Template<T>& v);

// Vector2 * Vector
template<class T> class Vector2Template<T> operator*(const Vector2Template<T>& u, const Vector2Template<T>& v);

// Vector2 / Vector2
template<class T> class Vector2Template<T> operator/(const Vector2Template<T>& u, const Vector2Template<T>& v);

// Vector % Vector
template<class T> class Vector2Template<T> operator%(const Vector2Template<T>& u, const Vector2Template<T>& v);

// Vector2 + int
template<class T> class Vector2Template<T> operator+(const Vector2Template<T>& u, T k);

// Vector2 - int
template<class T> class Vector2Template<T> operator-(const Vector2Template<T>& u, T k);

// Vector2 * int
template<class T> class Vector2Template<T> operator*(const Vector2Template<T>& u, T k);

// int * Vector2
template<class T> class Vector2Template<T> operator*(T k, const Vector2Template<T>& u);

// Vector2 / int
template<class T> class Vector2Template<T> operator/(const Vector2Template<T>& u, T k);

// Vector2 % int
template<class T> class Vector2Template<T> operator%(const Vector2Template<T>& u, T k);

// abs(Vector2)
template<class T> class Vector2Template<T> abs(const Vector2Template<T>& u);

#include <common/dit/detail.h>
