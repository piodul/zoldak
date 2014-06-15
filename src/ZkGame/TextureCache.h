#pragma once

#include <QString>

#include <SFML/Graphics.hpp>

#include <map>
#include <string>

namespace Zk {
namespace Game {

class TextureCache
{
public:
	TextureCache();
	~TextureCache();

	sf::Texture * getTexture(const char * src);
	sf::Texture * getTexture(const std::string & str);
	void clear();

private:
	std::map<QString, sf::Texture*> cache;
};

}}
