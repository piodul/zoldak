#include "../ZkCommon/Constants.hpp"

#include "MeshTriangleEdge.hpp"
#include "MeshTriangleNode.hpp"
#include "MeshLayer.hpp"

#include <QtCore>
#include <QtGui>

using namespace Zk::Common;
using namespace Zk::LevelEditor;

MeshTriangleEdge::MeshTriangleEdge(
	MeshLayer * ml,
	std::array<MeshTriangleNode*, 2> ends,
	QGraphicsItem * parent
)
	: QGraphicsLineItem(parent)
{
	this->ends = ends;

	parentLayer = ml;

	for (MeshTriangleNode * end : ends)
	{
		end->addEdgeLink(this);

		connect(end, SIGNAL(moved(MeshTriangleNode*, const QPointF&)),
			this, SLOT(updatePosition(MeshTriangleNode*, const QPointF&)));

		connect(this, SIGNAL(unlinked(MeshTriangleEdge*)),
			end, SLOT(remEdgeLink(MeshTriangleEdge*)));
	}

	isActive = true;
	refreshLook();
}

MeshTriangleEdge::~MeshTriangleEdge()
{

}

std::array<MeshTriangleNode*, 2> MeshTriangleEdge::getEnds() const
{
	return ends;
}

void MeshTriangleEdge::addTriangleLink(MeshTriangle * mt)
{
	linkedTriangles << mt;
	refreshLook();
}

int MeshTriangleEdge::getTriangleLinkCount() const
{
	return linkedTriangles.size();
}

bool MeshTriangleEdge::canExtrude() const
{
	return getTriangleLinkCount() < 2;
}

void MeshTriangleEdge::setActivated(bool activated)
{
	isActive = activated;
	refreshLook();
}

void MeshTriangleEdge::remTriangleLink(MeshTriangle * mt)
{
	linkedTriangles.removeOne(mt);
	refreshLook();

	if (linkedTriangles.size() == 0)
		emit unlinked(this);
}

void MeshTriangleEdge::updatePosition(MeshTriangleNode * mtn, const QPointF & pos)
{
	if (mtn == ends[0])
		setLine(QLineF(pos, ends[1]->pos()));
	else if (mtn == ends[1])
		setLine(QLineF(ends[0]->pos(), pos));
}

void MeshTriangleEdge::mousePressEvent(QGraphicsSceneMouseEvent * event)
{
	QGraphicsLineItem::mousePressEvent(event);

	if (!isActive)
		return;

	if (event->button() == Qt::LeftButton)
		emit clicked(this, event);
}

void MeshTriangleEdge::contextMenuEvent(QGraphicsSceneContextMenuEvent * event)
{
	//Nie przepuszczamy menu kontekstowego niżej
	if (isActive)
		event->accept();
}

void MeshTriangleEdge::refreshLook()
{
	//TODO: Zrobić ztych magicznych liczb stałe
	QPen pen;
	if (isActive && canExtrude())
	{
		pen.setColor(QColor(0, 127, 255));
		pen.setWidthF(8.0 * Constants::METERS_PER_PIXEL);
	}
	else
	{
		pen.setColor(QColor(127, 127, 127));
		pen.setWidthF(2.0 * Constants::METERS_PER_PIXEL);
	}

	setPen(pen);
	setLine(QLineF(ends[0]->pos(), ends[1]->pos()));

	double z = (isActive ? 1024.0 : (double)-parentLayer->getIndex());
	setZValue(z + 0.1);
}
