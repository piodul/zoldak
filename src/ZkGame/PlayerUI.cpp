#include <SFML/Graphics.hpp>

#include <QtCore>

#include <memory>

#include "../ZkCommon/Constants.hpp"

#include "PlayerUI.hpp"
#include "Entities/PlayerEntity.hpp"
#include "Game.hpp"
#include "GameSystem.hpp"
#include "TextureCache.hpp"
#include "Camera.hpp"

#include "Weapons/Weapon.hpp"
#include "Weapons/WeaponDef.hpp"

using namespace Zk::Common;
using namespace Zk::Game;

PlayerUI::PlayerUI(Player & player)
	: player(player)
{
	TextureCache & tc = GameSystem::getInstance()->getTextureCache();

	font.loadFromFile(
		GameSystem::resourcePath("SourceSansPro/SourceSansPro-Regular.otf")
	);
	healthTexture = tc.getTexture(GameSystem::resourcePath("life.png"));
	grenadeTexture = tc.getTexture(GameSystem::resourcePath("grenade.png"));
	ammoTexture = tc.getTexture(GameSystem::resourcePath("ammo.png"));
}

PlayerUI::~PlayerUI()
{

}

void PlayerUI::paint(sf::RenderTarget * rt)
{
	std::weak_ptr<PlayerEntity> pe = player.getPlayerEntity();

	Camera * cam = Game::getInstance()->getCamera();
	sf::View view = cam->getViews()[player.getID()];

	//Modyfikujemy widok, gdyż potrzebne jest mierzenie
	//długości/pozycji w pikselach
	sf::Vector2f viewSize =
		view.getSize() * (float)Constants::PIXELS_PER_METER;
	view.reset(sf::FloatRect(0.f, 0.f, viewSize.x, viewSize.y));

	sf::FloatRect area;
	area.left = 0.f;
	area.top = 0.f;
	area.width = (float)viewSize.x;
	area.height = (float)viewSize.y;

	rt->setView(view);

	double health;
	double healthFraction;
	double ammoFraction;
	int numGrenades;

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
	else
	{
		health = 0.0;
		ammoFraction = 0.0;
		numGrenades = 0;
	}

	healthFraction = health / 100.0;

	sf::Vector2u htSize = healthTexture->getSize();
	sf::Vector2u gtSize = grenadeTexture->getSize();
	sf::Vector2u atSize = ammoTexture->getSize();

	//Narysuj amunicję
	sf::Sprite sprite;
	sprite.setTexture(*ammoTexture, true);
	sprite.setPosition(sf::Vector2f(
		area.left,
		area.top + area.height - atSize.y
	));
	rt->draw(sprite);

	//Pasek amunicji
	sf::RectangleShape rs;
	rs.setPosition(sf::Vector2f(
		area.left + htSize.x + 2.f,
		area.top + area.height - atSize.y + 2.f
	));
	rs.setSize(sf::Vector2f((256.f - 4.f) * ammoFraction, atSize.y - 4.f));
	rs.setOutlineColor(sf::Color::Transparent);
	rs.setFillColor(sf::Color::Yellow);
	rt->draw(rs);

	rs.setSize(sf::Vector2f(256.f - 4.f, atSize.y - 4.f));
	rs.setOutlineColor(sf::Color::Black);
	rs.setFillColor(sf::Color::Transparent);
	rs.setOutlineThickness(2.f);
	rt->draw(rs);

	//Narysuj życie
	sprite.setTexture(*healthTexture, true);
	sprite.setPosition(sf::Vector2f(
		area.left,
		area.top + area.height - atSize.y - htSize.y
	));
	rt->draw(sprite);

	//Pasek życia
	rs.setPosition(sf::Vector2f(
		area.left + htSize.x + 2.f,
		area.top + area.height - htSize.y - atSize.y + 2.f
	));
	rs.setSize(sf::Vector2f((256.f - 4.f) * healthFraction, htSize.y - 4.f));
	rs.setOutlineColor(sf::Color::Transparent);
	rs.setFillColor(sf::Color::Green);
	rt->draw(rs);

	rs.setSize(sf::Vector2f(256.f - 4.f, htSize.y - 4.f));
	rs.setOutlineColor(sf::Color::Black);
	rs.setFillColor(sf::Color::Transparent);
	rs.setOutlineThickness(2.f);
	rt->draw(rs);

	//Narysuj granaty
	for (int i = 0; i < numGrenades; i++)
	{
		sprite.setTexture(*grenadeTexture, true);
		sprite.setPosition(sf::Vector2f(
			area.left + (float)i * gtSize.x,
			area.top + area.height - atSize.y - htSize.y - gtSize.y
		));
		rt->draw(sprite);
	}

	//Narysuj punktację
	QString pointsString =
		QString("%1 - %2").arg(player.getKillCount()).arg(player.getDeathCount());

	sf::Text text;
	text.setFont(font);
	text.setString(pointsString.toStdString());
	text.setCharacterSize(48);
	sf::FloatRect rect = text.getLocalBounds();
	text.setColor(sf::Color::Blue);
	text.setPosition(
		area.left + area.width - rect.width,
		area.top + area.height - 48
	);
	rt->draw(text);

	if (p == nullptr)
	{
		//Gracz nie żyje, więc wypisujemy ile zostało do respawnu
		QString respawnString =
			QString("Respawn in %1").arg(player.getSecondsToRespawn(), 0, 'f', 1);

		text.setCharacterSize(48);
		text.setString(respawnString.toStdString());
		rect = text.getLocalBounds();
		text.setPosition(
			area.left + (area.width - rect.width) / 2.f,
			area.top + (area.height - rect.height) / 2.f
		);

		rt->draw(text);
	}
}
