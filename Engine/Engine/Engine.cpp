#include <SFML/Graphics.hpp>
#include "Engine.h"
#include "PrimitiveRenderer.h"
#include "Point2D.h"



// Po ":" wypisujemy liste inicjalizacyjna zastepujaca np. this->width = w;
Engine:: Engine(int w, int h, bool fullscreen) : width(w), height(h), fullscreen(fullscreen), window(sf::VideoMode(w, h), "Engine2D"), moveCounter(0) {
	if (fullscreen) {
		window.create(sf::VideoMode(w, h), "Engine2D", sf::Style::Fullscreen);
	}
	else {
		window.create(sf::VideoMode(w, h), "Engine2D");
	}
	if (!window.isOpen()) {
		// Zapisanie komunikatu o bledzie w pliku logfile.txt
		std::ofstream logfile("logfile.txt");
		if (logfile.is_open()) {
			logfile << "B??d inicjalizacji okna." << std::endl;
		}
		else {
			std::cerr << "Blad otwarcia pliku do zapisu." << std::endl;
		}
		logfile.close();

		std::cerr << "B??d inicjalizacji okna. Zobacz plik logfile.txt dla wi?cej informacji." << std::endl;
		// Zakoncz prace silnika
		exit(1);
	}
};



void Engine:: setLimit(int limit) {
	this->limitFramrate = limit;
}

void Engine:: clearScreen(sf::RenderTarget& target, const sf::Color& color) {
	target.clear(color);
}

void Engine::setFullscreen(bool fullscreen) {
	this->fullscreen = fullscreen;
	if (fullscreen) {
		sf::VideoMode fullscreenMode = sf::VideoMode::getFullscreenModes()[0];
		window.create(fullscreenMode, "Engine2D Full Screen", sf::Style::Fullscreen);
		width = fullscreenMode.width;
		height = fullscreenMode.height;
	}
	else {
		window.create(sf::VideoMode(width, height), "Engine2D");

	}
}

void Engine::setWindowSize(int w, int h) {
	width = w;
	height = h;
	window.setSize(sf::Vector2u(width, height));
}

void Engine::zaladujBitmape(const std::string& nazwaPliku) {
	bitmapa.zaladujZPliku(nazwaPliku);
}

void Engine::zapiszBitmape(const std::string& nazwaPliku) {
	bitmapa.zapiszDoPliku(nazwaPliku);
}

void Engine::skopiujBitmapyZSilnika(int x, int y, int szerokosc, int wysokosc) {
	bitmapa.skopiujZBitmapy(bitmapa, x, y, szerokosc, wysokosc); // Wywo�anie metody z obiektu bitmapy
}

void Engine::run() {
	window.setFramerateLimit(limitFramrate);
	PrimitiveRenderer newLine;
	PrimitiveRenderer circle;
	PrimitiveRenderer rectangle;
	PrimitiveRenderer elipse;
	//Point2D ptk(700, 400);
	//Point2D newPoint(circle.c1, circle.c2);
	//std::vector<Point2D> startPoints;
	bool bgWhite = true;

	std::vector<sf::Vector2f> vertices = {
		sf::Vector2f(100, 50),
		sf::Vector2f(200, 100),
		sf::Vector2f(200, 200),
		sf::Vector2f(100, 150)
	};


	sf::Clock clock;

	while (window.isOpen()) {
		//Pobiera czas, ktory uplynal od ostatniego wywolania clock.restart()
		sf::Time deltaTime = clock.restart();
		sf::Event event;

		//Nasluchiwnie zdarzen
		while (window.pollEvent(event)) {
			if (event.type == sf::Event::Closed) {
				window.close();
			} 

			// Ustawienie ekranu na rozdzielczosc 800x600 skrotem ALT+R
			if (event.type == sf::Event::KeyPressed) {
				if ((event.key.code == sf::Keyboard::R) && (event.key.alt)) {
					if (fullscreen) {
						setFullscreen(false);
						setWindowSize(800, 600);
					}
					else {
						setWindowSize(800, 600);
					}
				}
			}

			// Obs�uga strza�ek na klawiaturze, kt�re przesuwaj� nasz obiekt rect
			if (event.type == sf::Event::KeyPressed) {
				if (event.key.code == sf::Keyboard::Left) {
					circle.move(-5.f, 0.f);
					moveCounter++;
				}
				else if (event.key.code == sf::Keyboard::Right) {
					circle.move(5.f, 0.f);
					moveCounter++;
				}
				else if (event.key.code == sf::Keyboard::Up) {
					circle.move(0.f, -5.f);
					moveCounter++;
				}
				else if (event.key.code == sf::Keyboard::Down) {
					circle.move(0.f, 5.f);
					moveCounter++;
				}
			}

			// Ustawienie pelnego ekranu skrotem ALT+F (F-fullscreen)
			if (event.type == sf::Event::KeyPressed) {
				if ((event.key.code == sf::Keyboard::F) && (event.key.alt)) {
					setFullscreen(true);
				}
			}

			if (event.type == sf::Event::MouseButtonPressed) {
				if (event.mouseButton.button == sf::Mouse::Left) {
					sf::Vector2i mousePosition = sf::Mouse::getPosition(window);
					sf::Vector2f direction = sf::Vector2f(mousePosition) - sf::Vector2f(circle.c1, circle.c2);
					float length = std::sqrt(direction.x * direction.x + direction.y * direction.y);

					// Normalizujemy wektor kierunku, aby uzyska� wektor jednostkowy
					if (length != 0) {
						direction /= length;
					}

					// Obliczamy punkt na obwodzie okr�gu, kt�ry b�dzie punktem pocz�tkowym przemieszczenia
					Point2D startPoint(circle.c1, circle.c2, direction, 5.0f);
					//startPoints.push_back(Point2D(circle.c1, circle.c2, direction, 5.0f));

					// Dop�ki punkt jest na ekranie, przesuwamy go w kierunku klikni�cia
					while (window.isOpen() && startPoint.getPoint().x >= 0 && startPoint.getPoint().x <= width && startPoint.getPoint().y >= 0 && startPoint.getPoint().y <= height) {
						// Aktualizujemy po�o�enie punktu
						startPoint.update();

						// Czyscimy ekran
						window.clear(bgColor);

						// Rysujemy wszystkie elementy
						newLine.drawLine(50, 40, 400, 100, window, sf::Color::Red);
						circle.drawCircle(50, window, sf::Color::Magenta);
						rectangle.drawRectangle(vertices, window, sf::Color::Red);
						elipse.drawElipse(400, 300, 100, 50, window, sf::Color::Yellow);
						//ptk.setPoint(100, 380);
						//ptk.drawPoint(ptk, window, sf::Color::Cyan);

						// Rysujemy punkt
						startPoint.drawPoint(startPoint, window, sf::Color::Red);

						// Wy�wietlamy wszystkie elementy
						window.display();
					}
				}
				else if (event.mouseButton.button == sf::Mouse::Right) {
					std::cout << "Wcisnieto prawy przycisk myszy" << std::endl;
					//dalsza obsluga zdarzenia
				}
			}


		/*	if (event.type == sf::Event::MouseMoved) {
				sf::Vector2i mousePosition = sf::Mouse::getPosition(window);
				std::cout << "Pozycja myszy: " << mousePosition.x << ", " << mousePosition.y << std::endl;
			}*/

			if (moveCounter == 5)
			{
				if (bgWhite) {
					bgColor.r = std::max(bgColor.r - 32, 0);
					bgColor.g = std::max(bgColor.g - 32, 0);
					bgColor.b = std::max(bgColor.b - 32, 0);
					if (bgColor.r == 0 && bgColor.g == 0 && bgColor.b == 0) {
						bgWhite = false;
					}
				}
				else {
					bgColor.r = std::min(bgColor.r + 32, 255);
					bgColor.g = std::min(bgColor.g + 32, 255);
					bgColor.b = std::min(bgColor.b + 32, 255);
					if (bgColor.r == 255 && bgColor.g == 255 && bgColor.b == 255) {
						bgWhite = true;
					}
				}

				// Resetujemy licznik ruch�w
				moveCounter = 0;
			}






		}

		// Czyszczenie ekranu do zadanego koloru (np. jasnoniebieski)
		//window.clear(sf::Color(135, 206, 250));
		// Czy�cimy ekran do wylosowanego koloru
		window.clear(bgColor);
		// Wylczenie synchronizacji pionowej
		window.setVerticalSyncEnabled(true);

		newLine.drawLine(50, 40, 400, 100,window, sf::Color::Red);
		circle.drawCircle(50, window, sf::Color::Magenta);
		rectangle.drawRectangle(vertices, window, sf::Color::Red);
		elipse.drawElipse(400, 300, 100, 50, window, sf::Color::Yellow);
		//ptk.setPoint(100, 380);
		//ptk.drawPoint(ptk, window, sf::Color::Cyan);
		//newPoint.drawPoint(newPoint, window, sf::Color::Red);

		// wczytywanie bitmapy z pliku
		zaladujBitmape("bitmapa.png");

		// zapisywanie bitmapy do pliku
		zapiszBitmape("nowa_bitmapa.png");

		// kopiowanie fragmentu bitmapy z silnika do samego siebie
		// skopiujBitmapyZSilnika(100, 100, 200, 200);

		// rysowanie bitmapy na ekranie
		bitmapa.rysujNaRenderWindow(window, 300, 300);
	

		/* Nasz� scen� tworzymy wi�c na buforze, kt�rego zawarto�� jest automatycznie kopiowana na ekran w chwili wywo�ania metody display
		W SFML zarzadzanie technika wielokrotnego buforowania nastepuje automatycznie
		*/
		window.display();

		//std::cout << "Czas trwania klatki: " << deltaTime.asSeconds() << " sekundy" << std::endl;
	}
}


int main()
{
    Engine& engine = Engine::getInstance(800, 600, false);
    engine.setLimit(2);
    engine.run();

    return 0;
}