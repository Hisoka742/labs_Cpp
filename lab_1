#include <iostream>
#include <fstream>
#include <vector>
#include <cmath>

#pragma pack(push, 1)
struct BMPHeader {
    char signature[2];
    int32_t fileSize;
    int32_t reserved;
    int32_t dataOffset;
    int32_t headerSize;
    int32_t width;
    int32_t height;
    uint16_t planes;
    uint16_t bitsPerPixel;
    int32_t compression;
    int32_t imageSize;
    int32_t xPixelsPerMeter;
    int32_t yPixelsPerMeter;
    int32_t colorsUsed;
    int32_t importantColors;
};
#pragma pack(pop)

// Function to read a BMP image into memory
std::vector<uint8_t> ReadBMP(const std::string& filename, int& width, int& height) {
    std::ifstream file(filename, std::ios::binary);
    if (!file) {
        std::cerr << "Error: Cannot open file " << filename << std::endl;
        exit(1);
    }

    BMPHeader header;
    file.read(reinterpret_cast<char*>(&header), sizeof(BMPHeader));

    if (header.signature[0] != 'B' || header.signature[1] != 'M') {
        std::cerr << "Error: Not a valid BMP file." << std::endl;
        exit(1);
    }

    width = header.width;
    height = header.height;

    std::vector<uint8_t> image(header.imageSize);
    file.read(reinterpret_cast<char*>(image.data()), header.imageSize);
    return image;
}

// Function to save a BMP image to a file
void SaveBMP(const std::string& filename, const std::vector<uint8_t>& data, int width, int height) {
    std::ofstream file(filename, std::ios::binary);
    if (!file) {
        std::cerr << "Error: Cannot create file " << filename << std::endl;
        exit(1);
    }

    BMPHeader header;
    header.signature[0] = 'B';
    header.signature[1] = 'M';
    header.fileSize = sizeof(BMPHeader) + data.size();
    header.reserved = 0;
    header.dataOffset = sizeof(BMPHeader);
    header.headerSize = sizeof(BMPHeader) - 14;
    header.width = width;
    header.height = height;
    header.planes = 1;
    header.bitsPerPixel = 24;
    header.compression = 0;
    header.imageSize = data.size();
    header.xPixelsPerMeter = 0;
    header.yPixelsPerMeter = 0;
    header.colorsUsed = 0;
    header.importantColors = 0;

    file.write(reinterpret_cast<const char*>(&header), sizeof(BMPHeader));
    file.write(reinterpret_cast<const char*>(data.data()), data.size());
}

// Function to rotate a BMP image 90 degrees clockwise
std::vector<uint8_t> RotateBMP90Clockwise(const std::vector<uint8_t>& input, int width, int height) {
    std::vector<uint8_t> output(width * height * 3);

    for (int y = 0; y < height; ++y) {
        for (int x = 0; x < width; ++x) {
            int inputIdx = (y * width + x) * 3;
            int outputIdx = ((width - x - 1) * height + y) * 3;

            output[outputIdx] = input[inputIdx];
            output[outputIdx + 1] = input[inputIdx + 1];
            output[outputIdx + 2] = input[inputIdx + 2];
        }
    }

    return output;
}

// Function to apply a 5x5 Gaussian filter to an image
std::vector<uint8_t> ApplyGaussianFilter(const std::vector<uint8_t>& input, int width, int height) {
    std::vector<uint8_t> output(input.size());

    // Define the 5x5 Gaussian kernel
    double kernel[5][5] = {
        {1.0 / 256, 4.0 / 256, 6.0 / 256, 4.0 / 256, 1.0 / 256},
        {4.0 / 256, 16.0 / 256, 24.0 / 256, 16.0 / 256, 4.0 / 256},
        {6.0 / 256, 24.0 / 256, 36.0 / 256, 24.0 / 256, 6.0 / 256},
        {4.0 / 256, 16.0 / 256, 24.0 / 256, 16.0 / 256, 4.0 / 256},
        {1.0 / 256, 4.0 / 256, 6.0 / 256, 4.0 / 256, 1.0 / 256}
    };

    int kernelSize = 5;

    for (int y = 0; y < height; ++y) {
        for (int x = 0; x < width; ++x) {
            double sumR = 0.0;
            double sumG = 0.0;
            double sumB = 0.0;
            double sumWeight = 0.0;

            for (int ky = 0; ky < kernelSize; ++ky) {
                for (int kx = 0; kx < kernelSize; ++kx) {
                    int offsetX = x - kernelSize / 2 + kx;
                    int offsetY = y - kernelSize / 2 + ky;

                    if (offsetX >= 0 && offsetX < width && offsetY >= 0 && offsetY < height) {
                        int idx = (offsetY * width + offsetX) * 3;
                        double weight = kernel[ky][kx];

                        sumR += static_cast<double>(input[idx]) * weight;
                        sumG += static_cast<double>(input[idx + 1]) * weight;
                        sumB += static_cast<double>(input[idx + 2]) * weight;
                        sumWeight += weight;
                    }
                }
            }

            int outputIdx = (y * width + x) * 3;
            output[outputIdx] = static_cast<uint8_t>(sumR / sumWeight);
            output[outputIdx + 1] = static_cast<uint8_t>(sumG / sumWeight);
            output[outputIdx + 2] = static_cast<uint8_t>(sumB / sumWeight);
        }
    }

    return output;
}

int main() {
    int width, height;

    // Load the BMP image into memory
    std::string filename = "C:\\imagefortest\\Shapes_24.bmp";
    std::vector<uint8_t> image = ReadBMP(filename, width, height);

    // Rotate the image 90 degrees clockwise
    std::vector<uint8_t> rotatedImage = RotateBMP90Clockwise(image, width, height);

    // Apply the Gaussian filter to the rotated image
    std::vector<uint8_t> filteredImage = ApplyGaussianFilter(rotatedImage, height, width);

    // Save the filtered image to a file
    SaveBMP("filtered_image.bmp", filteredImage, height, width);

    return 0;
}
