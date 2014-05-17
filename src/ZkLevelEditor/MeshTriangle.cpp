#include "MeshTriangle.h"
#include "MeshTriangleNode.h"
#include "MeshLayer.h"

#include <QtCore>
#include <QtGui>
#include <QtOpenGL>
#include <QDebug>

using namespace Zk::LevelEditor;

MeshTriangle::MeshTriangle(
	MeshLayer * ml,
	std::array<MeshTriangleNode*, 3> verts,
	QGraphicsItem * parent
)
	: QGraphicsObject(parent)
{
	parentLayer = ml;
	this->verts = verts;
	
	for (MeshTriangleNode * vert : verts)
	{
		connect(vert, SIGNAL(moved(MeshTriangleNode*, const QPointF&)),
			this, SLOT(updatePosition(MeshTriangleNode*, const QPointF&)));
		
		connect(vert, SIGNAL(colorChanged(MeshTriangleNode*)),
			this, SLOT(updateColors()));
	}
	
	updatePosition(nullptr, QPointF());
	
	//setBrush(QBrush(QColor(255, 127, 0)));
	//setPen(QPen(Qt::transparent));
	setZValue(-1.0);
}

MeshTriangle::~MeshTriangle()
{
	
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
	for (MeshTriangleNode * vert : verts)
	{
		QColor color = vert->getColor();
		QPointF pos = vert->pos();
		glColor4f(color.redF(), color.greenF(), color.blueF(), color.alphaF());
		glVertex2f(pos.x(), pos.y());
	}
	glEnd();
	
	painter->endNativePainting();
}

void MeshTriangle::updatePosition(MeshTriangleNode * mtn, const QPointF & pos)
{
	/*QPolygonF poly;
	for (MeshTriangleNode * vert : verts)
	{
		if (vert == mtn)
			poly << pos;
		else
			poly << vert->pos();
	}
	
	QPainterPath path;
	path.addPolygon(poly);
	setPath(path);*/
	update();
}

void MeshTriangle::updateColors()
{
	update();
}
