#include <SFML/Graphics.hpp>
#include "Engine.h"




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
			logfile << "Blad inicjalizacji okna." << std::endl;
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
	PrimitiveRenderer player;
	Point2D ptk(700, 400);
	Point2D ptk2(600, 400);
	bool bgWhite = true;

	sf::RectangleShape toolPanel(sf::Vector2f(30, 111));
	toolPanel.setFillColor(sf::Color(200, 200, 200));
	
	sf::RectangleShape moveButton(sf::Vector2f(24, 24));
	moveButton.setFillColor(sf::Color::White);
	moveButton.setOutlineColor(sf::Color::Black);
	moveButton.setOutlineThickness(1);
	moveButton.setPosition(toolPanel.getPosition().x + 3, toolPanel.getPosition().y + 3);
	sf::Texture moveTexture;
	if (!moveTexture.loadFromFile("moveButton.png")) {
		std::cerr << "Nie mo�na za�adowa� obrazka!" << std::endl; 
	}
	sf::Sprite moveButTexture(moveTexture);
	moveButTexture.setPosition(toolPanel.getPosition().x + 4, toolPanel.getPosition().y + 4);
	moveButTexture.setScale(22.0f / moveButTexture.getLocalBounds().width, 22.0f / moveButTexture.getLocalBounds().height);

	sf::RectangleShape rotateButton(sf::Vector2f(24, 24));
	rotateButton.setFillColor(sf::Color::White);
	rotateButton.setOutlineColor(sf::Color::Black);
	rotateButton.setOutlineThickness(1);
	rotateButton.setPosition(toolPanel.getPosition().x + 3, toolPanel.getPosition().y + 30);
	sf::Texture rotateTexture;
	if (!rotateTexture.loadFromFile("rotateButton.png")) {
		std::cerr << "Nie mo�na za�adowa� obrazka!" << std::endl;
	}
	sf::Sprite rotateButTexture(rotateTexture);
	rotateButTexture.setPosition(toolPanel.getPosition().x + 4, toolPanel.getPosition().y + 31);
	rotateButTexture.setScale(22.0f / rotateButTexture.getLocalBounds().width, 22.0f / rotateButTexture.getLocalBounds().height);
	
	sf::RectangleShape scaleButton(sf::Vector2f(24, 24));
	scaleButton.setFillColor(sf::Color::White);
	scaleButton.setOutlineColor(sf::Color::Black);
	scaleButton.setOutlineThickness(1);
	scaleButton.setPosition(toolPanel.getPosition().x + 3, toolPanel.getPosition().y + 57);
	sf::Texture scaleTexture;
	if (!scaleTexture.loadFromFile("scaleButton.png")) {
		std::cerr << "Nie mo�na za�adowa� obrazka!" << std::endl;
	}
	sf::Sprite scaleButTexture(scaleTexture);
	scaleButTexture.setPosition(toolPanel.getPosition().x + 4, toolPanel.getPosition().y + 58);
	scaleButTexture.setScale(22.0f / scaleButTexture.getLocalBounds().width, 22.0f / scaleButTexture.getLocalBounds().height);

	sf::RectangleShape playButton(sf::Vector2f(24, 24));
	playButton.setFillColor(sf::Color::White);
	playButton.setOutlineColor(sf::Color::Black);
	playButton.setOutlineThickness(1);
	playButton.setPosition(toolPanel.getPosition().x + 3, toolPanel.getPosition().y + 84);
	sf::Texture playTexture;
	if (!playTexture.loadFromFile("playButton.png")) {
		std::cerr << "Nie mo�na za�adowa� obrazka!" << std::endl;
	}
	sf::Sprite playButTexture(playTexture);
	playButTexture.setPosition(toolPanel.getPosition().x + 4, toolPanel.getPosition().y + 85);
	playButTexture.setScale(22.0f / playButTexture.getLocalBounds().width, 22.0f / playButTexture.getLocalBounds().height);

	// Zmienna przechowujaca informacje, czy wcisniety przycisk do przesuwania figur
	bool isMoveBut = false, isRotateBut = false, isScaleBut = false, isGameOn = false;
	float temp_x, temp_y, temp_angle, temp_factor;

	std::vector<sf::Vector2f> vertices = {
		sf::Vector2f(100, 50),
		sf::Vector2f(200, 100),
		sf::Vector2f(200, 200),
		sf::Vector2f(100, 150)
	};

	std::vector<Point2D> verticesPoint2d = {
		sf::Vector2f(200, 200),
		sf::Vector2f(400, 200),
		sf::Vector2f(295, 103),
		sf::Vector2f(235, 103),
		sf::Vector2f(295, 163),
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

			if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left) {
				sf::Vector2f mousePosition = window.mapPixelToCoords(sf::Vector2i(event.mouseButton.x, event.mouseButton.y));
				if (toolPanel.getGlobalBounds().contains(mousePosition)) {
					moveButton.setFillColor(sf::Color::White);
					rotateButton.setFillColor(sf::Color::White);
					scaleButton.setFillColor(sf::Color::White);
					playButton.setFillColor(sf::Color::White);
					isMoveBut = false;
					isRotateBut = false;
					isScaleBut = false;
					isGameOn = false;
					if (moveButton.getGlobalBounds().contains(mousePosition)) {
						moveButton.setFillColor(sf::Color(100, 100, 100));
						isMoveBut = true;
					}
					else if (rotateButton.getGlobalBounds().contains(mousePosition)) {
						rotateButton.setFillColor(sf::Color(100, 100, 100));
						isRotateBut = true;
					}
					else if (scaleButton.getGlobalBounds().contains(mousePosition)) {
						scaleButton.setFillColor(sf::Color(100, 100, 100));
						isScaleBut = true;
					}
					else if (playButton.getGlobalBounds().contains(mousePosition)) {
						isGameOn = true;
					}
				}
				else if (isMoveBut == true) {
					std::cout << "Wykorzystanie metody przesuniecia na przykladzie obiektu player" << std::endl;
					std::cout << "Wprowadz wartosc o jaka chcesz przesunac obiekt player w poziomie" << std::endl;
					std::cin >> temp_x;
					std::cout << "Wprowadz wartosc o jaka chcesz przesunac obiekt player w pionie" << std::endl;
					std::cin >> temp_y;
					player.translate(temp_x, temp_y);
				}
				else if (isRotateBut == true) {
					std::cout << "Wykorzystanie metody rotacji wzgledem srodka ekranu na przykladzie obiektu player" << std::endl;
					std::cout << "Wprowadz wartosc o jaka chcesz obrocic obiekt player" << std::endl;
					std::cin >> temp_angle;
					player.rotate(temp_angle);
				}
				else if (isScaleBut == true) {
					std::cout << "Wykorzystanie metody skalowania wzgledem srodka ekranu na przykladzie obiektu player" << std::endl;
					std::cout << "Wprowadz wartosc o jaka chcesz oddalic lub przyblizyc od srodka obiekt player" << std::endl;
					std::cin >> temp_factor;
					player.scale(temp_factor);
				}
			}
			if (isGameOn == true) {
				if (!fullscreen) {
					setFullscreen(true);
				}

				// Ustawienie ekranu na rozdzielczosc 800x600 skrotem ALT+R
				if (event.type == sf::Event::KeyPressed) {
					if (event.key.code == sf::Keyboard::Escape) {
						setFullscreen(false);
						setWindowSize(800, 600);
						isGameOn = false;
					}
				}

				// Obs�uga strza�ek na klawiaturze, kt�re przesuwaj� nasz obiekt rect
				if (event.type == sf::Event::KeyPressed) {
					if (event.key.code == sf::Keyboard::Left) {
						player.move(-5.f, 0.f);
						moveCounter++;
					}
					else if (event.key.code == sf::Keyboard::Right) {
						player.move(5.f, 0.f);
						moveCounter++;
					}
					else if (event.key.code == sf::Keyboard::Up) {
						player.move(0.f, -5.f);
						moveCounter++;
					}
					else if (event.key.code == sf::Keyboard::Down) {
						player.move(0.f, 5.f);
						moveCounter++;
					}
				}
				if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left) {
					sf::Vector2i mousePosition = sf::Mouse::getPosition(window);
					sf::Vector2f direction = sf::Vector2f(mousePosition) - sf::Vector2f(player.GameObject::getX(), player.GameObject::getY());
					float length = std::sqrt(direction.x * direction.x + direction.y * direction.y);

					// Normalizujemy wektor kierunku, aby uzyska� wektor jednostkowy
					if (length != 0) {
						direction /= length;
					}

					// Obliczamy punkt na obwodzie okr�gu, kt�ry b�dzie punktem pocz�tkowym przemieszczenia
					Bullet startPoint(player.GameObject::getX(), player.GameObject::getY(), direction, 5.0f);

					// Dop�ki punkt jest na ekranie, przesuwamy go w kierunku klikni�cia
					while (startPoint.getPoint().x >= 0 && startPoint.getPoint().x <= width && startPoint.getPoint().y >= 0 && startPoint.getPoint().y <= height) {
						// Aktualizujemy po�o�enie punktu
						startPoint.update();



						// Czy�cimy ekran do wylosowanego koloru
						window.clear(bgColor);
						// Wylczenie synchronizacji pionowej
						window.setVerticalSyncEnabled(true);

						//window.draw(moveText);
						//newLine.drawLine(50, 40, 400, 100,window, sf::Color::Red);
						//newLine.drawBrokenLine(verticesPoint2d, window, sf::Color::Yellow, false);
						//circle.drawCircle(400, 70, 50, window, sf::Color::Magenta);
						rectangle.drawSimplePolygon(verticesPoint2d, window, sf::Color::Magenta);
						//rectangle.drawPolygon(vertices, window, sf::Color::Red);
						//elipse.drawElipse(400, 300, 100, 50, window, sf::Color::Yellow);
						//rectangle.filledPolygon(vertices, window, sf::Color::Green);
						player.drawPlayer(50, 30, window, sf::Color::Blue);

						ptk.setPoint(100, 380);
						ptk2.setPoint(150, 200);
						ptk.draw(window, sf::Color::Cyan);
						ptk2.draw(window, sf::Color::Blue);

						// Rysujemy punkt
						startPoint.draw(window, sf::Color::Red);

						// wczytywanie bitmapy z pliku
						zaladujBitmape("bitmapa.png");

						// zapisywanie bitmapy do pliku
						//zapiszBitmape("nowa_bitmapa.png");

						// kopiowanie fragmentu bitmapy z silnika do samego siebie
						// skopiujBitmapyZSilnika(100, 100, 200, 200);

						// rysowanie bitmapy na ekranie
						bitmapa.rysujNaRenderWindow(window, 300, 300);

						// Wy�wietlamy wszystkie elementy
						window.display();
					}
				}
			}

			


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

		if (!isGameOn) {
			window.draw(toolPanel);
			window.draw(moveButton);
			window.draw(moveButTexture);
			window.draw(rotateButton);
			window.draw(rotateButTexture);
			window.draw(scaleButton);
			window.draw(scaleButTexture);
			window.draw(playButton);
			window.draw(playButTexture);
		}
		//window.draw(moveText);
		//newLine.drawLine(50, 40, 400, 100,window, sf::Color::Red);
		//newLine.drawBrokenLine(verticesPoint2d, window, sf::Color::Yellow, false);
		//circle.drawCircle(400, 70, 50, window, sf::Color::Magenta);
		rectangle.drawSimplePolygon(verticesPoint2d, window, sf::Color::Magenta);
		//rectangle.drawPolygon(vertices, window, sf::Color::Red);
		//elipse.drawElipse(400, 300, 100, 50, window, sf::Color::Yellow);
		//rectangle.filledPolygon(vertices, window, sf::Color::Green);
		player.drawPlayer(50, 30, window, sf::Color::Blue);

		ptk.setPoint(100, 380);
		ptk2.setPoint(150, 200);
		ptk.draw(window, sf::Color::Cyan);
		ptk2.draw(window, sf::Color::Blue);
		

		// wczytywanie bitmapy z pliku
		zaladujBitmape("bitmapa.png");

		// zapisywanie bitmapy do pliku
		//zapiszBitmape("nowa_bitmapa.png");

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