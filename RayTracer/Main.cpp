#include <iostream>

#include "../General/CommonHeader.hpp"
#include "../General/Color.h"
#include "../General/HitableList.h"
#include "../General/Sphere.h"
#include "../General/Camera.h"
#include "../General/LambertianMaterial.h"
#include "../General/MetalMaterial.h"

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
	auto materialGround = std::make_shared<LambertianMaterial>(Color(0.8, 0.8, 0.0));
	auto materialCenter = std::make_shared<LambertianMaterial>(Color(0.7, 0.3, 0.3));
	auto materialLeft = std::make_shared<MetalMaterial>(Color(0.8));
	auto materialRight = std::make_shared<MetalMaterial>(Color(0.8, 0.6, 0.2));
	world.Append(std::make_shared<Sphere>(Vector3(0.0, -100.5, -1.0), materialGround, 100.0));
	world.Append(std::make_shared<Sphere>(Vector3{ 0.0, 0.0, -1.0 }, materialCenter, 0.5));
	world.Append(std::make_shared<Sphere>(Vector3{ -1.0, 0.0, -1.0 }, materialLeft, 0.5));
	world.Append(std::make_shared<Sphere>(Vector3{ 1.0, 0.0, -1.0 }, materialRight, 0.5));

	// Create the camera.
	Vector3 Origin(0.0);
	Camera mainCamera(Origin);

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
				auto u = (i + RabbitUtility::Random(-1, 1)) / (imageWidth - 1);
				auto v = (j + RabbitUtility::Random(-1, 1)) / (imageHeight - 1);
				Ray ray = mainCamera.GetRayByCoordinate(u, v);
				pixelColor.GetData() += ray.GetColor(world, maxReflectionTimes).GetData();
			}
			pixelColor.GetData() /= samplesPerPixel;
			std::cout << pixelColor << std::endl;
		}
	}
}