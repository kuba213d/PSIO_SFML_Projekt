#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <iostream>
#include <vector>
#include <map>
#include <sstream>
#include "Player.h"
#include "Kolizje.h"
//#include "ECTS.h"
#include "Mapa.h"
#include "Chmurki.h"
#include "CoinMap.h"
#include "STBlock.h"
#include <conio.h>
#include <Windows.h>

class Gra
{
public:
	//Gracz:
	Player* player;
	//Coiny:
	
	Coin* coin;
	sf::RenderWindow* window;
	sf::View* view;
	Level* level;
	STLevel* ST_level;
	sf::Event evnt;
	sf::Clock clock;
	sf::Clock clock2;
	std::map<char, sf::Texture*> GroundTextures;
	std::map<char, sf::Texture*> CoinTextures;
	std::map<char, sf::Texture*> ST_textures;
	float VIEW_HEIGHT = 640.0f;
	sf::Vector2f direction;
	sf::Vector2f direction2;
	sf::Vector2f direction3;
	float deltaTime = 0.0f;
	//Tekstury:
	sf::Texture playerTexture;
	// old coin:  sf::Texture coinTexture;
	Collider col = player->GetCollider();
	sf::Texture tlo;
	sf::Sprite Tlo;
	//Bloki:
	sf::Texture* grass = new sf::Texture;
	sf::Texture* water = new sf::Texture;
	sf::Texture* wall = new sf::Texture;
	sf::Texture* box = new sf::Texture;
	sf::Texture* stone = new sf::Texture;
	sf::Texture* coinT = new sf::Texture;
	//Wektor coin�w:
	std::vector<Coin*> coinVec;
	//Rzeczy do licznika punkt�w:
	std::ostringstream ssScore;
	sf::Text Score;
	sf::Font font;
	sf::Time elapsed1 = clock2.getElapsedTime();
	sf::Text licznik;
	std::ostringstream Zegar;
	int score = 0;
	float c = 0.0f;
	//D�wi�ki:
	sf::SoundBuffer coinsound;
	sf::Sound sound1;
	std::vector<std::unique_ptr<RuchomySprite>> alien;
	sf::Clock clock3;
	sf::Time elapsed3;


	Gra();
	~Gra();
	void wysPunkty();
	void loadTextures();
	void loadData();
	void Chmurki();
	//void TworzCoin();
	void Czas();
	bool Run();
	void Update();
	void Render();
	void Licznik();
	void CheckCollision(sf::Vector2f& direction, float p);
	void CheckCollisionST(sf::Vector2f& direction, float p);
	void CoinCollision(sf::Vector2f& direction, float p);
	//bool isCollidingWithCoin(std::vector<Coin*> &coinVec);


};

	

