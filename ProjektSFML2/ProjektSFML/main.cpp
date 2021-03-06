#include <SFML/Graphics.hpp>
#include "Gra.h"
#include "Chmurki.h"
#include "Menu.h"


void sterowanie()
{
	sf::RenderWindow window(sf::VideoMode(800, 800), "Sterowanie");
	sf::Texture texture3;
	texture3.loadFromFile("Textures/tlo_sterowanie.png");
	sf::Sprite sprite3;
	sprite3.setTexture(texture3);
	sprite3.setPosition(0, 0);
	sf::Image icon;
	icon.loadFromFile("Textures/ikona_gra.png");
	window.setIcon(64, 64, icon.getPixelsPtr());
	sf::Event evnt;
	while (window.isOpen())
	{
		while (window.pollEvent(evnt)) {

			switch (evnt.type) {

			case sf::Event::Closed:
				window.close();
				break;
			}
		}
		
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
		{
			window.close();
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
		{
			window.clear();
			texture3.loadFromFile("Textures/tlo_sterowanie2.jpg");
			window.display();
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
		{
			window.clear();
			texture3.loadFromFile("Textures/tlo_sterowanie.png");
			window.display();
		}
		window.clear();
		window.draw(sprite3);
		window.display();
	}
}
	
int main()
{
	int win;
	std::cout << "Zeby nie musial Pan przechodzic calej gry zeby zobaczyc ekran wygranej, prosze wpisac liczbe (maks 14) punktow po ktorej zdobyciu ma nastapic wygrana:  "<<std::endl;
	cin >> win;
	std::cout << "================================================================" << std::endl;
	std::cout << "Gra polega na przeszukiwaniu mapy w poszukiwaniu zlotych monet ('ECTS'). Podczas gry trzeba uwazac na wrogow, kontakt z nimi zabiera czesc zycia." ;
	std::cout << "Obecny stan zycia okresla 'Ocena', jej poczatkowa wartosc to BDB.Wrogow mozna pokonac atakujac ich w stylu 'Mario', czyli skaczac na nich." ;
	std::cout << "Gra konczy sie po zdobyciu wszystkich monet ECTS(maksymalnie 14, jednak mozna zmienic ta wartosc)";
	std::cout << "Koncowa punktacja zalezy od czasu w jakim zdobylo sie wymagane monety, oraz poziom zycia ('Ocena') z jaka gracz ukonczyl gre. " << std::endl;

	sf::RenderWindow window(sf::VideoMode(600, 600), "Gra MENU");
	sf::Clock clock;
	sf::Time elapsed;
	srand(time(NULL));

	

	Menu menu(window.getSize().x, window.getSize().y);
	sf::Texture texture;
	texture.loadFromFile("Textures/background.png");
	sf::Sprite sprite;
	sprite.setTexture(texture);
	sprite.setPosition(0, 0);

	sf::Texture texture2;
	texture2.loadFromFile("Textures/background2.png");
	sf::Sprite sprite2;
	sprite2.setTexture(texture2);
	sprite2.setPosition(0, 0);

	sf::SoundBuffer MenuSound;
	sf::Sound menu_sound;
	if (!MenuSound.loadFromFile("Sounds/menusound.wav"))
	{
		std::cout << "Problem z zaladowaniem dzwieku nr. 1";
	}
	menu_sound.setBuffer(MenuSound);

	sf::SoundBuffer MenuEnter;
	sf::Sound menu_enter;
	if (!MenuEnter.loadFromFile("Sounds/entermenu.ogg"))
	{
		std::cout << "Problem z zaladowaniem dzwieku nr. 1";
	}
	menu_enter.setBuffer(MenuEnter);

	std::vector<std::unique_ptr<RuchomySprite>> alien;

	for (int i = 0; i < 2; i++)
	{
		alien.emplace_back(std::make_unique<Duch>("Textures/chmurka.png"));
	}
	float pleaceX;
	float pleaceY;
	int direction;

	for (size_t i = 0; i < alien.size(); i++)
	{
		
		if (i == 1)
		{
			pleaceX = 30;
			pleaceY = 100;
		}
		else
		{
			pleaceX = 500;
			pleaceY = 50;
		}
		alien[i]->setPosition(pleaceX, pleaceY);
	}

	while (window.isOpen())
	{
		sf::Event event;
		elapsed = clock.restart();

		while (window.pollEvent(event))
		{
			switch (event.type)
			{
			case sf::Event::KeyReleased:
				
				switch (event.key.code)
				{
				case sf::Keyboard::Up:
					menu_sound.play();
					menu.MoveUp();
					break;

				case sf::Keyboard::Down:
					menu_sound.play();
					menu.MoveDown();
					break;

				case sf::Keyboard::Return:
					menu_enter.play();
					switch (menu.GetPressedItem())
					{
					case 0:
					{
						
						Gra* gra = new Gra(win);
						while (gra->Run())
						{
							gra->Update();
							gra->Render();
						}
					}
						break;
					case 1:
					{
						sterowanie();
					}
						break;
					case 2:
						window.close();
						break;
					}

					break;
				}

				break;
			case sf::Event::Closed:
				window.close();

				break;

			}
		}
		for (size_t i = 0; i < alien.size(); i++)
		{
			alien[i]->Animuj2(elapsed);
		}


		window.clear();
		window.draw(sprite);
		for (size_t i = 0; i < alien.size(); i++)
		{
			window.draw(*alien[i]);
		}
		window.draw(sprite2);
		menu.draw(window);
		window.display();
	}
}