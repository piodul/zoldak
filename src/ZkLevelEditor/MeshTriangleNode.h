#pragma once

#include <QtWidgets>

namespace Zk {
namespace LevelEditor {

class MeshTriangle;
class LevelView;

class MeshTriangleNode : public QObject, public QGraphicsEllipseItem
{
	Q_OBJECT;
	
public:
	MeshTriangleNode(LevelView * lv, QGraphicsItem * parent = nullptr);
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
	LevelView * parentView;
	QList<MeshTriangle*> linkedTriangles;
};

}}
