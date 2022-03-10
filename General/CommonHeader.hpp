//
// Created by bunny on 3/9/22.
//

#ifndef RAYTRACINGINONEWEEKEND_COMMONHEADER_HPP
#define RAYTRACINGINONEWEEKEND_COMMONHEADER_HPP

#include <cmath>
#include <limits>
#include <memory>
#include <random>

#include "Vector3.h"
#include "Ray.h"

const double Infinity = std::numeric_limits<double>::infinity();
const double Pi = 3.1415926535897932385;

class RabbitUtility
{
public:
	static double DegreeToRadian(double degree)
	{
		return degree * Pi / 180.0;
	}

	static double Random(double min = 0.0, double max = 1.0)
	{
		static std::random_device randomDevice;
		static std::mt19937 generator(randomDevice());
		static std::uniform_real_distribution<double> distribution(min, max);
		return distribution(generator);
	}

	static double Clamp(double number, double min, double max)
	{
		// Return the inclusive value, not interpolation.
		if (number < min)return min;
		if (number > max)return max;
		return number;
	}
};

#endif //RAYTRACINGINONEWEEKEND_COMMONHEADER_HPP
