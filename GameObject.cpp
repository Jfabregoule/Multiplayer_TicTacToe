#include <SFML/Graphics.hpp>

#include "GameObject.h"

#include "math.h"

using namespace sf;
using namespace std;

/*
---------------------------------------------------------------------------------
|						 Here is the constructor								|
---------------------------------------------------------------------------------
*/

GameObject::GameObject(sf::Sprite* sprite) {
	o_height = 0;
	o_width = 0;
	o_posX = 0.f;
	o_posY = 0.f;

	o_sprite = *new sf::Sprite;
	if (sprite != NULL)
		o_sprite = *sprite;
}

/*
---------------------------------------------------------------------------------
|				Here are the object parameters related methods					|
---------------------------------------------------------------------------------
*/

void GameObject::SetPos(float posX, float posY) {
	o_posX = posX;
	o_posY = posY;
	o_sprite.setPosition(posX, posY);
}

void GameObject::SetColor(int r, int g, int b) {
	o_sprite.setColor(Color(r, g, b));
}

GameObject::~GameObject() {

}