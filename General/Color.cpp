//
// Created by bunny on 3/5/22.
//

#include "Color.h"
#include "CommonHeader.hpp"

Vector3& Color::GetData()
{
	return Data;
}

std::ostream& operator<<(std::ostream& out, Color& color)
{
	// Gamma Correction.
	color.GetData().Pow(1.0 / 1.8);

	return out << int(256.0 * RabbitUtility::Clamp(color.GetData()[0], 0.0, 0.999)) << ' '
			   << int(256.0 * RabbitUtility::Clamp(color.GetData()[1], 0.0, 0.999)) << ' '
			   << int(256.0 * RabbitUtility::Clamp(color.GetData()[2], 0.0, 0.999));
}

Color& Color::operator=(const Color& other)
{
	Data[0] = other.Data[0];
	Data[1] = other.Data[1];
	Data[2] = other.Data[2];
	return *this;
}
