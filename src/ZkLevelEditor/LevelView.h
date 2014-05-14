#pragma once

#include <QtWidgets>
#include <array>

namespace Zk {
namespace LevelEditor {

class TriangleNode;
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
	void triangleNodeClicked(TriangleNode * tn);
	void triangleEdgeClicked(MeshTriangleEdge * mte, const QPointF & pos);
	
private:
	TriangleNode * createNode(const QPointF & pos);
	MeshTriangle * createTriangle(std::array<TriangleNode*, 3> verts);
	MeshTriangleEdge * createTriangleEdge(std::array<TriangleNode*, 2> ends);
};

}}
