#pragma once

#include <QtWidgets>
#include <array>

namespace Zk {
namespace LevelEditor {

class LevelView;
class TriangleNode;

class MeshTriangleEdge : public QObject, public QGraphicsLineItem
{
	Q_OBJECT;
	
public:
	MeshTriangleEdge(
		LevelView * lv,
		std::array<TriangleNode*, 2> ends,
		QGraphicsItem * parent = nullptr
	);
	virtual ~MeshTriangleEdge();
	
	std::array<TriangleNode*, 2> getEnds() const;
	void deactivateExtruding();
	
signals:
	void clicked(MeshTriangleEdge * mte, const QPointF & pos);
	
public slots:
	void updatePosition(TriangleNode * tn, const QPointF & pos);
	
protected:
	void mousePressEvent(QGraphicsSceneMouseEvent * event);
	
private:
	std::array<TriangleNode*, 2> ends;
	bool canExtrude;
};

}}
