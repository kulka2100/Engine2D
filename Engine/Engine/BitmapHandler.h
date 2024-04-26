#pragma once
#include <vector>
#include <string>

/**
 * @class BitmapHandler
 * @brief Klasa obslugujaca manipulacje bitmapami
 */
class BitmapHandler {
private:
    std::vector<std::vector<int>> bitmap; /**< Dwuwymiarowy wektor reprezentujacy bitmape */

public:
    /**
     * @brief Konstruktor domyslny klasy BitmapHandler
     */
    BitmapHandler();

    /**
     * @brief Metoda tworzaca nowy bitmape o podanych wymiarach
     * @param width Szerokosc nowej bitmape
     * @param height Wysokosc nowej bitmape
     */
    void createBitmap(int width, int height);

    /**
     * @brief Metoda usuwaj¹ca zawartoœæ bitmapy
     */
    void deleteBitmap();

    /**
     * @brief Metoda wczytujaca bitmape z pliku o podanej nazwie
     * @param filename Nazwa pliku z bitmapa
     * @return informacjca o sukcesie operacji wczytywania
     */
    bool loadFromFile(const std::string& filename);

    /**
     * @brief Metoda zapisujaca bitmape do pliku o podanej nazwie
     * @param filename nazwa pliku do ktorego zostanie zapisana bitmapa
     * @return informacja o sukcesie operacji zapisywania
     */
    bool saveToFile(const std::string& filename);

    /**
     * @brief Metoda kopiujaca zawartosc bitmapy z innej bitmapy
     * @param other Inna instancja klasy BitmapHandler
     */
    void copyFrom(const BitmapHandler& other);
};