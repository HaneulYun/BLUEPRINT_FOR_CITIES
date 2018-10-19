#pragma once

template <typename T>
struct Type3
{
	union
	{
		struct
		{
			T x;
			T y;
			T z;
		};
		struct
		{
			T r;
			T g;
			T b;
		};
	};

public:
	inline Type3(T x = 0, T y = 0, T z = 0) : x(x), y(y), z(z) {}
	inline ~Type3() {};

	inline T distance() const { return sqrt(x * x + y * y + z * z); }

	inline Type3<T> operator+(const Type3<T>& rhs) { return Type3<T>{ x + rhs.x, y + rhs.y, z + rhs.z }; }
	inline Type3<T> operator-(const Type3<T>& rhs) { return Type3<T>{ x - rhs.x, y - rhs.y, z - rhs.z }; }
	inline Type3<T> operator/(const Type3<T>& rhs) { return Type3<T>{ x / rhs.x, y / rhs.y, z / rhs.z }; }
	inline Type3<T> operator*(const T& rhs) { return Type3<T>{ x * rhs, y * rhs, z * rhs }; }
	inline Type3<T> operator/(const T& rhs) { return Type3<T>{ x / rhs, y / rhs, z / rhs }; }

	inline Type3<T>& operator+=(const Type3<T>& rhs) { return *this = *this + rhs; }
	inline Type3<T>& operator-=(const Type3<T>& rhs) { return *this = *this - rhs; }
};
