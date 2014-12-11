#pragma once

#include <QtWidgets>

namespace Zk {
namespace LevelEditor {

class MeshTriangle;
class MeshTriangleEdge;
class MeshLayer;

class MeshTriangleNode : public QObject, public QGraphicsEllipseItem
{
	Q_OBJECT;

public:
	MeshTriangleNode(MeshLayer * ml, QGraphicsItem * parent = nullptr);
	virtual ~MeshTriangleNode();

	void addTriangleLink(MeshTriangle * mt);
	int getTriangleLinkCount() const;

	void addEdgeLink(MeshTriangleEdge * mte);
	int getEdgeLinkCount() const;

	const QList<MeshTriangle*> & getLinkedTriangles() const;
	const QList<MeshTriangleEdge*> & getLinkedEdges() const;

	void setMarked(bool marked);
	bool isMarked() const;

	void setActivated(bool activated);

signals:
	void clicked(MeshTriangleNode * mtn, const QGraphicsSceneMouseEvent * event);
	void moved(MeshTriangleNode * mtn, const QPointF & pos);

	//Wysyłany przy rozłączeniu ze wszystkimi trójkątami
	void unlinked(MeshTriangleNode * mtn);

public slots:
	void remTriangleLink(MeshTriangle * mt);
	void remEdgeLink(MeshTriangleEdge * mte);

protected:
	void mousePressEvent(QGraphicsSceneMouseEvent * event) override;
	void contextMenuEvent(QGraphicsSceneContextMenuEvent * event) override;
	QVariant itemChange(GraphicsItemChange change, const QVariant & value) override;

private:
	void refreshLook();

	MeshLayer * parentLayer;
	QList<MeshTriangle*> linkedTriangles;
	QList<MeshTriangleEdge*> linkedEdges;

	bool isActive;

	bool marked;
};

}}
