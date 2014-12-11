#pragma once

#include <QtWidgets>
#include <array>

#include "../ZkCommon/Level.hpp"
#include "EditState.hpp"

namespace Zk {
namespace LevelEditor {

//TODO: Doxygen

class MeshTriangle;
class MeshTriangleNode;
class MeshTriangleEdge;

class ColorPaletteWidget;

class MeshLayer : public QObject
{
	Q_OBJECT;

public:
	MeshLayer(
		QGraphicsScene * scene,
		ColorPaletteWidget * palette,
		int index,
		QObject * parent = nullptr
	);
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
	Common::LevelLayer toCommonLevelLayer() const;

	EditState getState() const;
	QColor getSelectedColor() const;
	int getIndex() const;

signals:
	void statusTextChanged(QString txt);

public slots:
	void setState(EditState es);

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
	ColorPaletteWidget * palette;
	bool isActive;

	EditState editState;
	std::array<MeshTriangleNode*, 3> nodesToConnect;

	int index;
};

}}
