#pragma once

#include <SFML/Graphics/RenderWindow.hpp>

class GameObject;

using namespace sf;

class GameWindow
{
private:

	// Main Attributes

	const char*			w_name;
	float				w_width;
	float				w_height;

public:

	RenderWindow*		w_window;

	GameWindow();
	~GameWindow();

	// Main Methods

	void				DrawObject(GameObject* gameObject);
	void				RefreshScreen();

	// Get Methods

	float				GetWidth();
	float				GetHeight();
};
