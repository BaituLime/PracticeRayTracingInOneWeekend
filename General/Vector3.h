//
// Created by bunny on 3/3/22.
//

#ifndef RAYTRACINGINONEWEEKEND_VECTOR3_H
#define RAYTRACINGINONEWEEKEND_VECTOR3_H


#include <iostream>
#include <cstddef>
#include <cmath>

class Vector3
{
protected:
	double Elements[3];
public:
	Vector3() : Elements{ 0, 0, 0 }
	{
	}

	explicit Vector3(double element) : Elements{ element, element, element }
	{
	}

	explicit Vector3(double elements[3]) : Elements{ elements[0], elements[1], elements[2] }
	{
	}

	Vector3(Vector3& other) : Elements{ other[0], other[1], other[2] }
	{
	}

	Vector3(const Vector3& other) : Elements{ other[0], other[1], other[2] }
	{
	}

	Vector3(double x, double y, double z) : Elements{ x, y, z }
	{
	}

	double Length() const;
	double LengthSquared() const;

	double operator[](size_t index) const;
	double& operator[](size_t index);

	Vector3 operator-() const;
	Vector3& operator=(const Vector3& theOther);
	Vector3& operator+=(const Vector3& theOther);
	Vector3& operator*=(const Vector3& theOther);
	Vector3& operator*=(double times);
	Vector3& operator/=(double times);

	double Dot(const Vector3& theOther);
	Vector3 Cross(const Vector3& theOther);

	Vector3& Normalize();
	Vector3 Normalized() const;
	void Pow(double times);

	bool IsNearZero() const;
	Vector3 Reflect(const Vector3& normal);
	Vector3 Refract(const Vector3& normal, double refractionRate);
public:
	static Vector3 Random(double min = 0.0, double max = 1.0);
	// Used for a lazy hack of LambertianMaterial Reflection.
	static Vector3 RandomPointInUnitSphere();
	// Used for True LambertianMaterial Reflection.
	static Vector3 RandomPointOnUnitSphere();
	// Used for Hemisphere Diffuse Reflection.
	static Vector3 RandomPointInHemisphere(const Vector3& normal);
};


std::ostream& operator<<(std::ostream& out, const Vector3& vector);
Vector3 operator+(const Vector3& one, const Vector3& theOther);
Vector3 operator-(const Vector3& one, const Vector3& theOther);
Vector3 operator*(const Vector3& vector, double times);
Vector3 operator*(double times, const Vector3& vector);
Vector3 operator*(const Vector3& one, const Vector3& theOther);
Vector3 operator/(const Vector3& vector, double times);

#endif //RAYTRACINGINONEWEEKEND_VECTOR3_H
