#pragma once

#include <QtWidgets>

namespace Zk {
namespace LevelEditor {

class BackgroundItem : public QGraphicsObject
{
	Q_OBJECT;

public:
	BackgroundItem(QGraphicsView * view, QGraphicsItem * parent = nullptr);
	virtual ~BackgroundItem();

	virtual QRectF boundingRect() const override;
	virtual QPainterPath shape() const override;
	virtual void paint(
		QPainter * painter,
		const QStyleOptionGraphicsItem * option,
		QWidget * widget = nullptr
	) override;

signals:
	void contextMenuOpened(const QPoint & pos, const QPointF & scenePos);
	void clicked();

public slots:
	void updateSceneView();

protected:
	void mousePressEvent(QGraphicsSceneMouseEvent * event) override;
	void contextMenuEvent(QGraphicsSceneContextMenuEvent * event) override;

private:
	QGraphicsView * view;
	QRectF sceneRect;
};

}}
