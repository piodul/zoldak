#pragma once
#include <SFML/Graphics.hpp>

#include "TextureCache.hpp"
#include "Player.hpp"


namespace Zk {
namespace Game {

/**
 * @brief Klasa reprezentuje obiekt layoutu PlayerUI zainicjalizowanego wszystmimi danymi potrzebnymi do renderowania.
 */
class PlayerUILayout {
public:
	PlayerUILayout(
		sf::RenderTarget * rt, Player & player, const sf::Font * font, sf::Texture * healthTexture,
		sf::Texture * grenadeTexture, sf::Texture * ammoTexture);

	void paint();

private:
	void drawAmmoBar(const double ammoFraction);
	void drawHealthBar(const double healthFraction);
	void drawGrenades(const int numGrenades);
	void drawPoints();
	void drawRespawnCounter();
	void drawBar(const sf::FloatRect & barRect, const double fraction, const sf::Color & fillColor,
		     const sf::Color & backgroundColor = sf::Color::Transparent,
		     const sf::Color & borderColor = sf::Color::Black);
	void drawTexture(const sf::Vector2f & position, const sf::Texture * texture);
	void drawText(const std::string & str, const bool centered = false, const bool toRight = false,
		      const sf::Color & color = sf::Color::Blue);

	sf::RenderTarget * rt;
	Player player;
	const sf::Font * font;
	const sf::Texture * healthTexture;
	const sf::Texture * grenadeTexture;
	const sf::Texture * ammoTexture;

	sf::FloatRect area;
	const sf::Vector2u atSize;
	const sf::Vector2u htSize;
	const sf::Vector2u gtSize;
};

}}