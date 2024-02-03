#include <SFML/Graphics.hpp>
#include <SFML/System/Sleep.hpp>
#include <SFML/Audio.hpp>

#include "GameManager.h"

int main()
{
    GameManager        game;

    //game.Menu();
    //sf::sleep(sf::milliseconds(200));
    game.Start();
    return 0;
}