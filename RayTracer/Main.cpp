#include <iostream>

#include "../General/Vector3.h"
#include "../General/Color.h"
#include "../General/Ray.h"

int main()
{
	// Target Image.
	const double aspectRatio = 16.0 / 9.0;
	const int imageWidth = 2560;
	const int imageHeight = imageWidth / aspectRatio;

	// Camera`s properties.
	double viewportHeight = 2.0;
	double viewportWidth = aspectRatio * viewportHeight;
	double focalLength = 1.0;

	Vector3 origin(0.0);
	Vector3 horizontal = Vector3(viewportWidth, 0, 0);
	Vector3 vertical = Vector3(0, viewportHeight, 0);
	Vector3 lowerLeftCornerPoint = origin - horizontal / 2 - vertical / 2 - Vector3(0, 0, focalLength);

	// Render.
	std::cout << "P3\n" << imageWidth << " " << imageHeight << "\n255\n";
	for (double j = imageHeight - 1; j >= 0; j--)
	{
		std::cerr << "\rScan lines remaining: " << j << ' ' << std::flush;
		for (double i = 0; i < imageWidth; i++)
		{
			auto u = i / imageWidth;
			auto v = j / imageHeight;
			Ray ray(origin, lowerLeftCornerPoint + u * horizontal + v * vertical - origin);
			std::cout << ray.GetColor() << std::endl;
		}
	}
}