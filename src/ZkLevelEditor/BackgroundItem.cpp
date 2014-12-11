#include "../ZkCommon/Constants.hpp"

#include "BackgroundItem.hpp"
#include "LevelView.hpp"

#include <QtCore>
#include <QtGui>

using namespace Zk::LevelEditor;

BackgroundItem::BackgroundItem(QGraphicsView * view, QGraphicsItem * parent)
	: QGraphicsObject(parent)
{
	this->view = view;
	setZValue(-1024.0);
	updateSceneView();
}

BackgroundItem::~BackgroundItem()
{

}

QRectF BackgroundItem::boundingRect() const
{
	return sceneRect;
}

QPainterPath BackgroundItem::shape() const
{
	QPainterPath pp;
	pp.addRect(sceneRect);
	return pp;
}

void BackgroundItem::paint(
	QPainter * painter,
	const QStyleOptionGraphicsItem * option,
	QWidget * widget
)
{
	painter->setBrush(QBrush(QColor(200, 200, 200)));
	painter->setPen(QPen(QColor(), 0.0));
	painter->drawRect(sceneRect);
}

void BackgroundItem::updateSceneView()
{
	prepareGeometryChange();
	QRect viewportRect(QPoint(0, 0), view->viewport()->size());
	sceneRect = view->mapToScene(viewportRect).boundingRect();
}

void BackgroundItem::mousePressEvent(QGraphicsSceneMouseEvent * event)
{
	QGraphicsObject::mousePressEvent(event);
	emit clicked();
}

void BackgroundItem::contextMenuEvent(QGraphicsSceneContextMenuEvent * event)
{
	qDebug() << "BackgroundItem::contextMenuEvent";
	emit contextMenuOpened(event->screenPos(), event->pos());
}
