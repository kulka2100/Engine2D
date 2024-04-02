#pragma once
#include <SFML/Graphics/Image.hpp>
#include <SFML/Graphics/Texture.hpp>
#include <SFML/Graphics.hpp>

class BitmapHandler {
private:
    sf::Image obraz;

public:
    BitmapHandler() {}

    void utworz(int szerokosc, int wysokosc);

    void zaladujZPliku(const std::string& nazwaPliku);

    void zapiszDoPliku(const std::string& nazwaPliku);

    void skopiujZBitmapy(const BitmapHandler& inna, int x, int y, int szerokosc, int wysokosc);

    void rysujNaRenderWindow(sf::RenderWindow& okno, int x, int y);
};