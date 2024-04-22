#include "BitmapHandler.h"
#include <fstream>

// Konstruktor domy�lny klasy BitmapHandler
BitmapHandler::BitmapHandler() {}

// Funkcja tworz�ca nowy bitmap� o podanych wymiarach
void BitmapHandler::createBitmap(int width, int height) {
    // Zmiana rozmiaru bitmapy na podane wymiary, wype�nienie zerami
    bitmap.resize(height, std::vector<int>(width, 0));
}

// Funkcja usuwaj�ca zawarto�� bitmapy
void BitmapHandler::deleteBitmap() {
    // Wyczyszczenie wektora bitmapy
    bitmap.clear();
}

// Funkcja wczytuj�ca bitmap� z pliku o podanej nazwie
bool BitmapHandler::loadFromFile(const std::string& filename) {
    // Otwarcie pliku do odczytu
    std::ifstream file(filename);
    // Sprawdzenie, czy plik zosta� otwarty poprawnie
    if (!file.is_open()) {
        // Je�li nie, zwr�� false (b��d wczytywania)
        return false;
    }

    // Wyczyszczenie aktualnej zawarto�ci bitmapy
    bitmap.clear();

    // Deklaracja zmiennych przechowuj�cych szeroko�� i wysoko�� bitmapy
    int width, height;
    // Wczytanie szeroko�ci i wysoko�ci z pliku
    file >> width >> height;

    // Zmiana rozmiaru bitmapy na podane wymiary, wype�nienie zerami
    bitmap.resize(height, std::vector<int>(width, 0));

    // Wczytywanie danych pikseli z pliku do bitmapy
    for (int y = 0; y < height; ++y) {
        for (int x = 0; x < width; ++x) {
            file >> bitmap[y][x];
        }
    }

    // Zamkni�cie pliku i zwr�cenie true (wczytanie zako�czone sukcesem)
    file.close();
    return true;
}

// Funkcja zapisuj�ca bitmap� do pliku o podanej nazwie
bool BitmapHandler::saveToFile(const std::string& filename) {
    // Otwarcie pliku do zapisu
    std::ofstream file(filename);
    // Sprawdzenie, czy plik zosta� otwarty poprawnie
    if (!file.is_open()) {
        // Je�li nie, zwr�� false (b��d zapisu)
        return false;
    }

    // Pobranie szeroko�ci i wysoko�ci bitmapy
    int width = bitmap[0].size();
    int height = bitmap.size();

    // Zapisanie szeroko�ci i wysoko�ci do pliku
    file << width << " " << height << std::endl;

    // Zapisanie danych pikseli do pliku
    for (int y = 0; y < height; ++y) {
        for (int x = 0; x < width; ++x) {
            file << bitmap[y][x] << " ";
        }
        // Zako�czenie linii po zapisaniu wszystkich pikseli w wierszu
        file << std::endl;
    }

    // Zamkni�cie pliku i zwr�cenie true (zapis zako�czony sukcesem)
    file.close();
    return true;
}

// Funkcja kopiuj�ca zawarto�� bitmapy z innej bitmapy
void BitmapHandler::copyFrom(const BitmapHandler& other) {
    // Przypisanie zawarto�ci bitmapy z innej bitmapy
    bitmap = other.bitmap;
}