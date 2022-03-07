#include <iostream>
#include <random>

int main() {
    const double ImageWidth = 2560;
    const double ImageHeight = 1440;
    std::random_device rd;
    std::mt19937 mt(rd());
    double oneColor[3]{static_cast<double>(mt() % 256), static_cast<double>(mt() % 256),
                       static_cast<double>(mt() % 256)};
    double otherColor[3]{static_cast<double>(mt() % 256), static_cast<double>(mt() % 256),
                         static_cast<double>(mt() % 256)};
    double offset[3]{(otherColor[0] - oneColor[0]) / ImageHeight, (otherColor[1] - oneColor[1]) / ImageHeight,
                     (otherColor[2] - oneColor[2]) / ImageHeight};

    std::cout << "P3\n" << ImageWidth << ' ' << ImageHeight << "\n255\n";
    for (double j = ImageHeight; j > 0; j--) {
        std::cerr << "\rScanlines remaining: " << j << ' ' << std::flush;
        for (double i = 0; i < ImageWidth; i++) {
            for (double k: oneColor)
                std::cout << (int) k << ' ';
            std::cout << std::endl;
        }
        for (size_t k = 0; k < 3; k++)
            oneColor[k] += offset[k];
    }
    std::cerr << "\nDone.\n";
}

