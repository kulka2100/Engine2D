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
     * @brief Konstruktor klasy BitmapHandler
     */
    BitmapHandler();

    /**
     * @brief Metoda tworzaca nowa bitmape o podanej szerokosci i wysokosci
     * @param width Szerokosc nowej bitmape
     * @param height Wysokosc nowej bitmape
     */
    void createBitmap(int width, int height);

    /**
     * @brief Metoda usuwajaca istniejaca bitmape
     */
    void deleteBitmap();

    /**
     * @brief Metoda wczytujaca bitmape z pliku
     * @param filename Nazwa pliku z bitmapa
     * @return informacjca o sukcesie operacji wczytywania
     */
    bool loadFromFile(const std::string& filename);

    /**
     * @brief Metoda zapisujaca bitmape do pliku
     * @param filename nazwa pliku do ktorego zostanie zapisana bitmapa
     * @return informacja o sukcesie operacji zapisywania
     */
    bool saveToFile(const std::string& filename);

    /**
     * @brief Metoda kopiujaca zawartosc bitmape z innej instancji klasy BitmapHandler
     * @param other Inna instancja klasy BitmapHandler
     */
    void copyFrom(const BitmapHandler& other);
};