#include <QString>
#include <SFML/Graphics.hpp>

#include <map>

#include "TextureCache.hpp"

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

sf::Texture * TextureCache::getTexture(const std::string & str)
{
	return getTexture(str.c_str());
}

void TextureCache::clear()
{
	for (auto it : cache)
		delete it.second;

	cache.clear();
}
