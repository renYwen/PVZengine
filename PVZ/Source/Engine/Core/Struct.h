#pragma once
#include<iostream>
#include<string>



constexpr double PI = 3.1415926;




/* ��ά���� */
struct Vector2D
{
	float x, y;
	Vector2D() :x(0), y(0) {}
	Vector2D(float a, float b) :x(a), y(b) {}

	//��ȡ��������
	float Size() const
	{
		return sqrtf(x * x + y * y);
	}

	//��ȡ��λ����
	Vector2D Normalize() const
	{
		return Vector2D(x / Size(), y / Size());
	}

	//������ת��Ϊ�ַ���
	std::string ToString() const
	{
		return "(" + std::to_string((int)x) + "," + std::to_string((int)y) + ")";
	}

	//�������
	static float DotProduct(const Vector2D& v1, const Vector2D& v2)
	{
		return v1.x * v2.x + v1.y * v2.y;
	}

	//�������
	static Vector2D CrossProduct(const Vector2D& v1, const Vector2D& v2)
	{
		return { v1.y * v2.x - v1.x * v2.y, v1.x * v2.y - v1.y * v2.x };
	}

	//��ȡ��������֮��ľ���
	static float Distance(const Vector2D& a, const Vector2D& b)
	{
		return sqrtf((a.x - b.x) * (a.x - b.x) + (a.y - b.y) * (a.y - b.y));
	}

	//��תĳһ������������ת�����������λ�ǽǶȣ�
	static Vector2D RotateVector(float angle, const Vector2D& another)
	{
		double radian = PI * angle / 180;
		float fsin = float(sin(radian));
		float fcos = float(cos(radian));
		return Vector2D(another.x * fcos - another.y * fsin, another.x * fsin + another.y * fcos);
	}

	// ������ u ͶӰ������ v ���ڵ�ֱ����
	static Vector2D ProjectVector(const Vector2D& u, const Vector2D& v)
	{
		float scalar = DotProduct(u, v) / v.Size();  // ����ͶӰ��������������
		return v.Normalize() * scalar;
	}


	Vector2D operator+(const Vector2D& another)const
	{
		return Vector2D(x + another.x, y + another.y);
	}
	Vector2D operator-(const Vector2D& another)const
	{
		return Vector2D(x - another.x, y - another.y);
	}
	Vector2D& operator+=(const Vector2D& another)
	{
		x += another.x; y += another.y;
		return *this;
	}
	Vector2D& operator-=(const Vector2D& another)
	{
		x -= another.x; y -= another.y;
		return *this;
	}


	bool operator==(const Vector2D& another) const
	{
		return x == another.x && y == another.y;
	}
	bool operator!=(const Vector2D& another) const
	{
		return x != another.x || y != another.y;
	}
	Vector2D operator*(float scale) const
	{
		return Vector2D(x * scale, y * scale);
	}
	Vector2D& operator*=(float scale)
	{
		x *= scale; y *= scale;
		return *this;
	}
	Vector2D operator/(float scale) const
	{
		return Vector2D(x / scale, y / scale);
	}
	Vector2D& operator/=(float scale)
	{
		x /= scale; y /= scale;
		return *this;
	}
	Vector2D operator-() const
	{
		return Vector2D(-x, -y);
	}
	Vector2D operator*(const Vector2D& another) const
	{
		return Vector2D(x * another.x, y * another.y);
	}
	Vector2D operator/(const Vector2D& another) const
	{
		return Vector2D(x / another.x, y / another.y);
	}
};

inline std::ostream& operator<<(std::ostream& out, const Vector2D& vec)
{
	std::cout << "(" << vec.x << "," << vec.y << ")";
	return out;
}

inline Vector2D operator*(float scale, Vector2D vec)
{
	return Vector2D(vec.x * scale, vec.y * scale);
}





/* ���� */
struct Pair
{
	int x, y;
	Pair() :x(0), y(0) {}
	Pair(int x, int y) :x(x), y(y) {}
	bool operator==(const Pair& another) const
	{
		return x == another.x && y == another.y;
	}
	bool operator!=(const Pair& another) const
	{
		return x != another.x || y != another.y;
	}
};




/* ���������� */
struct Transform
{
	Vector2D position;
	float rotation;
	Vector2D scale;

	Transform() :position(0, 0), rotation(0), scale(1, 1) {}
	Transform(const Vector2D& pos, float angle, const Vector2D& scale)
		:position(pos), rotation(angle), scale(scale) {}

	Transform Indentity() const
	{
		return Transform(Vector2D(0, 0), 0, Vector2D(1, 1));
	}
};