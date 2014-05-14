#pragma once

#include <QtWidgets>

namespace Zk {
namespace LevelEditor {

class MeshTriangle;
class LevelView;

class TriangleNode : public QObject, public QGraphicsEllipseItem
{
	Q_OBJECT;
	
public:
	TriangleNode(LevelView * lv, QGraphicsItem * parent = nullptr);
	virtual ~TriangleNode();
	
	void attachTriangle(MeshTriangle * mt);

signals:
	void clicked(TriangleNode * tn);
	void moved(TriangleNode * tn, const QPointF & pos);
	
protected:
	void mousePressEvent(QGraphicsSceneMouseEvent * event) override;
	void contextMenuEvent(QGraphicsSceneContextMenuEvent * event) override;
	QVariant itemChange(GraphicsItemChange change, const QVariant & value) override;

private:
	LevelView * parentView;
	QList<MeshTriangle*> linkedTriangles;
};

}}
