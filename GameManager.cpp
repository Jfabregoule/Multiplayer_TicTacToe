#include <iostream>
#include <SFML/Graphics.hpp>

#include "GameManager.h"
#include "GameWindow.h"

GameManager::GameManager() {

	m_window = new GameWindow();
	m_icon = new sf::Image();

	m_running = true;

	m_currentTurn = 0;
	m_currentPlayer = 1;

	m_Clock = new sf::Clock();
	m_deltaTime = 0.f;
	m_fpsLimit = 1.0f / 120.0f;
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

void GameManager::LimitFps(float fps) {
	m_deltaTime = m_Clock->restart().asSeconds();
	if (m_deltaTime < m_fpsLimit) {
		sleep(seconds(m_fpsLimit - m_deltaTime));
		m_deltaTime += m_fpsLimit - m_deltaTime;
	}
	fps = 1.0f / m_deltaTime;
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

	sf::RectangleShape row1(sf::Vector2f(600.0f, 5.f));
	row1.setPosition(0.0f, 197.5f);
	m_window->w_window->draw(row1);

	sf::RectangleShape row2(sf::Vector2f(600.0f, 5.f));
	row2.setPosition(0.0f, 397.5f);
	m_window->w_window->draw(row2);
}

void GameManager::DrawBoard() {
	int		j = 0;
	bool	isEmpty = true;

	float	posX = 98.75f;
	float	posY = 98.75f;

	sf::Sprite currentSprite;

	for (int i = 0; i < 3; i++)
	{
		for (int j = 0; j < 3; j++)
		{
			switch (m_map[i][j])
			{
				case '0':
					isEmpty = true;
					break;
				case 'x':
					isEmpty = false;
					currentSprite = *m_sprites.at(0);
					break;
				case '.':
					isEmpty = false;
					currentSprite = *m_sprites.at(1);
					break;
			}
			if (!isEmpty)
			{
				currentSprite.setOrigin(75.0f, 75.0f);
				currentSprite.setPosition(posX, posY);
				m_window->w_window->draw(currentSprite);
			}
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

	//GenerateHud();
	//PlayMusic();
}

void GameManager::Place() {
	char			c;
	char			*toReplace = nullptr;
	sf::Vector2i	position = sf::Mouse::getPosition(*m_window->w_window);

	int i = -1, j = -1;
	if (m_currentPlayer == 1)
		c = 'x';
	else
		c = '.';
	if (position.x <= 197.5)
		j = 0;
	else if (position.x >= 202.5 and position.x <= 397.5)
		j = 1;
	else if (position.x >= 402.5)
		j = 2;

	if (position.y <= 197.5)
		i = 0;
	else if (position.y >= 202.5 and position.y <= 397.5)
		i = 1;
	else if (position.y >= 402.5)
		i = 2;

	if (i != -1 && j != -1 && m_map[i][j] == '0') {
		toReplace = &m_map[i][j];
		*toReplace = c;

		if (m_currentPlayer == 1)
			m_currentPlayer = 2;
		else
			m_currentPlayer = 1;
	}
}

void GameManager::EndCheck() {
	// Check rows
	for (int i = 0; i < 3; i++) {
		if (m_map[i][0] == 'x' && m_map[i][1] == 'x' && m_map[i][2] == 'x') {
			m_running = false;
			std::cout << "Player 1 wins!" << std::endl;
			return;
		}
		if (m_map[i][0] == '.' && m_map[i][1] == '.' && m_map[i][2] == '.') {
			m_running = false;
			std::cout << "Player 2 wins!" << std::endl;
			return;
		}
	}

	// Check columns
	for (int j = 0; j < 3; j++) {
		if (m_map[0][j] == 'x' && m_map[1][j] == 'x' && m_map[2][j] == 'x') {
			m_running = false;
			std::cout << "Player 1 wins!" << std::endl;
			return;
		}
		if (m_map[0][j] == '.' && m_map[1][j] == '.' && m_map[2][j] == '.') {
			m_running = false;
			std::cout << "Player 2 wins!" << std::endl;
			return;
		}
	}

	// Check diagonals
	if ((m_map[0][0] == 'x' && m_map[1][1] == 'x' && m_map[2][2] == 'x') ||
		(m_map[0][2] == 'x' && m_map[1][1] == 'x' && m_map[2][0] == 'x')) {
		m_running = false;
		std::cout << "Player 1 wins!" << std::endl;
		return;
	}
	if ((m_map[0][0] == '.' && m_map[1][1] == '.' && m_map[2][2] == '.') ||
		(m_map[0][2] == '.' && m_map[1][1] == '.' && m_map[2][0] == '.')) {
		m_running = false;
		std::cout << "Player 2 wins!" << std::endl;
		return;
	}
}

void GameManager::HandleEvents() {
	Event event;

	while (m_window->w_window->pollEvent(event))
	{
		if (event.type == Event::Closed)
			CloseWindow();
		if (Mouse::isButtonPressed(Mouse::Button::Left) and m_window->w_window->hasFocus()) {
			Place();
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
		EndCheck();
		LimitFps(fps);
	}
	//EndGame();
}
