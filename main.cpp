#include <iostream>
#include <SDL2/SDL.h>
#include "Utils.hpp"
#include "../General/CommonHeader.hpp"
#include "../General/Color.h"
#include "../General/HitableList.h"
#include "../General/Sphere.h"
#include "../General/Camera.h"
#include "../General/LambertianMaterial.h"
#include "../General/MetalMaterial.h"
#include "../General/DielectricMaterial.h"
#include "ThreadPool.hpp"

void render(int imageWidth, double aspectRatio, unsigned int *pixels)
{
    const int imageHeight = imageWidth / aspectRatio;
    const int samplesPerPixel = 100;
    const int maxReflectionTimes = 50;

    // Build the World.
    HitableList world;

    auto materialGround = std::make_shared<LambertianMaterial>(Color(0.8, 0.8, 0.0));
    auto materialCenter = std::make_shared<LambertianMaterial>(Color(0.7, 0.3, 0.3));
    auto materialLeft = std::make_shared<DielectricMaterial>(1.5);
    auto materialRight = std::make_shared<MetalMaterial>(Color(0.8, 0.6, 0.2), 0.0);
    world.Append(std::make_shared<Sphere>(Vector3(0.0, -100.5, -1.0), materialGround, 100.0));
    world.Append(std::make_shared<Sphere>(Vector3{0.0, 0.0, -1.0}, materialCenter, 0.5));
    world.Append(std::make_shared<Sphere>(Vector3{-1.0, 0.0, -1.0}, materialLeft, 0.5));
    world.Append(std::make_shared<Sphere>(Vector3{-1.0, 0.0, -1.0}, materialLeft, -0.45));
    world.Append(std::make_shared<Sphere>(Vector3{1.0, 0.0, -1.0}, materialRight, 0.5));

    // Create the camera.
    Camera mainCamera({-2, 1, 1}, {0.0, 0.0, -1.0}, {0, 1, 0}, 90, aspectRatio);

    std::cout << "P3\n"
              << imageWidth << " " << imageHeight << "\n255\n";

    ThreadPool pool{12};
    for (int j = imageHeight - 1; j >= 0; j--)
    {
        auto render_process = [imageWidth, imageHeight, samplesPerPixel, pixels, maxReflectionTimes, &mainCamera, &world](int j)
        {
            for (int i = 0; i < imageWidth; ++i)
            {
                Color pixelColor;
                for (int s = 0; s < samplesPerPixel; s++)
                {
                    auto u = (static_cast<double>(i) + RabbitUtility::Random(-1, 1)) / (imageWidth - 1);
                    auto v = (static_cast<double>(j) + RabbitUtility::Random(-1, 1)) / (imageHeight - 1);
                    Ray ray = mainCamera.GetRayByCoordinate(u, v);

                    pixelColor.GetData() += ray.GetColor(world, maxReflectionTimes).GetData();
                }
                pixelColor.GetData() /= samplesPerPixel;

                pixels[i + (imageHeight - j - 1) * imageWidth] = RGB(
                    int(256.0 * RabbitUtility::Clamp(pixelColor.GetData()[0], 0.0, 0.999)),
                    int(256.0 * RabbitUtility::Clamp(pixelColor.GetData()[1], 0.0, 0.999)),
                    int(256.0 * RabbitUtility::Clamp(pixelColor.GetData()[2], 0.0, 0.999)));
            }
        };
        pool.enqueue(render_process, j);
    }
}

int main(int argc, char **argv)
{
    int imageWidth = 1368;
    double aspectRatio = 16.0 / 9.0;
    int imageHeight = imageWidth / aspectRatio;

    SDL_Init(SDL_INIT_VIDEO);
    SDL_Window *window = SDL_CreateWindow("demo", 40, 40, imageWidth, imageHeight, SDL_WINDOW_SHOWN);
    SDL_Renderer *renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    SDL_Texture *screen_texture = SDL_CreateTexture(renderer, SDL_PIXELFORMAT_RGBA8888, SDL_TEXTUREACCESS_STREAMING, imageWidth, imageHeight);
    unsigned int *pixels = (unsigned int *)malloc(imageWidth * imageHeight * 4);

    SDL_Event event;
    bool quit = false;

    std::thread render_thread(render, imageWidth, aspectRatio, pixels);

    while (!quit)
    {
        if (SDL_PollEvent(&event))
        {
            if (event.type == SDL_QUIT)
            {
                SDL_DestroyWindow(window);
                exit(0);
            }
        }
        else
        {
            clock_t start = clock();
            SDL_RenderClear(renderer);
            SDL_UpdateTexture(screen_texture, NULL, pixels, imageWidth * 4);
            SDL_RenderCopy(renderer, screen_texture, NULL, NULL);
            SDL_RenderPresent(renderer);
            clock_t end = clock();
            std::this_thread::sleep_for(std::chrono::milliseconds(16 - (end - start)));
        }
    }

    return 0;
}