#pragma once

#include <SFML/Graphics.hpp>

class GameWindow;

class GameObject {

public:
	// Main Attributes

	float			o_width;
	float			o_height;

	// Pos and Mov related

	float			o_posX;
	float			o_posY;

	sf::Sprite		o_sprite;

	GameObject(sf::Sprite* sprite);
	~GameObject();

	// Object parameters related

	void			SetColor(int r, int g, int b);
	void			SetPos(float posX, float posY);
};

