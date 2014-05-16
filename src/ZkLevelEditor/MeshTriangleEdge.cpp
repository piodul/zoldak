#include "MeshTriangleEdge.h"
#include "MeshTriangleNode.h"
#include "LevelView.h"

#include <QtCore>
#include <QtGui>

using namespace Zk::LevelEditor;

MeshTriangleEdge::MeshTriangleEdge(
	LevelView * lv,
	std::array<MeshTriangleNode*, 2> ends,
	QGraphicsItem * parent
)
	: QGraphicsLineItem(parent)
{
	this->ends = ends;
	
	for (MeshTriangleNode * end : ends)
	{
		connect(end, SIGNAL(moved(MeshTriangleNode*, const QPointF&)),
			this, SLOT(updatePosition(MeshTriangleNode*, const QPointF&)));
	}
	
	QPen pen(QColor(0, 127, 255));
	pen.setWidth(8);
	setPen(pen);
	setLine(QLineF(ends[0]->pos(), ends[1]->pos()));
	
	canExtrude = true;
}

MeshTriangleEdge::~MeshTriangleEdge()
{
	
}

std::array<MeshTriangleNode*, 2> MeshTriangleEdge::getEnds() const
{
	return ends;
}

void MeshTriangleEdge::deactivateExtruding()
{
	canExtrude = false;
	QPen pen(QColor(0, 127, 127));
	pen.setWidth(8);
	setPen(pen);
	setLine(QLineF(ends[0]->pos(), ends[1]->pos()));
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
	if (canExtrude)
		emit clicked(this, event->pos());
}
