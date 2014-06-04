#include <SFML/Graphics.hpp>

#include "PlayerUI.h"

using namespace Zk::Game;

PlayerUI::PlayerUI()
{
	font.loadFromFile("../data/SourceSansPro/SourceSansPro-Regular.otf");
}

PlayerUI::~PlayerUI()
{
	
}

void PlayerUI::paint(sf::RenderTarget * rt, sf::FloatRect area)
{
	sf::Text text;
	text.setFont(font);
	text.setString("Hello, world!");
	text.setCharacterSize(24);
	text.setColor(sf::Color::Blue);
	rt->draw(text);
}
