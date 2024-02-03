#include "GameWindow.h"
#include "GameObject.h"
#include <SFML/Graphics.hpp>

using namespace sf;

/*
---------------------------------------------------------------------------------
|						 Here is the constructor								|
---------------------------------------------------------------------------------
*/

GameWindow::GameWindow() {
	w_width = 600.f;
	w_height = 600.f;
	w_name = "Tic Tac Toe";

	w_window = new sf::RenderWindow(sf::VideoMode((unsigned int)w_width, (unsigned int)w_height), w_name);
	sf::View view(sf::Vector2f(300, 300), sf::Vector2f(600, 600));
	w_window->setView(view);
}

/*
---------------------------------------------------------------------------------
|				Here are all the get methods									|
---------------------------------------------------------------------------------
*/

float GameWindow::GetWidth() {
	return (float)w_width;
}

float GameWindow::GetHeight() {
	return (float)w_height;
}

/*
---------------------------------------------------------------------------------
|				Here are all the main methods									|
---------------------------------------------------------------------------------
*/

void	GameWindow::DrawObject(GameObject* gameObject) {
	w_window->draw(gameObject->o_sprite);
}

void	GameWindow::RefreshScreen() {
	w_window->clear();
}

GameWindow::~GameWindow() {
	delete w_window;
}
