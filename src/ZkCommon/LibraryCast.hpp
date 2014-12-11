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
	static_assert(sizeof(To) == 0, "Unsupported conversion");
}

#if defined(QCOLOR_H) && defined(SFML_COLOR_HPP)

template<> inline
sf::Color lib_cast<sf::Color, QColor>(const QColor & o)
{ return sf::Color(o.red(), o.green(), o.blue(), o.alpha()); }

template<> inline
QColor lib_cast<QColor, sf::Color>(const sf::Color & o)
{ return QColor(o.r, o.g, o.b, o.a); }

#endif



#if defined(QPOINT_H) && defined(SFML_VECTOR2_HPP)

template<> inline
sf::Vector2f lib_cast<sf::Vector2f, QPointF>(const QPointF & o)
{ return sf::Vector2f(o.x(), o.y()); }

template<> inline
QPointF lib_cast<QPointF, sf::Vector2f>(const sf::Vector2f & o)
{ return QPointF(o.x, o.y); }

#endif



#if defined(QPOINT_H) && defined(B2_MATH_H)

template<> inline
b2Vec2 lib_cast<b2Vec2, QPointF>(const QPointF & o)
{ return b2Vec2(o.x(), o.y()); }

template<> inline 
QPointF lib_cast<QPointF, b2Vec2>(const b2Vec2 & o)
{ return QPointF(o.x, o.y); }

#endif



#if defined(B2_MATH_H) && defined(SFML_VECTOR2_HPP)

template<> inline
sf::Vector2f lib_cast<sf::Vector2f, b2Vec2>(const b2Vec2 & o)
{ return sf::Vector2f(o.x, o.y); }

template<> inline
b2Vec2 lib_cast<b2Vec2, sf::Vector2f>(const sf::Vector2f & o)
{ return b2Vec2(o.x, o.y); }

#endif



#if defined(QRECT_H) && defined(SFML_RECT_HPP)

template<> inline
sf::FloatRect lib_cast<sf::FloatRect, QRectF>(const QRectF & o)
{ return sf::FloatRect(o.x(), o.y(), o.width(), o.height()); }

template<> inline
QRectF lib_cast<QRectF, sf::FloatRect>(const sf::FloatRect & o)
{ return QRectF(o.left, o.top, o.width, o.height); }

#endif

}}
