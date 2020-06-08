#include "Game.h"
#include "Coin.h"

Game::Game()
{
	window = new sf::RenderWindow(sf::VideoMode(1024, 640), "POLIBUDA", sf::Style::Close | sf::Style::Resize);
	loadData();
	view = new sf::View(sf::Vector2f(0.0f, 0.0f), sf::Vector2f(1024, 640));
	level = new Level(GroundTextures);
	player = new Player(&playerTexture, sf::Vector2u(3, 8), 0.1f, 200.0f, 320.0f);
	
}
Game::~Game()
{
	delete one;
}
void Game::loadTextures()
{
	playerTexture.loadFromFile("spritesheet3.png");

	coinTexture.loadFromFile("CoinSheet.png");

	tlo.loadFromFile("tlo3.jpg");

	one = new sf::Texture;
	one->loadFromFile("1.png");
	GroundTextures['G'] = one;

	one = new sf::Texture;
	one->loadFromFile("2.png");
	GroundTextures['D'] = one;

	one = new sf::Texture;
	one->loadFromFile("3.png");
	GroundTextures['X'] = one;

	one = new sf::Texture;
	one->loadFromFile("4.png");
	GroundTextures['B'] = one;
}
void Game::loadData()
{
	loadTextures();
	TworzCoin();
	Czas();
	wysPunkty();
}
void Game::Czas()
{
	Zegar.clear();
	clock2.restart();
	c += elapsed1.asSeconds();
	Zegar << "Czas: " << c;
}
bool Game::Run()
{
	return window->isOpen();
}
void Game::wysPunkty()
{
	if (score == 0) ssScore << "Punkty ECTS: " << "[" << score << "]";
}
void Game::Update()
{
	window->setFramerateLimit(30);
	deltaTime = clock.restart().asSeconds();
	if (deltaTime > 1.0f / 20.0f)
		deltaTime = 1.0f / 20.0f;
	while (window->pollEvent(evnt)) {

		switch (evnt.type) {

		case sf::Event::Closed:
			window->close();
			break;
		}
	}
	
	player->Update(deltaTime);
	CheckCollision(direction, 1.0f);
	
}
void Game::TworzCoin()
{
	coinVec.push_back(coin1);
	coinVec.push_back(coin2);
	coinVec.push_back(coin3);
	coinVec.push_back(coin4);

	coin1.setPos({ 420, 230 });
	coin2.setPos({ 580, 230 });
	coin3.setPos({ 360, 420 });
	coin4.setPos({ 220, 70 });

	coin1.Draw(*window);
	coin2.Draw(*window);
	coin3.Draw(*window);
	coin4.Draw(*window);
}
void Game::Render()
{
	

	Tlo.setTexture(tlo);
	view->setCenter(player->GetPosition());
	window->clear();
	window->draw(Tlo);
	window->setView(*view);
	Tlo.setPosition(view->getCenter().x - 512, view->getCenter().y - 320);
	
	
	for (int i = 0; i < level->Matrix.size(); i++)
	{
		for (int j = 0; j < level->Matrix[i].size(); j++)
		{
			window->draw(level->Matrix[i][j]);
		}
	}
	Licznik();
	

	player->Draw(*window);
	window->display();
}
void Game::Usun(int&i)
{
	coinVec[i]->setPos({ 422234, 423432 });
}
void Game::Licznik()
{
	font.loadFromFile("font.ttf");

	licznik.setCharacterSize(35);
	licznik.setFillColor(sf::Color::Red);
	licznik.setFont(font);
	licznik.setString(Zegar.str());
	licznik.setPosition(view->getCenter().x - 512, view->getCenter().y - 180);
	
	Score.setCharacterSize(45);
	Score.setFillColor(sf::Color::Red);
	Score.setFont(font);
	Score.setString(ssScore.str());
	Score.setPosition(view->getCenter().x - 512, view->getCenter().y - 280);

	for (int i = 0; i < coinVec.size(); i++) {
		if (player->isCollidingWithCoin(coinVec[i])) {
			Usun(i);
			score++;
			ssScore.str("");
			ssScore << "Punkty ECTS: " << "[" << score << "]";
			Score.setString(ssScore.str());
		}
	}

	window->draw(Score);
	window->draw(licznik);
	
}
void Game::CheckCollision(sf::Vector2f& direction, float p)
{
	float deltax;
	float deltay;
	float intersectX;
	float intersectY;

	for (size_t i = 0; i < this->level->Matrix.size(); i++)
	{
		for (size_t j = 0; j < this->level->Matrix[i].size(); j++)
		{
			sf::Vector2f thisposition = this->level->Matrix[i][j].getPosition();
			sf::Vector2f otherposition = this->player->GetPosition();
			sf::Vector2f thishalfsize(this->level->Matrix[i][j].getGlobalBounds().width / 2.0f, level->Matrix[i][j].getGlobalBounds().height / 2.0f);
			sf::Vector2f otherhalfsize = this->player->body.getSize() / 2.0f;

			bool t;

			deltax = otherposition.x - thisposition.x;
			deltay = otherposition.y - thisposition.y;

			intersectX = std::abs(deltax) - (otherhalfsize.x + thishalfsize.x);
			intersectY = std::abs(deltay) - (otherhalfsize.y + thishalfsize.y);

			if (intersectX < 0.0f && intersectY < 0.0f)
			{
				p = std::min(std::max(p, 0.0f), 1.0f);

				if (intersectX > intersectY)
				{
					if (deltax > 0.0f)
					{
						this->level->Matrix[i][j].move(intersectX * (1.0f - p), 0.0f);
						this->player->body.move(-intersectX * p, 0.0f);

						direction.x = 1.0f;
						direction.y = 0.0f;
					}
					else
					{
						this->level->Matrix[i][j].move(-intersectX * (1.0f - p), 0.0f);
						this->player->body.move(intersectX * p, 0.0f);

						direction.x = -1.0f;
						direction.y = 0.0f;
					}
				}
				else
				{
					if (deltay > 0.0f)
					{
						this->level->Matrix[i][j].move(0.0f, intersectY * (1.0f - p));
						this->player->body.move(0.0f, -intersectY * p);

						direction.x = 0.0f;
						direction.y = 1.0f;
					}
					else
					{
						this->level->Matrix[i][j].move(0.0f, -intersectY * (1.0f - p));
						this->player->body.move(0.0f, intersectY * p);

						direction.x = 0.0f;
						direction.y = -1.0f;
					}
				}

				t = true;

			}
			else {
				t = false;
			}
			if (t == true)
			{
				this->player->OnCollision(direction);
			}
		}

	}
	
}
