#include "PlayerUILayout.hpp"

#include "../ZkCommon/Constants.hpp"

#include "Entities/PlayerEntity.hpp"
#include "Game.hpp"
#include "GameSystem.hpp"
#include "TextureCache.hpp"
#include "Camera.hpp"

#include "Weapons/Weapon.hpp"
#include "Weapons/WeaponDef.hpp"

using namespace Zk::Common;
using namespace Zk::Game;

PlayerUILayout::PlayerUILayout(sf::RenderTarget * rt, Player & player, const sf::Font * font,
			       sf::Texture * healthTexture, sf::Texture * grenadeTexture,
			       sf::Texture * ammoTexture)
: rt{rt}, player{player}, font{font}, healthTexture{healthTexture}, grenadeTexture{grenadeTexture}
, ammoTexture{ammoTexture}, atSize{ammoTexture->getSize()}, htSize{healthTexture->getSize()}
, gtSize{grenadeTexture->getSize()}
{
	Camera * cam = Game::getInstance()->getCamera();
	sf::View view = cam->getViews()[player.getID()];

	//Modyfikujemy widok, gdyż potrzebne jest mierzenie
	//długości/pozycji w pikselach
	sf::Vector2f viewSize = view.getSize() * (float)Constants::PIXELS_PER_METER;
	view.reset(sf::FloatRect(0.f, 0.f, viewSize.x, viewSize.y));

	area.left = 0.f;
	area.top = 0.f;
	area.width = (float)viewSize.x;
	area.height = (float)viewSize.y;

	rt->setView(view);
}


void PlayerUILayout::paint()
{
	std::weak_ptr<PlayerEntity> pe = player.getPlayerEntity();

	double health = 0.0;
	double ammoFraction = 0.0;
	int numGrenades = 0;

	auto p = pe.lock();
	if (p != nullptr)
	{
		const Weapon & weapon = p->getWeapon();

		health = p->getHealth();

		if (weapon.getAmmoCount() > 0)
			ammoFraction =
			(double)weapon.getAmmoCount() /
			(double)weapon.getWeaponDef().clipSize;
		else
			ammoFraction = weapon.reloadProgress();

		numGrenades = p->getGrenadeCount();
	}


	drawAmmoBar(ammoFraction);
	drawHealthBar(health / 100.0);
	drawGrenades(numGrenades);
	drawPoints();

	if (p == nullptr)
	{
		//Gracz nie żyje, więc wypisujemy ile zostało do respawnu
		drawRespawnCounter();
	}
}

void PlayerUILayout::drawAmmoBar(const double ammoFraction)
{
	//Narysuj amunicję
	drawTexture(sf::Vector2f(
		area.left,
		area.top + area.height - atSize.y
	), ammoTexture);

	//Pasek amunicji
	sf::FloatRect barArea(
		area.left + htSize.x,
		area.top + area.height - atSize.y,
		256.f,
		atSize.y
	);
	drawBar(barArea, ammoFraction, sf::Color::Yellow);
}

void PlayerUILayout::drawHealthBar(const double healthFraction)
{
	//Narysuj życie
	drawTexture(sf::Vector2f(
		area.left,
		area.top + area.height - atSize.y - htSize.y
	), healthTexture);

	//Pasek życia
	sf::FloatRect barArea(
		area.left + htSize.x,
		area.top + area.height - htSize.y - atSize.y,
		256.f,
		htSize.y
	);
	drawBar(barArea, healthFraction, sf::Color::Green);
}

void PlayerUILayout::drawGrenades(const int numGrenades)
{
	//Narysuj granaty
	for (int i = 0; i < numGrenades; i++)
		drawTexture(sf::Vector2f(
			area.left + (float)i * gtSize.x,
			area.top + area.height - atSize.y - htSize.y - gtSize.y
		), grenadeTexture);
}

void PlayerUILayout::drawPoints()
{
	//Narysuj punktację
	QString pointsString =
	QString("%1 - %2").arg(player.getKillCount()).arg(player.getDeathCount());

	drawText(pointsString.toStdString(), false, true);
}

void PlayerUILayout::drawRespawnCounter()
{
	QString respawnString =
	QString("Respawn in %1").arg(player.getSecondsToRespawn(), 0, 'f', 1);

	drawText(respawnString.toStdString(), true);
}

void PlayerUILayout::drawBar(const sf::FloatRect & barRect, const double fraction,
			     const sf::Color & fillColor, const sf::Color & backgroundColor,
			     const sf::Color & borderColor)
{
	sf::RectangleShape rs;
	rs.setPosition(sf::Vector2f(barRect.left + 2.f, barRect.top + 2.f));

	// Narysuj prostokąt
	rs.setSize(sf::Vector2f(barRect.width - 4.f, barRect.height - 4.f));
	rs.setOutlineColor(borderColor);
	rs.setFillColor(backgroundColor);
	rs.setOutlineThickness(2.f);
	rt->draw(rs);

	// Narysuj wypełnienie
	rs.setSize(sf::Vector2f((barRect.width - 4.f) * fraction, barRect.height - 4.f));
	rs.setOutlineColor(sf::Color::Transparent);
	rs.setFillColor(fillColor);
	rt->draw(rs);
}

void PlayerUILayout::drawTexture(const sf::Vector2f & position, const sf::Texture * texture)
{
	sf::Sprite sprite;
	sprite.setTexture(*texture, true);
	sprite.setPosition(position);
	rt->draw(sprite);
}

void PlayerUILayout::drawText(const std::string & str, const bool centered, const bool toRight, const sf::Color & color)
{
	sf::Text text;
	text.setFont(*font);
	text.setCharacterSize(48);
	text.setColor(color);
	text.setString(str);
	sf::FloatRect rect = text.getLocalBounds();
	if (centered)
		text.setPosition(sf::Vector2f(
			area.left + (area.width - rect.width) / 2.f,
					      area.top + (area.height - rect.height) / 2.f
		));
	else if (toRight) {
		text.setPosition(sf::Vector2f(
			area.left + area.width - rect.width,
			area.top + area.height - 48
		));
	}

	rt->draw(text);
}

