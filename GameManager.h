#pragma once

class GameWindow;

#include <SFML/Audio/Music.hpp>

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
	void		Sleep();
	void		RefreshWindow();

	// Generation related

	void		GenerateSprites();
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

	void		Place();
	void		EndCheck();
	void		HandleEvents();
};

