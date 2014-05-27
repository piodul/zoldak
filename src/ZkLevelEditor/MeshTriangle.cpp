#include "MeshTriangle.h"
#include "MeshTriangleNode.h"
#include "MeshTriangleEdge.h"
#include "MeshLayer.h"

#include <QtCore>
#include <QtGui>
#include <QtOpenGL>
#include <QDebug>

#include <algorithm>

using namespace Zk::LevelEditor;

MeshTriangle::MeshTriangle(
	MeshLayer * ml,
	std::array<MeshTriangleNode*, 3> verts,
	std::array<MeshTriangleEdge*, 3> edges,
	QGraphicsItem * parent
)
	: QGraphicsObject(parent)
{
	parentLayer = ml;
	this->verts = verts;
	this->edges = edges;
	
	vColors = { Qt::black, Qt::black, Qt::black };
	
	swappedColorID = -1;
	
	for (MeshTriangleNode * vert : verts)
	{
		vert->addTriangleLink(this);
		
		connect(vert, SIGNAL(moved(MeshTriangleNode*, const QPointF&)),
			this, SLOT(updatePosition(MeshTriangleNode*, const QPointF&)));
		
		connect(this, SIGNAL(destroyed(MeshTriangle*)),
			vert, SLOT(remTriangleLink(MeshTriangle*)));
	}
	
	for (MeshTriangleEdge * edge : edges)
	{
		edge->addTriangleLink(this);
		
		connect(this, SIGNAL(destroyed(MeshTriangle*)),
			edge, SLOT(remTriangleLink(MeshTriangle*)));
	}
	
	setAcceptHoverEvents(true);
	
	updatePosition(nullptr, QPointF());
	
	setZValue(-1.0);
}

MeshTriangle::~MeshTriangle()
{
	emit destroyed(this);
	//parentLayer->triangleDestroyed(this);
}

QRectF MeshTriangle::boundingRect() const
{
	QRectF ret(verts[0]->pos(), QSize());
	ret = ret.united(QRectF(verts[1]->pos(), QSize()));
	ret = ret.united(QRectF(verts[2]->pos(), QSize()));
	
	return ret;
}

void MeshTriangle::paint(
	QPainter * painter,
	const QStyleOptionGraphicsItem * option,
	QWidget * widget
)
{
	if (painter->paintEngine()->type() != QPaintEngine::OpenGL2)
	{
		qDebug() << "Warning: supplied QPainter has OpenGL disabled!";
	}
	
	painter->beginNativePainting();
	
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	
	glBegin(GL_TRIANGLES);
	int id = 0;
	for (MeshTriangleNode * vert : verts)
	{
		QColor color = (id != swappedColorID) ? vColors[id] : swappedColor;
		QPointF pos = vert->pos();
		glColor4f(color.redF(), color.greenF(), color.blueF(), color.alphaF());
		glVertex2f(pos.x(), pos.y());
		id++;
	}
	glEnd();
	
	painter->endNativePainting();
}

QPainterPath MeshTriangle::shape() const
{
	QPolygonF poly;
	poly << verts[0]->pos() << verts[1]->pos() << verts[2]->pos();
	
	QPainterPath pp;
	pp.addPolygon(poly);
	
	return pp;
}

const std::array<MeshTriangleNode*, 3> & MeshTriangle::getLinkedNodes() const
{
	return verts;
}

const std::array<MeshTriangleEdge*, 3> & MeshTriangle::getLinkedEdges() const
{
	return edges;
}

const std::array<QColor, 3> & MeshTriangle::getColors() const
{
	return vColors;
}

void MeshTriangle::setColors(const std::array<QColor, 3> & colors)
{
	vColors = colors;
	update();
}

void MeshTriangle::updatePosition(MeshTriangleNode * mtn, const QPointF & pos)
{
	prepareGeometryChange();
	update();
}

void MeshTriangle::contextMenuEvent(QGraphicsSceneContextMenuEvent * event)
{
	//Nie przepuszczamy menu kontekstowego niżej
	event->accept();
}

void MeshTriangle::mousePressEvent(QGraphicsSceneMouseEvent * event)
{
	if (event->modifiers() & Qt::ControlModifier)
	{
		event->accept();
		delete this; //Zastanowić się czy to dobry pomysł
	}
	else
	{
		//Czasami dziwnym trafem udaje się kliknąć przed hoverem
		if (swappedColorID != -1)
			vColors[swappedColorID]  = swappedColor;
		QGraphicsObject::mousePressEvent(event);
	}
	qDebug() << "Clicked!";
}

void MeshTriangle::hoverMoveEvent(QGraphicsSceneHoverEvent * event)
{
	auto range = { 0, 1, 2 };
	swappedColorID = *std::min_element(
		range.begin(), range.end(),
		[&](int a, int b) -> bool
		{
			return  QVector2D(verts[a]->pos() - event->pos()).lengthSquared() <
					QVector2D(verts[b]->pos() - event->pos()).lengthSquared();
		}
	);
	swappedColor = parentLayer->getSelectedColor();
	update();
	event->accept();
}

void MeshTriangle::hoverLeaveEvent(QGraphicsSceneHoverEvent * event)
{
	swappedColorID = -1;
	update();
	event->accept();
}
