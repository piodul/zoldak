#include <QString>
#include <SFML/Graphics.hpp>

#include <map>

#include "TextureCache.h"

using namespace Zk::Game;

TextureCache::TextureCache()
{
	
}

TextureCache::~TextureCache()
{
	clear();
}

sf::Texture * TextureCache::getTexture(const char * src)
{
	QString qstr = src;
	sf::Texture * texture = cache[qstr];
	
	if (texture == nullptr)
	{
		texture = new sf::Texture();
		texture->loadFromFile(src);
		texture->setSmooth(true);
		cache[qstr] = texture;
	}
	
	return texture;
}

void TextureCache::clear()
{
	for (auto it : cache)
		delete it.second;
	
	cache.clear();
}
