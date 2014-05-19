#include "BackgroundItem.h"
#include "LevelView.h"

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
	
}

void BackgroundItem::updateSceneView()
{
	QRect viewportRect(QPoint(0, 0), view->viewport()->size());
	sceneRect = view->mapToScene(viewportRect).boundingRect();
}

void BackgroundItem::contextMenuEvent(QGraphicsSceneContextMenuEvent * event)
{
	emit contextMenuOpened(event->pos());
}
