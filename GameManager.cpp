#include <iostream>
#include <fstream>
#include <SFML/Graphics.hpp>

#include "GameManager.h"
#include "GameWindow.h"
#include <json/json.h>

const float INPUT_BLOCK_TIME = 0.8f;

GameManager::GameManager() {

	m_window = new GameWindow();
	m_icon = new sf::Image();

	m_endScreen = false;
	m_menu = true;
	m_running = true;

	m_currentTurn = 0;
	m_currentPlayer = 1;

	m_Clock = new sf::Clock();
	m_deltaTime = 0.f;
	m_fpsLimit = 1.0f / 120.0f;
	m_timeChange = 0.0f;

	m_music = new Music();

	m_previousClickState = false;
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

void	GameManager::Sleep() {
	m_window->w_window->clear();
	sf::sleep(sf::milliseconds(800));
}

void	GameManager::CloseWindow() {
	m_music->stop();
	delete m_music;
	m_window->w_window->close();
	exit(0);
}

void GameManager::LimitFps(float fps) {
	m_deltaTime = m_Clock->restart().asSeconds();
	m_timeChange += m_deltaTime;
	if (m_deltaTime < m_fpsLimit) {
		sleep(seconds(m_fpsLimit - m_deltaTime));
		m_deltaTime += m_fpsLimit - m_deltaTime;
	}
	fps = 1.0f / m_deltaTime;
}

void GameManager::DrawTerrain() {
	sf::RectangleShape collumn1(sf::Vector2f(600.0f, 5.f));
	collumn1.setPosition(202.5f, 0.0f);
	collumn1.rotate(90.0f);
	m_window->w_window->draw(collumn1);

	sf::RectangleShape collumn2(sf::Vector2f(600.0f, 5.f));
	collumn2.setPosition(402.5f, 0.0f);
	collumn2.rotate(90.0f);
	m_window->w_window->draw(collumn2);

	sf::RectangleShape row1(sf::Vector2f(600.0f, 5.f));
	row1.setPosition(0.0f, 202.5f);
	m_window->w_window->draw(row1);

	sf::RectangleShape row2(sf::Vector2f(600.0f, 5.f));
	row2.setPosition(0.0f, 402.5f);
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
	if (m_sprites.empty())
		GenerateSprites();
	GenerateMap();

	//GenerateHud();
}

/*
---------------------------------------------------------------------------------
|				Here are all the music related methods							|
---------------------------------------------------------------------------------
*/

void	GameManager::PlayMusic(const char *path) {
	m_music->stop();
	if (!m_music->openFromFile(path)) {
		std::cout << "Error loading "  << path << std::endl;
		exit(1);
	}
	m_music->setVolume(10.0f);
	m_music->play();
	m_music->setLoop(true);
}

/*
---------------------------------------------------------------------------------
|				Here are all the menu related methods							|
---------------------------------------------------------------------------------
*/

void GameManager::ChooseMenu() {
	sf::Vector2i	position = sf::Mouse::getPosition(*m_window->w_window);
	sf::Vector2u	windowSize = m_window->w_window->getSize();

	if (position.y <= windowSize.y / 2)
		m_menu = false;
	else if (position.y > windowSize.y / 2) {
		m_menu = false;
		m_running = false;
	}
}

void GameManager::Menu() {
	Event		event;
	sf::Texture	menuBackgroundTexture;
	sf::Sprite	menuBackgroundSprite;

	if (!menuBackgroundTexture.loadFromFile("rsrc/img/menu/background.png")) {
		std::cout << "Error loading menu background image" << std::endl;
		exit(1);
	}
	menuBackgroundSprite.setTexture(menuBackgroundTexture);
	SetIcon();
	PlayMusic("rsrc/music/menu.ogg");

	m_timeChange = 0.0f;
	while (m_menu) {

		while (m_window->w_window->pollEvent(event))
		{
			if (m_timeChange > INPUT_BLOCK_TIME) {
				if (event.type == Event::Closed)
					CloseWindow();

				if (Mouse::isButtonPressed(Mouse::Button::Left) && m_window->w_window->hasFocus())
					ChooseMenu();
			}
		}
		m_window->w_window->draw(menuBackgroundSprite);
		m_window->w_window->display();
		LimitFps(60.0f);
	}
	RefreshWindow();
	m_timeChange = 0.0f;
}

/*
---------------------------------------------------------------------------------
|					Here are all the end screens methods						|
---------------------------------------------------------------------------------
*/

void GameManager::ChooseEnd() {
	sf::Vector2i	position = sf::Mouse::getPosition(*m_window->w_window);
	sf::Vector2u	windowSize = m_window->w_window->getSize();

	if (position.y <= windowSize.y / 2){
		m_menu = true;
		m_endScreen = false;
	}
	else if (position.y > windowSize.y / 2) {
		m_endScreen = false;
		m_menu = false;
		m_running = false;
	}
}

void GameManager::Player1WinScreen() {
	Event		event;
	sf::Texture	player1BackgroundTexture;
	sf::Sprite	player1BackgroundSprite;
	
	if (!player1BackgroundTexture.loadFromFile("rsrc/img/end/player1background.png")) {
		std::cout << "Error loading player 1 win screen background image" << std::endl;
		exit(1);
	}
	player1BackgroundSprite.setTexture(player1BackgroundTexture);
	PlayMusic("rsrc/music/endscreens/player1win.ogg");

	m_endScreen = true;
	m_timeChange = 0.0f;
	while (m_endScreen) {

		while (m_window->w_window->pollEvent(event))
		{
			if (m_timeChange > INPUT_BLOCK_TIME)
			{
				if (event.type == Event::Closed)
					CloseWindow();

				if (Mouse::isButtonPressed(Mouse::Button::Left) && m_window->w_window->hasFocus())
					ChooseEnd();
			}
		}
		m_window->w_window->draw(player1BackgroundSprite);
		m_window->w_window->display();
		LimitFps(60.0f);
	}
}

void GameManager::Player2WinScreen() {
	Event		event;
	sf::Texture	player2BackgroundTexture;
	sf::Sprite	player2BackgroundSprite;

	if (!player2BackgroundTexture.loadFromFile("rsrc/img/end/player2background.png")) {
		std::cout << "Error loading player 2 win screen background image" << std::endl;
		exit(1);
	}
	player2BackgroundSprite.setTexture(player2BackgroundTexture);
	PlayMusic("rsrc/music/endscreens/player2win.ogg");

	m_endScreen = true;
	m_timeChange = 0.0f;
	while (m_endScreen) {

		while (m_window->w_window->pollEvent(event))
		{
			if (event.type == Event::Closed)
				CloseWindow();

			if (Mouse::isButtonPressed(Mouse::Button::Left) && m_window->w_window->hasFocus())
				ChooseEnd();
		}
		m_window->w_window->draw(player2BackgroundSprite);
		m_window->w_window->display();
		LimitFps(60.0f);
	}
}

void GameManager::TieScreen() {
	Event		event;
	sf::Texture	tieBackgroundTexture;
	sf::Sprite	tieBackgroundSprite;

	if (!tieBackgroundTexture.loadFromFile("rsrc/img/end/tiebackground.png")) {
		std::cout << "Error loading tie screen background image" << std::endl;
		exit(1);
	}
	tieBackgroundSprite.setTexture(tieBackgroundTexture);
	PlayMusic("rsrc/music/endscreens/tie.ogg");

	m_endScreen = true;
	m_timeChange = 0.0f;
	while (m_endScreen) {

		while (m_window->w_window->pollEvent(event))
		{
			if (event.type == Event::Closed)
				CloseWindow();

			if (Mouse::isButtonPressed(Mouse::Button::Left) && m_window->w_window->hasFocus())
				ChooseEnd();
		}
		m_window->w_window->draw(tieBackgroundSprite);
		m_window->w_window->display();
		LimitFps(60.0f);
	}
}

/*
---------------------------------------------------------------------------------
|						Here are all the main methods							|
---------------------------------------------------------------------------------
*/

Json::Value GameManager::Place() {
	char			c;
	char			test;
	char			*toReplace = nullptr;
	sf::Vector2i	position = sf::Mouse::getPosition(*m_window->w_window);
	sf::Vector2u	windowSize = m_window->w_window->getSize();
	Json::Value		json;

	int i = -1, j = -1;
	if (m_currentPlayer == 1)
		c = 'x';
	else
		c = '.';
	if (position.x <= windowSize.x / 3)
		j = 0;
	else if (position.x >= windowSize.x / 3 and position.x <= windowSize.x / 3 * 2)
		j = 1;
	else if (position.x >= windowSize.x / 3 * 2)
		j = 2;

	if (position.y <= windowSize.y / 3)
		i = 0;
	else if (position.y >= windowSize.y / 3 and position.y <= windowSize.y / 3 * 2)
		i = 1;
	else if (position.y >= windowSize.y / 3 * 2)
		i = 2;

	if (i != -1 && j != -1 && m_map[i][j] == '0') {
		test = m_map[i][j];
		test = c;

		json["grill_row_0"] = m_map[0];
		json["grill_row_1"] = m_map[1];
		json["grill_row_2"] = m_map[2];

		toReplace = &m_map[i][j];
		*toReplace = c;

		if (m_currentPlayer == 1)
			m_currentPlayer = 2;
		else
			m_currentPlayer = 1;

		return json;
	}
}

void GameManager::EndCheck() {
	// Check rows
	for (int i = 0; i < 3; i++) {
		if (m_map[i][0] == 'x' && m_map[i][1] == 'x' && m_map[i][2] == 'x') {
			Player1WinScreen();
			return;
		}
		if (m_map[i][0] == '.' && m_map[i][1] == '.' && m_map[i][2] == '.') {
			Player2WinScreen();
			return;
		}
	}

	// Check columns
	for (int j = 0; j < 3; j++) {
		if (m_map[0][j] == 'x' && m_map[1][j] == 'x' && m_map[2][j] == 'x') {
			Player1WinScreen();
			return;
		}
		if (m_map[0][j] == '.' && m_map[1][j] == '.' && m_map[2][j] == '.') {
			Player2WinScreen();
			return;
		}
	}

	// Check diagonals
	if ((m_map[0][0] == 'x' && m_map[1][1] == 'x' && m_map[2][2] == 'x') ||
		(m_map[0][2] == 'x' && m_map[1][1] == 'x' && m_map[2][0] == 'x')) {
		Player1WinScreen();
		return;
	}
	if ((m_map[0][0] == '.' && m_map[1][1] == '.' && m_map[2][2] == '.') ||
		(m_map[0][2] == '.' && m_map[1][1] == '.' && m_map[2][0] == '.')) {
		Player2WinScreen();
		return;
	}

	// Check tie
	bool isTie = true;
	for (int i = 0; i < 3; i++) {
		for (int j = 0; j < 3; j++) {
			if (m_map[i][j] == '0') {
				isTie = false;
				break;
			}
		}
	}

	if (isTie) {
		TieScreen();
	}
}

void GameManager::HandleEvents() {
	Event	event;
	bool	currentClickState;

	while (m_window->w_window->pollEvent(event))
	{ 
		if (m_timeChange > INPUT_BLOCK_TIME)
		{
			currentClickState = Mouse::isButtonPressed(Mouse::Button::Left);
			if (event.type == Event::Closed)
				CloseWindow();

			if (currentClickState && !m_previousClickState && m_window->w_window->hasFocus())
				if (m_currentPlayer == 1)
				{
					Place();
				}

			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Numpad1)) {
				if (m_currentPlayer == 2)
				{
					m_currentPlayer = 1;
					Json::Value jsonData;
					jsonData["grill_row_0"] = "000\0";
					jsonData["grill_row_1"] = "0.0\0";
					jsonData["grill_row_2"] = "000\0";

					convertJsonToMap(jsonData);
				}
				

			}
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Numpad2)) {
				if (m_currentPlayer == 2)
				{
					m_currentPlayer = 1;
					m_map[2][1] = '.';
				}
			}
			m_previousClickState = currentClickState;
		}
	}
}

void GameManager::Start() {
	float	fps = 0;

	Generate();
	Menu();
	PlayMusic("rsrc/music/theme.ogg");
	while (m_running)
	{
		RefreshWindow();
		HandleEvents();
		EndCheck();
		LimitFps(fps);
		if (m_menu) {
			Generate();
			Menu();
			PlayMusic("rsrc/music/theme.ogg");
		}
	}
}


/*
---------------------------------------------------------------------------------
|						Here is the Multiplayers methods						|
---------------------------------------------------------------------------------
*/

char* GameManager::convertJsonToString(const Json::Value& json, std::string key) {
	Json::StreamWriterBuilder builder;
	std::ostringstream os;
	std::unique_ptr<Json::StreamWriter> writer(builder.newStreamWriter());
	writer->write(json[key], &os);
	std::string jsonString = os.str();

	// Allouer de la mémoire pour le tableau de caractères (char*)
	char* charString = new char[jsonString.size() + 1];

	// Copier le contenu de la chaîne dans le tableau de caractères
	strcpy_s(charString, jsonString.size() + 1, jsonString.substr(1, jsonString.length() - 2).c_str());

	return charString;
}

void GameManager::convertJsonToMap(Json::Value& json) {
	char* charRow0 = convertJsonToString(json, "grill_row_0");
	char* charRow1 = convertJsonToString(json, "grill_row_1");
	char* charRow2 = convertJsonToString(json, "grill_row_2");
	std::cout << charRow0;
	std::cout << charRow1;
	std::cout << charRow2;
	for (int i = 0; i < 4; i++)
	{
		m_map[0][i] = charRow0[i];
		m_map[1][i] = charRow1[i];
		m_map[2][i] = charRow2[i];
	}
}

/*
---------------------------------------------------------------------------------
|						Here is the constructor methods							|
---------------------------------------------------------------------------------
*/

GameManager::~GameManager() {
	delete m_window;
	delete m_icon;
	m_music->stop();
	delete m_music;
	m_sprites.clear();
}
