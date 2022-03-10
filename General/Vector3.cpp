//
// Created by bunny on 3/3/22.
//

#include "Vector3.h"
#include "CommonHeader.hpp"

double Vector3::Length() const
{
	return std::sqrt(LengthSquared());
}

double Vector3::LengthSquared() const
{
	return Elements[0] * Elements[0] + Elements[1] * Elements[1] + Elements[2] * Elements[2];
}

double Vector3::operator[](size_t index) const
{
	return Elements[index];
}

double& Vector3::operator[](size_t index)
{
	return Elements[index];
}

Vector3 Vector3::operator-() const
{
	return { -Elements[0], -Elements[1], -Elements[2] };
}

Vector3& Vector3::operator=(const Vector3& theOther)
{
	Elements[0] = theOther.Elements[0];
	Elements[1] = theOther.Elements[1];
	Elements[2] = theOther.Elements[2];
	return *this;
}

Vector3& Vector3::operator+=(const Vector3& theOther)
{
	Elements[0] += theOther.Elements[0];
	Elements[1] += theOther.Elements[1];
	Elements[2] += theOther.Elements[2];
	return *this;
}

Vector3& Vector3::operator*=(const double times)
{
	Elements[0] *= times;
	Elements[1] *= times;
	Elements[2] *= times;
	return *this;
}

Vector3& Vector3::operator/=(const double times)
{
	Elements[0] /= times;
	Elements[1] /= times;
	Elements[2] /= times;
	return *this;
}

double Vector3::Dot(const Vector3& theOther)
{
	return Elements[0] * theOther.Elements[0] + Elements[1] * theOther.Elements[1] + Elements[2] * theOther.Elements[2];
}

Vector3 Vector3::Cross(const Vector3& theOther)
{
	return {
			Elements[1] * theOther.Elements[2] - Elements[2] * theOther.Elements[1],
			Elements[2] * theOther.Elements[0] - Elements[0] * theOther.Elements[2],
			Elements[0] * theOther.Elements[1] - Elements[1] * theOther.Elements[0]
	};
}

Vector3& Vector3::Normalize()
{
	return operator/=(Length());
}

Vector3 Vector3::Normalized() const
{
	return *this / Length();
}

Vector3 Vector3::Random(double min, double max)
{
	return Vector3(RabbitUtility::Random(min, max));
}

Vector3 Vector3::RandomPointInUnitSphere()
{
	while (true)
	{
		Vector3 point = Vector3::Random(-1, 1);
		if (point.LengthSquared() >= 1)
			continue;
		return point;
	}
}

void Vector3::Pow(double times)
{
	Elements[0] = std::pow(Elements[0], times);
	Elements[1] = std::pow(Elements[1], times);
	Elements[2] = std::pow(Elements[2], times);
}

std::ostream& operator<<(std::ostream& out, const Vector3& vector)
{
	return out << vector[0] << ' ' << vector[1] << ' ' << vector[2];
}

Vector3 operator+(const Vector3& one, const Vector3& theOther)
{
	return { one[0] + theOther[0], one[1] + theOther[1], one[2] + theOther[2] };
}

Vector3 operator-(const Vector3& one, const Vector3& theOther)
{
	return { one[0] - theOther[0], one[1] - theOther[1], one[2] - theOther[2] };
}

Vector3 operator*(const Vector3& one, const Vector3& theOther)
{
	return { one[0] * theOther[0], one[1] * theOther[1], one[2] * theOther[2] };
}

Vector3 operator*(const Vector3& vector, double times)
{
	return { vector[0] * times, vector[1] * times, vector[2] * times };
}

Vector3 operator*(double times, const Vector3& vector)
{
	return vector * times;
}

Vector3 operator/(const Vector3& vector, double times)
{
	return { vector[0] / times, vector[1] / times, vector[2] / times };
}