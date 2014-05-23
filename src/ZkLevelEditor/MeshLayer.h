#pragma once

#include <QtWidgets>
#include <array>

#include "../ZkCommon/Level.h"
#include "EditState.h"

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
	inline bool isActivated()
	{
		return isActive;
	}
	
	void clear();
	bool fromCommonLevelLayer(const Common::LevelLayer & ll);
	void toCommonLevelLayer(Common::LevelLayer & ll) const;
	
signals:
	void statusTextChanged(QString txt);
	
private slots:
	void triangleNodeClicked(MeshTriangleNode * mtn, const QGraphicsSceneMouseEvent * event);
	void triangleEdgeClicked(MeshTriangleEdge * mte, const QGraphicsSceneMouseEvent * event);
	
	void triangleDestroyed(MeshTriangle * mt);
	void nodeUnlinked(MeshTriangleNode * mtn);
	void edgeUnlinked(MeshTriangleEdge * mte);
	
	void backgroundClicked();
	
	void contextMenu(const QPoint & pos, const QPointF & scenePos);
	
private:
	MeshTriangleNode * createNode(const QPointF & pos);
	MeshTriangle * createTriangle(
		std::array<MeshTriangleNode*, 3> verts,
		std::array<MeshTriangleEdge*, 3> edges
	);
	MeshTriangleEdge * createEdge(std::array<MeshTriangleNode*, 2> ends);
	
	//Tworzy trójkąt na podstawie trzech istniejących wierzchołków
	MeshTriangle * formTriangle(std::array<MeshTriangleNode*, 3> verts);
	
	//Tworzy osobny trójkąt
	MeshTriangle * createFullTriangle(const QPointF & pos);
	
	QList<MeshTriangle*> triangles;
	QList<MeshTriangleNode*> nodes;
	QList<MeshTriangleEdge*> edges;
	
	QGraphicsScene * scene;
	bool isActive;
	
	EditState editState;
	std::array<MeshTriangleNode*, 3> nodesToConnect;
};

}}
