#pragma once

#include <QtWidgets>
#include <array>

namespace Zk {
namespace LevelEditor {

class MeshTriangle;
class MeshTriangleNode;
class MeshLayer;

class MeshTriangleEdge : public QObject, public QGraphicsLineItem
{
	Q_OBJECT;

public:
	MeshTriangleEdge(
		MeshLayer * ml,
		std::array<MeshTriangleNode*, 2> ends,
		QGraphicsItem * parent = nullptr
	);
	virtual ~MeshTriangleEdge();

	std::array<MeshTriangleNode*, 2> getEnds() const;

	void addTriangleLink(MeshTriangle * mt);
	int getTriangleLinkCount() const;

	bool canExtrude() const;

	void setActivated(bool activated);

signals:
	void clicked(MeshTriangleEdge * mte, const QGraphicsSceneMouseEvent*);

	//Wysyłany przy rozłączeniu ze wszystkimi trójkątami
	void unlinked(MeshTriangleEdge * mte);

public slots:
	void updatePosition(MeshTriangleNode * mtn, const QPointF&);
	void remTriangleLink(MeshTriangle * mt);

protected:
	void contextMenuEvent(QGraphicsSceneContextMenuEvent * event) override;
	void mousePressEvent(QGraphicsSceneMouseEvent * event) override;

private:
	void refreshLook();

	MeshLayer * parentLayer;
	std::array<MeshTriangleNode*, 2> ends;
	QList<MeshTriangle*> linkedTriangles;

	bool isActive;
};

}}
