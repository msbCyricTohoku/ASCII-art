//ascii art program -- run 'make' then './ascii-art.bin 3.png 5 10' that is './ascii-art.bin <your_image.png> <width_scale> <height_scale>'
#include <iostream>
#include <vector>
#include <thread>
#include <chrono>
#include <cstdlib>
#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

const char* grayScale = " .:-=+*#%@";

void printImageAsAscii(const std::vector<unsigned char>& image, int width, int height, int channels, int widthScale, int heightScale) {
    std::cout << "Original Width: " << width << ", Original Height: " << height << std::endl << std::endl;

    for (int y = 0; y < height; y += heightScale) {
        for (int x = 0; x < width; x += widthScale) {
            int sumR = 0, sumG = 0, sumB = 0, count = 0;
            for (int dy = 0; dy < heightScale && (y + dy) < height; ++dy) {
                for (int dx = 0; dx < widthScale && (x + dx) < width; ++dx) {
                    int index = ((y + dy) * width + (x + dx)) * channels;
                    sumR += image[index];
                    sumG += image[index + 1];
                    sumB += image[index + 2];
                    ++count;
                }
            }
            int avgR = sumR / count;
            int avgG = sumG / count;
            int avgB = sumB / count;
            int gray = (avgR + avgG + avgB) / 3;
            char c = grayScale[gray * 10 / 256];
            std::cout << c;
        }
        std::cout << std::endl;
        std::this_thread::sleep_for(std::chrono::milliseconds(50));
    }
}

int main(int argc, char* argv[]) {
    if (argc < 4) {
        std::cerr << "Usage: " << argv[0] << " <image_path> <width_scale> <height_scale>" << std::endl;
        return 1;
    }

    const char* imagePath = argv[1];
    int widthScale = std::atoi(argv[2]);
    int heightScale = std::atoi(argv[3]);

    int width, height, channels;
    unsigned char* img = stbi_load(imagePath, &width, &height, &channels, 0);
    if (img == nullptr) {
        std::cerr << "Error: Could not load image " << imagePath << std::endl;
        return 1;
    }

    std::vector<unsigned char> image(img, img + (width * height * channels));
    stbi_image_free(img);

    printImageAsAscii(image, width, height, channels, widthScale, heightScale);
    
    std::this_thread::sleep_for(std::chrono::milliseconds(2000));
    
    std::cout << "\n\n\n\n\n\n\n\n\n";

    return 0;
}

