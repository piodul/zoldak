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
	
	void attachTriangle(MeshTriangle * mt);
	void setColor(const QColor & color);
	QColor getColor() const;
	
	void addTriangleLink(MeshTriangle * mt);
	int getTriangleLinkCount() const;
	void remTriangleLink(MeshTriangle * mt);
	
	void addEdgeLink(MeshTriangleEdge * mte);
	int getEdgeLinkCount() const;
	void remEdgeLink(MeshTriangleEdge * mte);
	
	const QList<MeshTriangle*> getLinkedTriangles();

signals:
	void clicked(MeshTriangleNode * mtn);
	void moved(MeshTriangleNode * mtn, const QPointF & pos);
	void colorChanged(MeshTriangleNode * mtn);
	void unlinked(MeshTriangleNode * mtn);
	
protected:
	void mousePressEvent(QGraphicsSceneMouseEvent * event) override;
	void contextMenuEvent(QGraphicsSceneContextMenuEvent * event) override;
	QVariant itemChange(GraphicsItemChange change, const QVariant & value) override;

private:
	MeshLayer * parentLayer;
	QColor color;
	QList<MeshTriangle*> linkedTriangles;
	QList<MeshTriangleEdge*> linkedEdges;
};

}}
