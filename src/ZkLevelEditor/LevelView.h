#pragma once

#include <QtWidgets>
#include <array>

namespace Zk {
namespace LevelEditor {

class MeshTriangleNode;
class MeshTriangle;
class MeshTriangleEdge;

class LevelView : public QGraphicsView
{
	Q_OBJECT;
	
public:
	LevelView(QWidget * parent = nullptr);
	virtual ~LevelView();
	
private slots:
	void showContextMenu(const QPoint & pos);
	void triangleNodeClicked(MeshTriangleNode * mtn);
	void triangleEdgeClicked(MeshTriangleEdge * mte, const QPointF & pos);
	
private:
	MeshTriangleNode * createNode(const QPointF & pos);
	MeshTriangle * createTriangle(std::array<MeshTriangleNode*, 3> verts);
	MeshTriangleEdge * createTriangleEdge(std::array<MeshTriangleNode*, 2> ends);
};

}}
