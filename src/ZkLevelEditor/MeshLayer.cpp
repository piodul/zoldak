#include "MeshLayer.h"
#include "MeshTriangle.h"
#include "MeshTriangleNode.h"
#include "MeshTriangleEdge.h"

#include <QtCore>
#include <QtGui>
#include <QDebug>

using namespace Zk::LevelEditor;

MeshLayer::MeshLayer(QGraphicsScene * scene, QObject * parent)
	: QObject(parent), scene(scene)
{
	MeshTriangleNode * na = createNode(QPoint(0, 0));
	MeshTriangleNode * nb = createNode(QPoint(0, 200));
	MeshTriangleNode * nc = createNode(QPoint(200, 0));
	
	createTriangle({ na, nb, nc });
	createEdge({ na, nb });
	createEdge({ nb, nc });
	createEdge({ nc, na });
}

MeshLayer::~MeshLayer()
{
	
}

void MeshLayer::triangleNodeClicked(MeshTriangleNode * mtn)
{
	qDebug() << "MTN clicked";
}

void MeshLayer::triangleEdgeClicked(MeshTriangleEdge * mte, const QPointF & pos)
{
	qDebug() << "MTE clicked";
	
	std::array<MeshTriangleNode*, 2> ends = mte->getEnds();
	
	//Create triangle "protruding" form the edge
	// MeshTriangleNode * mtn = new MeshTriangleNode(this);
	// mtn->setPos(pos);
	MeshTriangleNode * mtn = createNode(pos);
	createTriangle({ mtn, ends[0], ends[1] });
	//createEdge(ends); //Include it or not?
	createEdge({ mtn, ends[0] });
	createEdge({ mtn, ends[1] });
}

MeshTriangleNode * MeshLayer::createNode(const QPointF & pos)
{
	MeshTriangleNode * mtn = new MeshTriangleNode(this);
	mtn->setPos(pos);
	
	connect(mtn, SIGNAL(clicked(MeshTriangleNode*)),
		this, SLOT(triangleNodeClicked(MeshTriangleNode*)));
	
	nodes << mtn;
	scene->addItem(mtn);
	return mtn;
}

MeshTriangle * MeshLayer::createTriangle(std::array<MeshTriangleNode*, 3> verts)
{
	MeshTriangle * mt = new MeshTriangle(this, verts);
	
	for (int i : { 0, 1, 2 })
		verts[i]->attachTriangle(mt);
	
	triangles << mt;
	scene->addItem(mt);
	return mt;
}

MeshTriangleEdge * MeshLayer::createEdge(std::array<MeshTriangleNode*, 2> ends)
{
	MeshTriangleEdge * mte = new MeshTriangleEdge(this, ends);
	
	connect(mte, SIGNAL(clicked(MeshTriangleEdge*, const QPointF&)),
		this, SLOT(triangleEdgeClicked(MeshTriangleEdge*, const QPointF&)));
	
	edges << mte;
	scene->addItem(mte);
	return mte;
}
