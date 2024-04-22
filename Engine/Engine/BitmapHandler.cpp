#include "BitmapHandler.h"
#include <fstream>

// Konstruktor domyœlny klasy BitmapHandler
BitmapHandler::BitmapHandler() {}

// Funkcja tworz¹ca nowy bitmapê o podanych wymiarach
void BitmapHandler::createBitmap(int width, int height) {
    // Zmiana rozmiaru bitmapy na podane wymiary, wype³nienie zerami
    bitmap.resize(height, std::vector<int>(width, 0));
}

// Funkcja usuwaj¹ca zawartoœæ bitmapy
void BitmapHandler::deleteBitmap() {
    // Wyczyszczenie wektora bitmapy
    bitmap.clear();
}

// Funkcja wczytuj¹ca bitmapê z pliku o podanej nazwie
bool BitmapHandler::loadFromFile(const std::string& filename) {
    // Otwarcie pliku do odczytu
    std::ifstream file(filename);
    // Sprawdzenie, czy plik zosta³ otwarty poprawnie
    if (!file.is_open()) {
        // Jeœli nie, zwróæ false (b³¹d wczytywania)
        return false;
    }

    // Wyczyszczenie aktualnej zawartoœci bitmapy
    bitmap.clear();

    // Deklaracja zmiennych przechowuj¹cych szerokoœæ i wysokoœæ bitmapy
    int width, height;
    // Wczytanie szerokoœci i wysokoœci z pliku
    file >> width >> height;

    // Zmiana rozmiaru bitmapy na podane wymiary, wype³nienie zerami
    bitmap.resize(height, std::vector<int>(width, 0));

    // Wczytywanie danych pikseli z pliku do bitmapy
    for (int y = 0; y < height; ++y) {
        for (int x = 0; x < width; ++x) {
            file >> bitmap[y][x];
        }
    }

    // Zamkniêcie pliku i zwrócenie true (wczytanie zakoñczone sukcesem)
    file.close();
    return true;
}

// Funkcja zapisuj¹ca bitmapê do pliku o podanej nazwie
bool BitmapHandler::saveToFile(const std::string& filename) {
    // Otwarcie pliku do zapisu
    std::ofstream file(filename);
    // Sprawdzenie, czy plik zosta³ otwarty poprawnie
    if (!file.is_open()) {
        // Jeœli nie, zwróæ false (b³¹d zapisu)
        return false;
    }

    // Pobranie szerokoœci i wysokoœci bitmapy
    int width = bitmap[0].size();
    int height = bitmap.size();

    // Zapisanie szerokoœci i wysokoœci do pliku
    file << width << " " << height << std::endl;

    // Zapisanie danych pikseli do pliku
    for (int y = 0; y < height; ++y) {
        for (int x = 0; x < width; ++x) {
            file << bitmap[y][x] << " ";
        }
        // Zakoñczenie linii po zapisaniu wszystkich pikseli w wierszu
        file << std::endl;
    }

    // Zamkniêcie pliku i zwrócenie true (zapis zakoñczony sukcesem)
    file.close();
    return true;
}

// Funkcja kopiuj¹ca zawartoœæ bitmapy z innej bitmapy
void BitmapHandler::copyFrom(const BitmapHandler& other) {
    // Przypisanie zawartoœci bitmapy z innej bitmapy
    bitmap = other.bitmap;
}