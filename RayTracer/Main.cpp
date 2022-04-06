#include <iostream>

#include "../General/CommonHeader.hpp"
#include "../General/Color.h"
#include "../General/HitableList.h"
#include "../General/Sphere.h"
#include "../General/Camera.h"
#include "../General/LambertianMaterial.h"
#include "../General/MetalMaterial.h"
#include "../General/DielectricMaterial.h"

HitableList RandomScene()
{
	HitableList world;

	auto groundMaterial = std::make_shared<LambertianMaterial>(Color(0.5));
	auto material1 = std::make_shared<DielectricMaterial>(1.5);
	auto material2 = std::make_shared<LambertianMaterial>(Color(0.4, 0.2, 0.1));
	auto material3 = std::make_shared<MetalMaterial>(Color(0.7, 0.6, 0.5), 0.0);

	world.Append(std::make_shared<Sphere>(Vector3(0, -1000, 0), groundMaterial, 1000.0));
	world.Append(std::make_shared<Sphere>(Vector3(0, 1, 0), material1, 1.0));
	world.Append(std::make_shared<Sphere>(Vector3(-4, 1, 0), material2, 1.0));
	world.Append(std::make_shared<Sphere>(Vector3(4, 1, 0), material3, 1.0));

	for (int x = -11; x <= 11; x++)
		for (int z = -11; z <= 11; z++)
		{
			auto materialChoosingFactor = RabbitUtility::Random();
			Vector3 location(x + .9 * RabbitUtility::Random(), .2, z + .9 * RabbitUtility::Random());

			if ((location - Vector3(4, .2, 0)).Length() <= .9)
				continue;

			if (materialChoosingFactor < .8)
			{
				// Diffuse
				auto albedo = Color(Vector3::RandomPointInUnitSphere() * Vector3::RandomPointInUnitSphere());
				auto sphereMaterial = std::make_shared<LambertianMaterial>(albedo);
				world.Append(std::make_shared<Sphere>(location, sphereMaterial, .2));
			}
			else if (materialChoosingFactor < .95)
			{
				// Metal
				auto albedo = Color(RabbitUtility::Random(.5, 1), RabbitUtility::Random(.5, 1),
						RabbitUtility::Random(.5, 1));
				double fuzziness = RabbitUtility::Random(0, .5);
				auto sphereMaterial = std::make_shared<MetalMaterial>(albedo, fuzziness);
				world.Append(std::make_shared<Sphere>(location, sphereMaterial, .2));
			}
			else
			{
				// Glass
				auto sphereMaterial = std::make_shared<DielectricMaterial>(1.5);
				world.Append(std::make_shared<Sphere>(location, sphereMaterial, .2));
			}
		}

	return world;
}

int main()
{
	// Target Image.
	const double aspectRatio = 16.0 / 9.0;
	const int imageWidth = 2560;
	const int imageHeight = imageWidth / aspectRatio;
	const int samplesPerPixel = 32;
	const int maxReflectionTimes = 150;

	// Build the World.
//	HitableList world;
//	auto materialGround = std::make_shared<LambertianMaterial>(Color(0.8, 0.8, 0.0));
//	auto materialCenter = std::make_shared<LambertianMaterial>(Color(0.7, 0.3, 0.3));
//	auto materialLeft = std::make_shared<DielectricMaterial>(1.5);
//	auto materialRight = std::make_shared<MetalMaterial>(Color(0.8, 0.6, 0.2), .8);
//	world.Append(std::make_shared<Sphere>(Vector3(0.0, -100.5, -1.0), materialGround, 100.0));
//	world.Append(std::make_shared<Sphere>(Vector3{ 0.0, 0.0, -1.0 }, materialCenter, 0.5));
//	world.Append(std::make_shared<Sphere>(Vector3{ -1.0, 0.0, -1.0 }, materialLeft, 0.5));
//	world.Append(std::make_shared<Sphere>(Vector3{ -1.0, 0.0, -1.0 }, materialLeft, -0.45));
//	world.Append(std::make_shared<Sphere>(Vector3{ 1.0, 0.0, -1.0 }, materialRight, 0.5));
	HitableList world = RandomScene();

	// Create the camera.
	Camera mainCamera({ 13, 2, 3 }, { 0, 0, 0 }, { 0, 1, 0 }, 20, aspectRatio, 1.0, 10.0);

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