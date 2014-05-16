#pragma once

#include <QtWidgets>

namespace Zk {
namespace LevelEditor {

class MeshTriangle;
class MeshLayer;

class MeshTriangleNode : public QObject, public QGraphicsEllipseItem
{
	Q_OBJECT;
	
public:
	MeshTriangleNode(MeshLayer * ml, QGraphicsItem * parent = nullptr);
	virtual ~MeshTriangleNode();
	
	void attachTriangle(MeshTriangle * mt);

signals:
	void clicked(MeshTriangleNode * mtn);
	void moved(MeshTriangleNode * mtn, const QPointF & pos);
	
protected:
	void mousePressEvent(QGraphicsSceneMouseEvent * event) override;
	void contextMenuEvent(QGraphicsSceneContextMenuEvent * event) override;
	QVariant itemChange(GraphicsItemChange change, const QVariant & value) override;

private:
	MeshLayer * parentLayer;
	QList<MeshTriangle*> linkedTriangles;
};

}}
