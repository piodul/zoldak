#pragma once

#include <QtWidgets>
#include <array>

namespace Zk {
namespace LevelEditor {

//TODO: Doxygen

class MeshTriangle;
class MeshTriangleNode;
class MeshTriangleEdge;

class MeshLayer : public QObject
{
	Q_OBJECT;
	
public:
	MeshLayer(QGraphicsScene * scane, QObject * parent = nullptr);
	virtual ~MeshLayer();
	
	//Ustawia czy daną warstwę można edytować
	//i odpowiednio zmienia jej wygląd
	void setActivated(bool activated);
	
	//Zwraca czy jest aktywna
	inline bool isActivated(bool activated)
	{
		return isActive;
	}
	
private slots:
	void triangleNodeClicked(MeshTriangleNode * mtn);
	void triangleEdgeClicked(MeshTriangleEdge * mte, const QPointF & pos);
	
	void triangleDestroyed(MeshTriangle * mt);
	void nodeUnlinked(MeshTriangleNode * mtn);
	void edgeUnlinked(MeshTriangleEdge * mte);
	
private:
	MeshTriangleNode * createNode(const QPointF & pos);
	MeshTriangle * createTriangle(
		std::array<MeshTriangleNode*, 3> verts,
		std::array<MeshTriangleEdge*, 3> edges
	);
	MeshTriangleEdge * createEdge(std::array<MeshTriangleNode*, 2> ends);
	
	QList<MeshTriangle*> triangles;
	QList<MeshTriangleNode*> nodes;
	QList<MeshTriangleEdge*> edges;
	
	QGraphicsScene * scene;
	bool isActive;
	
};

}}
