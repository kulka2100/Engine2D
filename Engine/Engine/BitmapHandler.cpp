#include "BitmapHandler.h"
#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/RenderWindow.hpp>

// Funkcja do tworzenia nowego pustego obrazu o okreœlonej szerokoœci i wysokoœci
void BitmapHandler::utworz(int szerokosc, int wysokosc) {
    obraz.create(szerokosc, wysokosc, sf::Color::Transparent); // Tworzenie obrazu z przezroczystym kolorem
}

// Funkcja do wczytywania obrazu z pliku
void BitmapHandler::zaladujZPliku(const std::string& nazwaPliku) {
    obraz.loadFromFile(nazwaPliku); // Wczytywanie obrazu z pliku
}

// Funkcja do zapisywania obrazu do pliku
void BitmapHandler::zapiszDoPliku(const std::string& nazwaPliku) {
    obraz.saveToFile(nazwaPliku); // Zapisywanie obrazu do pliku
}

// Funkcja do kopiowania czêœci obrazu innego obiektu BitmapHandler na ten obraz
void BitmapHandler::skopiujZBitmapy(const BitmapHandler& inna, int x, int y, int szerokosc, int wysokosc) {
    obraz.copy(inna.obraz, x, y, sf::IntRect(0, 0, szerokosc, wysokosc), true); // Kopiowanie obrazu
}

// Funkcja do rysowania obrazu na obiekcie RenderWindow w okreœlonej pozycji
void BitmapHandler::rysujNaRenderWindow(sf::RenderWindow& okno, int x, int y) {
    sf::Texture tekstura;
    tekstura.loadFromImage(obraz); // Wczytywanie tekstury z obrazu
    sf::Sprite sprite(tekstura);
    sprite.setPosition(x, y);
    okno.draw(sprite); // Rysowanie sprite'a na oknie
}