#pragma once

class GameWindow;

#include <SFML/Audio/Music.hpp>

class GameManager
{

private:

	// Main Attributes

	GameWindow					*m_window;
	sf::Image					*m_icon;
	char						m_map[3][4];

	bool						m_menu;
	bool						m_running;

	int							m_currentTurn;
	int							m_currentPlayer;

	sf::Clock					*m_Clock;
	float						m_deltaTime;
	float						m_fpsLimit;

	sf::Music*					m_music;

	bool						m_previousClickState;

	// Textures

	std::vector<sf::Sprite*>	m_sprites;
	
public:

	GameManager();
	~GameManager();

	// Called in main

	void		Start();

private:

	void		SetIcon();
	void		CloseWindow();
	void		LimitFps(float fps);
	void		DrawTerrain();
	void		DrawBoard();
	void		RefreshWindow();

	void		GenerateSprites();
	void		GenerateMap();
	void		Generate();

	// Music related
	void		PlayMusic(const char *path);

	void		Place();
	void		EndCheck();
	void		HandleEvents();
	void		ChooseMenu();
	void		Menu();
};

