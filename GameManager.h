#pragma once

class GameWindow;

#include <SFML/Audio/Music.hpp>
#include <json/json.h>

class GameManager
{

private:

	// Window attributes

	GameWindow					*m_window;
	sf::Image					*m_icon;

	// Game attributes

	bool						m_running;

	char						m_map[3][4];
	int							m_currentTurn;
	int							m_currentPlayer;
	bool						m_previousClickState;

	bool						m_menu;
	bool						m_endScreen;
	bool						m_choiceScreen;
	bool						m_username;

	int							m_playerNumberSelf;
	int							m_playerNumberEnemy;

	bool						m_playerSpectator;

	std::vector<sf::Text>		m_textList;

	std::string					username;

	sf::Font					font;

	sf::Music* m_music;

	// Time attributes

	sf::Clock					*m_Clock;
	float						m_deltaTime;
	float						m_fpsLimit;
	float						m_timeChange;

	// Textures attributes

	std::vector<sf::Sprite*>	m_sprites;
	
public:

	// Constructor/Destructor

	GameManager();
	~GameManager();

	// Called in main

	void		Start();

private:

	// Window related

	void		SetIcon();
	void		CloseWindow();
	void		LimitFps(float fps);
	void		DrawTerrain();
	void		DrawBoard();
	void		DrawText();
	void		Sleep();
	void		RefreshWindow();

	// Generation related

	void		GenerateSprites();
	void		GenerateText();
	void		GenerateMap();
	void		Generate();

	// Music related

	void		PlayMusic(const char *path);

	// Menu related

	void		ChooseMenu();
	void		Menu();

	// End screen related

	void		ChooseEnd();
	void		Player1WinScreen();
	void		Player2WinScreen();
	void		TieScreen();

	// Main methods

	Json::Value	Place();
	void		EndCheck();
	void		HandleEvents();

	// Multiplayer Methods
	char*		convertJsonToString(const Json::Value& json, std::string key);
	Json::Value convertStringToJson(const std::string& jsonString);
	void		convertJsonToMap(Json::Value& json);
	void		ChoicePlayerScreen();
	void		enterNameScreen();
	void		ChoosePlayer();
	bool		PlayerVerification(int playerNumber);
};