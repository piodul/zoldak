#pragma once

#include <QString>

#include <SFML/Graphics.hpp>

#include <map>

namespace Zk {
namespace Game {

class TextureCache
{
public:
	TextureCache();
	~TextureCache();
	
	sf::Texture * getTexture(const char * src);
	void clear();
	
private:
	std::map<QString, sf::Texture*> cache;
};

}}
