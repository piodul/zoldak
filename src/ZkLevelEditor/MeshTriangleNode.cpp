#include "../ZkCommon/Constants.hpp"

#include "MeshTriangleNode.hpp"
#include "MeshLayer.hpp"

#include <QtCore>
#include <QtGui>
#include <QDebug>

using namespace Zk::Common;
using namespace Zk::LevelEditor;

MeshTriangleNode::MeshTriangleNode(MeshLayer * ml, QGraphicsItem * parent)
	: QGraphicsEllipseItem(parent)
{
	parentLayer = ml;

	marked = false;
	setActivated(true);
	refreshLook();
}

MeshTriangleNode::~MeshTriangleNode()
{

}

void MeshTriangleNode::addTriangleLink(MeshTriangle * mt)
{
	linkedTriangles << mt;
}

int MeshTriangleNode::getTriangleLinkCount() const
{
	return linkedTriangles.size();
}

void MeshTriangleNode::remTriangleLink(MeshTriangle * mt)
{
	linkedTriangles.removeOne(mt);

	if (linkedTriangles.size() == 0 && linkedEdges.size() == 0)
		emit unlinked(this);
}

void MeshTriangleNode::addEdgeLink(MeshTriangleEdge * mt)
{
	linkedEdges << mt;
}

int MeshTriangleNode::getEdgeLinkCount() const
{
	return linkedEdges.size();
}

void MeshTriangleNode::remEdgeLink(MeshTriangleEdge * mte)
{
	linkedEdges.removeOne(mte);

	if (linkedTriangles.size() == 0 && linkedEdges.size() == 0)
		emit unlinked(this);
}

const QList<MeshTriangle*> & MeshTriangleNode::getLinkedTriangles() const
{
	return linkedTriangles;
}

const QList<MeshTriangleEdge*> & MeshTriangleNode::getLinkedEdges() const
{
	return linkedEdges;
}

void MeshTriangleNode::setMarked(bool marked)
{
	this->marked = marked;
	refreshLook();
}

bool MeshTriangleNode::isMarked() const
{
	return marked;
}

void MeshTriangleNode::setActivated(bool activated)
{
	isActive = activated;

	setFlag(QGraphicsItem::ItemIsSelectable, isActive);
	setFlag(QGraphicsItem::ItemIsMovable, isActive);
	setFlag(QGraphicsItem::ItemSendsGeometryChanges, true);

	refreshLook();
}

void MeshTriangleNode::mousePressEvent(QGraphicsSceneMouseEvent * event)
{
	if (!isActive)
		return;

	QGraphicsEllipseItem::mousePressEvent(event);
	emit clicked(this, event);
}

void MeshTriangleNode::contextMenuEvent(QGraphicsSceneContextMenuEvent * event)
{
	event->accept();
}

QVariant MeshTriangleNode::itemChange(
	GraphicsItemChange change,
	const QVariant & value
)
{
	if (change == ItemPositionChange)
		emit moved(this, value.toPointF());

	return QGraphicsEllipseItem::itemChange(change, value);
}

void MeshTriangleNode::refreshLook()
{
	if (isActive)
	{
		if (marked)
			setPen(QPen(QBrush(Qt::blue), 3.0 * Constants::METERS_PER_PIXEL));
		else
			setPen(QPen(QBrush(Qt::white), 2.0 * Constants::METERS_PER_PIXEL));
	}
	else
		setPen(QPen(QBrush(Qt::gray), 1.0 * Constants::METERS_PER_PIXEL));

	setBrush(QBrush(QColor(0, 0, 0)));
	setRect(QRectF(
		-8.0 * Constants::METERS_PER_PIXEL,
		-8.0 * Constants::METERS_PER_PIXEL,
		16.0 * Constants::METERS_PER_PIXEL,
		16.0 * Constants::METERS_PER_PIXEL
	));

	double z = (isActive ? 1024.0 : (double)-parentLayer->getIndex());
	setZValue(z + 0.2);
}
