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

// Metoda wczytuj¹ca t³o z pliku
bool Engine::loadBackground(const std::string& filename)
{
	// Wczytywanie tekstury t³a z pliku o podanej nazwie (filename)
	if (!backgroundTexture.loadFromFile(filename))
	{
		std::cerr << "Blad wczytywania tekstury tla." << std::endl;
		return false;
	}

	// Jeœli wczytanie tekstury t³a zakoñczy³o siê sukcesem, ustaw teksturê na sprajcie t³a (backgroundSprite)
	backgroundSprite.setTexture(backgroundTexture);

	return true;
}

// Metoda rysuj¹ca t³o
void Engine::drawBackground()
{
	// Jeœli t³o nie jest zainicjowane, nie rysuj
	if (!backgroundTexture.getSize().x)
		return;

	// Rysuj t³o
	window.draw(backgroundSprite);
}

<<<<<<< Updated upstream
void Engine::skopiujBitmapyZSilnika(int x, int y, int szerokosc, int wysokosc) {
	bitmapa.skopiujZBitmapy(bitmapa, x, y, szerokosc, wysokosc); // Wywoï¿½anie metody z obiektu bitmapy
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

	sf::RectangleShape toolPanel(sf::Vector2f(30, 246));
	toolPanel.setFillColor(sf::Color(200, 200, 200));
	
	sf::RectangleShape moveButton(sf::Vector2f(24, 24));
	moveButton.setFillColor(sf::Color::White);
	moveButton.setOutlineColor(sf::Color::Black);
	moveButton.setOutlineThickness(1);
	moveButton.setPosition(toolPanel.getPosition().x + 3, toolPanel.getPosition().y + 3);
	sf::Texture moveTexture;
	if (!moveTexture.loadFromFile("moveButton.png")) {
		std::cerr << "Nie moï¿½na zaï¿½adowaï¿½ obrazka!" << std::endl; 
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
		std::cerr << "Nie moï¿½na zaï¿½adowaï¿½ obrazka!" << std::endl;
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
		std::cerr << "Nie moï¿½na zaï¿½adowaï¿½ obrazka!" << std::endl;
	}
	sf::Sprite scaleButTexture(scaleTexture);
	scaleButTexture.setPosition(toolPanel.getPosition().x + 4, toolPanel.getPosition().y + 58);
	scaleButTexture.setScale(22.0f / scaleButTexture.getLocalBounds().width, 22.0f / scaleButTexture.getLocalBounds().height);

	sf::RectangleShape whiteButton(sf::Vector2f(24, 24));
	whiteButton.setFillColor(sf::Color::White);
	whiteButton.setOutlineColor(sf::Color::Black);
	whiteButton.setOutlineThickness(1);
	whiteButton.setPosition(toolPanel.getPosition().x + 3, toolPanel.getPosition().y + 84);

	sf::RectangleShape blackButton(sf::Vector2f(24, 24));
	blackButton.setFillColor(sf::Color::Black);
	blackButton.setOutlineColor(sf::Color::Black);
	blackButton.setOutlineThickness(1);
	blackButton.setPosition(toolPanel.getPosition().x + 3, toolPanel.getPosition().y + 111);

	sf::RectangleShape greenButton(sf::Vector2f(24, 24));
	greenButton.setFillColor(sf::Color::Green);
	greenButton.setOutlineColor(sf::Color::Black);
	greenButton.setOutlineThickness(1);
	greenButton.setPosition(toolPanel.getPosition().x + 3, toolPanel.getPosition().y + 138);

	sf::RectangleShape playButton(sf::Vector2f(24, 24));
	playButton.setFillColor(sf::Color::White);
	playButton.setOutlineColor(sf::Color::Black);
	playButton.setOutlineThickness(1);
	playButton.setPosition(toolPanel.getPosition().x + 3, toolPanel.getPosition().y + 165);
	sf::Texture playTexture;
	if (!playTexture.loadFromFile("playButton.png")) {
		std::cerr << "Nie moï¿½na zaï¿½adowaï¿½ obrazka!" << std::endl;
	}
	sf::Sprite playButTexture(playTexture);
	playButTexture.setPosition(toolPanel.getPosition().x + 4, toolPanel.getPosition().y + 166);
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
=======


void Engine::run() {

	sf::RenderWindow& window = getWindow();

	// Tworzymy tekstury dla ka¿dej klatki animacji (dla nazw "down1.png", "up2.png", itd.)
	std::vector<sf::Texture> downFrames, upFrames, leftFrames, rightFrames;
	// Dodajemy po cztery klatki animacji dla ka¿dego kierunku
	for (int i = 1; i <= 4; ++i) {
		sf::Texture texture;
		texture.loadFromFile("down" + std::to_string(i) + ".png");
		downFrames.push_back(texture);
	}
	for (int i = 1; i <= 4; ++i) {
		sf::Texture texture;
		texture.loadFromFile("up" + std::to_string(i) + ".png");
		upFrames.push_back(texture);
	}
	for (int i = 1; i <= 4; ++i) {
		sf::Texture texture;
		texture.loadFromFile("left" + std::to_string(i) + ".png");
		leftFrames.push_back(texture);
	}
	for (int i = 1; i <= 4; ++i) {
		sf::Texture texture;
		texture.loadFromFile("right" + std::to_string(i) + ".png");
		rightFrames.push_back(texture);
	}
>>>>>>> Stashed changes

	if (!loadBackground("background.jpg"))
	{
		std::cerr << "Failed to load background." << std::endl;
		return;
	}

	// Dodajemy animacje dla ka¿dego kierunku do AnimationHandler
	animationHandler.addAnimation(downFrames);
	animationHandler.addAnimation(upFrames);
	animationHandler.addAnimation(leftFrames);
	animationHandler.addAnimation(rightFrames);

	// Pozycja postaci na ekranie
	float characterX = 400.0f;
	float characterY = 300.0f;
	float characterSpeed = 5.0f; // Szybkoœæ poruszania postaci

	window.setVerticalSyncEnabled(true);

	// Deklaracja zmiennych (flag) z informacj¹ o wciœniêciu danego klawisza
	bool leftKeyPressed = false;
	bool rightKeyPressed = false;
	bool upKeyPressed = false;
	bool downKeyPressed = false;

	while (window.isOpen()) {
		sf::Event event;
		window.setFramerateLimit(limitFramrate);
		
		//Nasluchiwnie zdarzen
		while (window.pollEvent(event)) {
			if (event.type == sf::Event::Closed) {
				window.close();
<<<<<<< Updated upstream
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
					else if (whiteButton.getGlobalBounds().contains(mousePosition)) {
						bgColor = sf::Color::White;
					}
					else if (blackButton.getGlobalBounds().contains(mousePosition)) {
						bgColor = sf::Color::Black;
					}
					else if (greenButton.getGlobalBounds().contains(mousePosition)) {
						bgColor = sf::Color::Green;
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

				// Obsï¿½uga strzaï¿½ek na klawiaturze, ktï¿½re przesuwajï¿½ nasz obiekt rect
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

					// Normalizujemy wektor kierunku, aby uzyskaï¿½ wektor jednostkowy
					if (length != 0) {
						direction /= length;
					}

					// Obliczamy punkt na obwodzie okrï¿½gu, ktï¿½ry bï¿½dzie punktem poczï¿½tkowym przemieszczenia
					Bullet startPoint(player.GameObject::getX(), player.GameObject::getY(), direction, 5.0f);

					// Dopï¿½ki punkt jest na ekranie, przesuwamy go w kierunku klikniï¿½cia
					while (startPoint.getPoint().x >= 0 && startPoint.getPoint().x <= width && startPoint.getPoint().y >= 0 && startPoint.getPoint().y <= height) {
						// Aktualizujemy poï¿½oï¿½enie punktu
						startPoint.update();



						// Czyï¿½cimy ekran do wylosowanego koloru
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

						// Wyï¿½wietlamy wszystkie elementy
						window.display();
					}
				}
			}
		}

		// Czyszczenie ekranu do zadanego koloru (np. jasnoniebieski)
		//window.clear(sf::Color(135, 206, 250));
		// Czyï¿½cimy ekran do wylosowanego koloru
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
			window.draw(whiteButton);
			window.draw(blackButton);
			window.draw(greenButton);
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
		
=======
			}
			else if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Left) {
				leftKeyPressed = true; // Ustaw flagê na true, gdy klawisz jest wciœniêty
				characterX -= characterSpeed; // Przesuniêcie postaci w lewo
				if (animationHandler.getWasUpdated(2)) {
					animationHandler.play(2, sf::seconds(0.2)); // Rozpocznij odtwarzanie animacji
				}
			}
			else if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Right) {
				rightKeyPressed = true; // Ustaw flagê na true, gdy klawisz jest wciœniêty
				characterX += characterSpeed; // Przesuniêcie postaci w prawo
				if (animationHandler.getWasUpdated(3)) {
					animationHandler.play(3, sf::seconds(0.2)); // Rozpocznij odtwarzanie animacji
				}
			}
			else if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Up) {
				upKeyPressed = true; // Ustaw flagê na true, gdy klawisz jest wciœniêty
				characterY -= characterSpeed; // Przesuniêcie postaci w górê
				if (animationHandler.getWasUpdated(1)) {
					animationHandler.play(1, sf::seconds(0.2)); // Rozpocznij odtwarzanie animacji
				}
			}
			else if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Down) {
				downKeyPressed = true; // Ustaw flagê na true, gdy klawisz jest wciœniêty
				characterY += characterSpeed; // Przesuniêcie postaci w dó³
				if (animationHandler.getWasUpdated(0)) {
					animationHandler.play(0, sf::seconds(0.2)); // Rozpocznij odtwarzanie animacji
				}
			}
			else if (event.type == sf::Event::KeyReleased) {
				leftKeyPressed = false;
				rightKeyPressed = false;
				upKeyPressed = false;
				downKeyPressed = false;
				// Zatrzymaj odtwarzanie animacji
				animationHandler.stop(0); 
				animationHandler.stop(1); 
				animationHandler.stop(2); 
				animationHandler.stop(3); 
			}
		}

		// Sprawdzenie odleg³oœci od krawêdzi
		if (characterX < 75) {
			// Zatrzymywanie postaci na lewej krawêdzi
			characterX = 75.0f;

			// Przesuwanie t³a w prawo
			if (backgroundSprite.getPosition().x < 0) {
				backgroundSprite.move(characterSpeed, 0);
			}
		}
>>>>>>> Stashed changes

		else if (characterX > width - 150) {
			// Zatrzymywanie postaci na prawej krawêdzi
			characterX = static_cast<float>(width - 150);

<<<<<<< Updated upstream
		// zapisywanie bitmapy do pliku
		//zapiszBitmape("nowa_bitmapa.png");
=======
			// Przesuwanie t³a w lewo
			if (backgroundSprite.getPosition().x + backgroundTexture.getSize().x > width) {
				backgroundSprite.move(-characterSpeed, 0);
			}
		}
>>>>>>> Stashed changes

		if (characterY < 75) {
			// Zatrzymywanie postaci na górnej krawêdzi
			characterY = 75.0f;

			// Przesuwanie t³a w dó³
			if (backgroundSprite.getPosition().y < 0) {
				backgroundSprite.move(0, characterSpeed);
			}
		}
		else if (characterY > height - 150) {
			// Zatrzymywanie postaci na dolnej krawêdzi
			characterY = static_cast<float>(height - 150);

			// Przesuwanie t³a w górê
			if (backgroundSprite.getPosition().y + backgroundTexture.getSize().y > height) {
				backgroundSprite.move(0, -characterSpeed);
			}
		}
		
		// Sprawdzenie, czy ¿aden klawisz strza³ki nie jest naciœniêty
		if (!leftKeyPressed && !rightKeyPressed && !upKeyPressed && !downKeyPressed) {
			if (animationHandler.getWasUpdated(0)) {
				// Rozpocznij odtwarzanie animacji poruszania siê w dó³
				animationHandler.play(0, sf::seconds(0.2));
			}
		}

		// Pêtla iteruj¹ca po wszystkich kierunkach
		for (int i = 0; i < 4; ++i) {
			// Sprawdzenie, czy dla danego kierunku (i) odpowiadaj¹cy klawisz strza³ki jest naciœniêty
			if ((i == 0 && downKeyPressed) ||
				(i == 1 && upKeyPressed) ||
				(i == 2 && leftKeyPressed) ||
				(i == 3 && rightKeyPressed)) {
				// Zaktualizuj animacjê dla tego kierunku
				animationHandler.update(i);
			}
		}
		
        clearScreen(window);

		// Rysuj t³o
		drawBackground();

		// Sprawdzenie, czy ¿aden klawisz strza³ki nie jest naciœniêty
		if (!leftKeyPressed && !rightKeyPressed && !upKeyPressed && !downKeyPressed) {
			// Rysuj klatkê animacji poruszania siê w dó³
			animationHandler.draw(window, 0, characterX, characterY);
		}

		// Pêtla iteruj¹ca po wszystkich kierunkach
		for (int i = 0; i < 4; ++i) {
			if ((i == 0 && downKeyPressed) ||
				(i == 1 && upKeyPressed) ||
				(i == 2 && leftKeyPressed) ||
				(i == 3 && rightKeyPressed)) {
				// Rysuj animacjê dla tego kierunku
				animationHandler.draw(window, i, characterX, characterY);
			}
		}
	
<<<<<<< Updated upstream

		/* Naszï¿½ scenï¿½ tworzymy wiï¿½c na buforze, ktï¿½rego zawartoï¿½ï¿½ jest automatycznie kopiowana na ekran w chwili wywoï¿½ania metody display
		W SFML zarzadzanie technika wielokrotnego buforowania nastepuje automatycznie
		*/
		window.display();

		//std::cout << "Czas trwania klatki: " << deltaTime.asSeconds() << " sekundy" << std::endl;
=======
        window.display();
>>>>>>> Stashed changes
	}
}


int main()
{
    Engine& engine = Engine::getInstance(800, 600, false);
    engine.setLimit(30);
    engine.run();

    return 0;
}