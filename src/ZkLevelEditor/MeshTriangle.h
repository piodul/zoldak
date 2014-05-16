#pragma once

#include <QtWidgets>
#include <array>

namespace Zk {
namespace LevelEditor {

class MeshTriangleNode;
class MeshLayer;

class MeshTriangle : public QObject, public QGraphicsPathItem
{
	Q_OBJECT;
	
public:
	MeshTriangle(
		MeshLayer * ml,
		std::array<MeshTriangleNode*, 3> verts,
		QGraphicsItem * parent = nullptr
	);
	virtual ~MeshTriangle();
	
public slots:
	void updatePosition(MeshTriangleNode * mtn, const QPointF & pos);
	
private:
	MeshLayer * parentLayer;
	std::array<MeshTriangleNode*, 3> verts;
};

}}
