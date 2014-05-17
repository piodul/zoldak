#pragma once

#include <QtWidgets>
#include <array>

namespace Zk {
namespace LevelEditor {

class MeshTriangleNode;
class MeshLayer;

class MeshTriangle : public QGraphicsObject
{
	Q_OBJECT;
	
public:
	MeshTriangle(
		MeshLayer * ml,
		std::array<MeshTriangleNode*, 3> verts,
		QGraphicsItem * parent = nullptr
	);
	virtual ~MeshTriangle();
	
	virtual QRectF boundingRect() const override;
	virtual void paint(
		QPainter * painter,
		const QStyleOptionGraphicsItem * option,
		QWidget * widget = nullptr
	) override;
	
public slots:
	void updatePosition(MeshTriangleNode * mtn, const QPointF & pos);
	void updateColors();
	
private:
	MeshLayer * parentLayer;
	std::array<MeshTriangleNode*, 3> verts;
};

}}
