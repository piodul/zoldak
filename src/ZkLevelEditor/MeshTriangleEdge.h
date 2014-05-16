#pragma once

#include <QtWidgets>
#include <array>

namespace Zk {
namespace LevelEditor {

class LevelView;
class MeshTriangleNode;

class MeshTriangleEdge : public QObject, public QGraphicsLineItem
{
	Q_OBJECT;
	
public:
	MeshTriangleEdge(
		LevelView * lv,
		std::array<MeshTriangleNode*, 2> ends,
		QGraphicsItem * parent = nullptr
	);
	virtual ~MeshTriangleEdge();
	
	std::array<MeshTriangleNode*, 2> getEnds() const;
	void deactivateExtruding();
	
signals:
	void clicked(MeshTriangleEdge * mte, const QPointF & pos);
	
public slots:
	void updatePosition(MeshTriangleNode * mtn, const QPointF & pos);
	
protected:
	void mousePressEvent(QGraphicsSceneMouseEvent * event);
	
private:
	std::array<MeshTriangleNode*, 2> ends;
	bool canExtrude;
};

}}
