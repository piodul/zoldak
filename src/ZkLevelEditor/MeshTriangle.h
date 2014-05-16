#pragma once

#include <QtWidgets>
#include <array>

namespace Zk {
namespace LevelEditor {

class MeshTriangleNode;
class LevelView;

class MeshTriangle : public QObject, public QGraphicsPathItem
{
	Q_OBJECT;
	
public:
	MeshTriangle(
		LevelView * lv,
		std::array<MeshTriangleNode*, 3> verts,
		QGraphicsItem * parent = nullptr
	);
	virtual ~MeshTriangle();
	
public slots:
	void updatePosition(MeshTriangleNode * mtn, const QPointF & pos);
	
private:
	LevelView * parentView;
	std::array<MeshTriangleNode*, 3> verts;
};

}}
