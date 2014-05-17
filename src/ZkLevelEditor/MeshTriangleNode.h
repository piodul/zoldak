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
	void setColor(const QColor & color);
	QColor getColor() const;

signals:
	void clicked(MeshTriangleNode * mtn);
	void moved(MeshTriangleNode * mtn, const QPointF & pos);
	void colorChanged(MeshTriangleNode * mtn);
	
protected:
	void mousePressEvent(QGraphicsSceneMouseEvent * event) override;
	void contextMenuEvent(QGraphicsSceneContextMenuEvent * event) override;
	QVariant itemChange(GraphicsItemChange change, const QVariant & value) override;

private:
	MeshLayer * parentLayer;
	QColor color;
	QList<MeshTriangle*> linkedTriangles;
};

}}
