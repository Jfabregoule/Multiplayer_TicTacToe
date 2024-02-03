#include <iostream>
#include <SFML/Graphics.hpp>

#include "GameManager.h"
#include "GameWindow.h"
#include "GameObject.h"

GameManager::GameManager() {

	m_window = new GameWindow();
	m_icon = new sf::Image();

	m_running = true;

	m_currentTurn = 0;
}

/*
---------------------------------------------------------------------------------
|				Here are all the window related methods							|
---------------------------------------------------------------------------------
*/

void GameManager::SetIcon() {
	if (!m_icon->loadFromFile("rsrc/img/icon/icon.png"))
	{
		std::cout << "Error loading icon" << std::endl;
		exit(1);
	}
	m_window->w_window->setIcon(m_icon->getSize().x, m_icon->getSize().y, m_icon->getPixelsPtr());
}

void	GameManager::CloseWindow() {
	m_window->w_window->close();
	exit(0);
}

void GameManager::DrawTerrain() {
	sf::RectangleShape collumn1(sf::Vector2f(600.0f, 5.f));
	collumn1.setPosition(197.5f, 0.0f);
	collumn1.rotate(90.0f);
	m_window->w_window->draw(collumn1);

	sf::RectangleShape collumn2(sf::Vector2f(600.0f, 5.f));
	collumn2.setPosition(397.5f, 0.0f);
	collumn2.rotate(90.0f);
	m_window->w_window->draw(collumn2);

	sf::RectangleShape line1(sf::Vector2f(600.0f, 5.f));
	line1.setPosition(0.0f, 197.5f);
	m_window->w_window->draw(line1);

	sf::RectangleShape line2(sf::Vector2f(600.0f, 5.f));
	line2.setPosition(0.0f, 397.5f);
	m_window->w_window->draw(line2);
}

void GameManager::DrawBoard() {
	int j = 0;

	float	posX = 98.75f;
	float	posY = 98.75f;

	sf::Sprite currentSprite;

	for (int i = 0; i < 3; i++)
	{
		for (int j = 0; j < 3; j++)
		{
			std::cout << m_map[i][j] << std::endl;
			switch (m_map[i][j])
			{
				case '0':
					return;
				case 'x':
					currentSprite = *m_sprites.at(0);
					break;
				case '.':
					currentSprite = *m_sprites.at(1);
					break;
			}
			currentSprite.setOrigin(75.0f, 75.0f);
			currentSprite.setPosition(posX, posY);
			m_window->w_window->draw(currentSprite);
			posX += 200;
		}
		posX = 98.75f;
		posY += 200;
	}
}

void GameManager::RefreshWindow() {
	m_window->RefreshScreen();
	DrawTerrain();
	DrawBoard();
	m_window->w_window->display();
}

/*
---------------------------------------------------------------------------------
|				Here are all the generation methods								|
---------------------------------------------------------------------------------
*/

void GameManager::GenerateSprites() {
	sf::Texture* crossTexture = new sf::Texture();
	sf::Texture* circleTexture = new sf::Texture();
	if (!crossTexture->loadFromFile("rsrc/img/objects/cross.png") or !circleTexture->loadFromFile("rsrc/img/objects/circle.png")){
		std::cout << "Error loading object textures." << std::endl;
		exit(1);
	}

	sf::Sprite* crossSprite = new sf::Sprite();
	crossSprite->setTexture(*crossTexture);
	m_sprites.push_back(crossSprite);

	sf::Sprite* circleSprite = new sf::Sprite();
	circleSprite->setTexture(*circleTexture);
	m_sprites.push_back(circleSprite);
}

void GameManager::GenerateMap() {
	int	j = 0;

	for (int i = 0; i < 3; i++)
	{
		for (j; j < 3; j++)
		{
			m_map[i][j] = '0';
		}
		m_map[i][j] = '\0';
		j = 0;
	}
}

void GameManager::Generate() {
	GenerateSprites();
	GenerateMap();

	//GenerateTerrain();
	//GenerateHud();
	//PlayMusic();
}

void GameManager::HandleEvents() {
	Event event;

	while (m_window->w_window->pollEvent(event))
	{
		if (event.type == Event::Closed)
			CloseWindow();
		if (Mouse::isButtonPressed(Mouse::Button::Left) and m_window->w_window->hasFocus()) {

		}
	}
}

void GameManager::Start() {
	float	fps = 0;

	SetIcon();
	Generate();

	while (m_running)
	{
		HandleEvents();
		RefreshWindow();
		//EndCheck();
		//LimitFps(fps);
	}
	//EndGame();
}
