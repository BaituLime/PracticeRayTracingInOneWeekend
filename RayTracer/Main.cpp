#include <iostream>

#include "../General/CommonHeader.hpp"
#include "../General/Color.h"
#include "../General/HitableList.h"
#include "../General/Sphere.h"
#include "../General/Camera.h"

int main()
{
	// Target Image.
	const double aspectRatio = 16.0 / 9.0;
	const int imageWidth = 2560;
	const int imageHeight = imageWidth / aspectRatio;
	const int samplesPerPixel = 4;
	const int maxReflectionTimes = 50;

	// Build the World.
	HitableList world;
	world.Append(std::make_shared<Sphere>(0, 0, -1, 0.5));
	world.Append(std::make_shared<Sphere>(0, -100.5, -1, 100));

	// Create the camera.
	Camera mainCamera((Vector3()));

	// Render.
	std::cout << "P3\n" << imageWidth << " " << imageHeight << "\n255\n";
	for (double j = imageHeight - 1; j >= 0; j--)
	{
		std::cerr << "\rScan lines remaining: " << j << ' ' << std::flush;
		for (double i = 0; i < imageWidth; i++)
		{
			Color pixelColor;
			for (int s = 0; s < samplesPerPixel; s++)
			{
				auto u = (i + RabbitUtility::Random()) / (imageWidth - 1);
				auto v = (j + RabbitUtility::Random()) / (imageHeight - 1);
				Ray ray = mainCamera.GetRayByCoordinate(u, v);
				pixelColor.GetData() += ray.GetColor(world, maxReflectionTimes).GetData();
			}
			pixelColor.GetData() /= samplesPerPixel;
			std::cout << pixelColor << std::endl;
		}
	}
}