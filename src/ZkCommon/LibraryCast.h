#pragma once

//W tym pliku zdefiniowana jest funkcja lib_cast służąca
//do konwertowania typów pomiędzy bibliotekami.
//Definiuje tylko te implementacje, które wykorzystują
//typy już zdefiniowane. Innymi słowy, jeśli chcesz
//korzystać z cast-ów z QColor na sf::Color, musisz
//przedtem za-include-ować nagłówki Qt oraz SFML.

namespace Zk {
namespace Common {

template<typename To, typename From>
To lib_cast(const From & f)
{
	static_assert(true, "Unsupported conversion");
}

#if defined(QCOLOR_H) && defined(SFML_COLOR_HPP)

template<>
sf::Color lib_cast<sf::Color, QColor>(const QColor & color)
{
	return sf::Color(color.red(), color.green(), color.blue(), color.alpha());
}

template<>
QColor lib_cast<QColor, sf::Color>(const sf::Color & color)
{
	return QColor(color.r, color.g, color.b, color.a);
}

#endif

}}
