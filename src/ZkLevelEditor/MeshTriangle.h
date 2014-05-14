#pragma once

#include <QtWidgets>
#include <array>

namespace Zk {
namespace LevelEditor {

class TriangleNode;
class LevelView;

class MeshTriangle : public QObject, public QGraphicsPathItem
{
	Q_OBJECT;
	
public:
	MeshTriangle(
		LevelView * lv,
		std::array<TriangleNode*, 3> verts,
		QGraphicsItem * parent = nullptr
	);
	virtual ~MeshTriangle();
	
public slots:
	void updatePosition(TriangleNode * tn, const QPointF & pos);
	
private:
	LevelView * parentView;
	std::array<TriangleNode*, 3> verts;
};

}}
