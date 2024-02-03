#pragma once

class GameWindow;

class GameManager
{

private:

	// Main Attributes

	GameWindow					*m_window;
	sf::Image					*m_icon;
	char						m_map[3][4];

	bool						m_running;

	int							m_currentTurn;
	int							m_currentPlayer;

	sf::Clock					*m_Clock;
	float						m_deltaTime;
	float						m_fpsLimit;

	// Textures

	std::vector<sf::Sprite*>	m_sprites;
	
public:

	GameManager();

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

	void		Place();
	void		EndCheck();
	void		HandleEvents();
};

