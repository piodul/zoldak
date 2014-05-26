#pragma once

#include <QtWidgets>
#include <array>

namespace Zk {
namespace LevelEditor {

class MeshTriangleNode;
class MeshTriangleEdge;
class MeshLayer;

class MeshTriangle : public QGraphicsObject
{
	Q_OBJECT;
	
public:
	MeshTriangle(
		MeshLayer * ml,
		std::array<MeshTriangleNode*, 3> verts,
		std::array<MeshTriangleEdge*, 3> edges,
		QGraphicsItem * parent = nullptr
	);
	virtual ~MeshTriangle();
	
	virtual QRectF boundingRect() const override;
	virtual void paint(
		QPainter * painter,
		const QStyleOptionGraphicsItem * option,
		QWidget * widget = nullptr
	) override;
	
	virtual QPainterPath shape() const override;
	
	const std::array<MeshTriangleNode*, 3> & getLinkedNodes() const;
	const std::array<MeshTriangleEdge*, 3> & getLinkedEdges() const;
	
signals:
	void destroyed(MeshTriangle * me);
	
public slots:
	void updatePosition(MeshTriangleNode * mtn, const QPointF & pos);

protected:
	virtual void contextMenuEvent(QGraphicsSceneContextMenuEvent * event) override;
	virtual void mousePressEvent(QGraphicsSceneMouseEvent * event) override;

private:
	MeshLayer * parentLayer;
	std::array<MeshTriangleNode*, 3> verts;
	std::array<MeshTriangleEdge*, 3> edges;
	std::array<QColor, 3> vColors;
};

}}
