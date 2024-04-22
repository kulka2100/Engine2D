#pragma once
#include <vector>
#include <string>

class BitmapHandler {
private:
    std::vector<std::vector<int>> bitmap;

public:
    BitmapHandler();
    void createBitmap(int width, int height);
    void deleteBitmap();
    bool loadFromFile(const std::string& filename);
    bool saveToFile(const std::string& filename);
    void copyFrom(const BitmapHandler& other);
};