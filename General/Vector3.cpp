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

Vector3& Vector3::operator*=(const Vector3& theOther)
{
	Elements[0] *= theOther.Elements[0];
	Elements[1] *= theOther.Elements[1];
	Elements[2] *= theOther.Elements[2];
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
	return { RabbitUtility::Random(min, max), RabbitUtility::Random(min, max), RabbitUtility::Random(min, max) };
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

Vector3 Vector3::RandomPointOnUnitSphere()
{
	return RandomPointInUnitSphere().Normalized();
}

Vector3 Vector3::RandomPointInHemisphere(const Vector3& normal)
{
	Vector3 temp = RandomPointInUnitSphere();
	if (temp.Dot(normal) > 0.0)
		return temp;
	else
		return -temp;
}

void Vector3::Pow(double times)
{
	Elements[0] = std::pow(Elements[0], times);
	Elements[1] = std::pow(Elements[1], times);
	Elements[2] = std::pow(Elements[2], times);
}

bool Vector3::IsNearZero() const
{
	return (std::fabs(Elements[0]) < 1e-8) && (std::fabs(Elements[1]) < 1e-8) && (std::fabs(Elements[2]) < 1e-8);
}

Vector3 Vector3::Reflect(const Vector3& normal)
{
	return *this - 2 * this->Dot(normal) * normal;
}

Vector3 Vector3::Refract(const Vector3& normal, double refractionRate)
{
	double cosTheta = std::fmin((-*this).Dot(normal), 1.0);
	Vector3 outPerpendicular = refractionRate * (*this + cosTheta * normal);
	Vector3 outParallel = -std::sqrt(std::fabs(1.0 - outPerpendicular.LengthSquared())) * normal;
	return outPerpendicular + outParallel;
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