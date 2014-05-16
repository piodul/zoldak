#include "LevelView.h"
#include "MeshTriangleNode.h"
#include "MeshTriangle.h"
#include "MeshTriangleEdge.h"

#include <QtCore>
#include <QtGui>
#include <QDebug>

using namespace Zk::LevelEditor;

LevelView::LevelView(QWidget * parent)
	: QGraphicsView(parent)
{
	setScene(new QGraphicsScene());
	
	setContextMenuPolicy(Qt::CustomContextMenu);
	connect(this, SIGNAL(customContextMenuRequested(const QPoint&)),
		this, SLOT(showContextMenu(const QPoint&)));
	
	setDragMode(QGraphicsView::RubberBandDrag);
	
	MeshTriangleNode * na = createNode(QPoint(0, 0));
	MeshTriangleNode * nb = createNode(QPoint(0, 200));
	MeshTriangleNode * nc = createNode(QPoint(200, 0));
	
	//MeshTriangleNode * verts[3] = { na, nb, nc };
	//createTriangle(verts);
	createTriangle({ na, nb, nc });
	createTriangleEdge({ na, nb });
	createTriangleEdge({ nb, nc });
	createTriangleEdge({ nc, na });
}

LevelView::~LevelView()
{
	
}

void LevelView::showContextMenu(const QPoint & pos)
{
	QPoint globalPos = mapToGlobal(pos);
	
	QMenu menu;
	QAction * addNewNode = menu.addAction("Add node");
	
	QAction * selectedAction = menu.exec(globalPos);
	if (selectedAction != nullptr)
	{
		if (selectedAction == addNewNode)
			createNode(mapToScene(pos));
	}
}

void LevelView::triangleNodeClicked(MeshTriangleNode * mtn)
{
	qDebug() << "MTN clicked";
}

void LevelView::triangleEdgeClicked(MeshTriangleEdge * mte, const QPointF & pos)
{
	qDebug() << "MTE clicked";
	
	std::array<MeshTriangleNode*, 2> ends = mte->getEnds();
	
	//Create triangle "protruding" form the edge
	// MeshTriangleNode * mtn = new MeshTriangleNode(this);
	// mtn->setPos(pos);
	MeshTriangleNode * mtn = createNode(pos);
	createTriangle({ mtn, ends[0], ends[1] });
	//createTriangleEdge(ends); //Include it or not?
	createTriangleEdge({ mtn, ends[0] });
	createTriangleEdge({ mtn, ends[1] });
}

MeshTriangleNode * LevelView::createNode(const QPointF & pos)
{
	MeshTriangleNode * mtn = new MeshTriangleNode(this);
	mtn->setPos(pos);
	
	connect(mtn, SIGNAL(clicked(MeshTriangleNode*)),
		this, SLOT(triangleNodeClicked(MeshTriangleNode*)));
	
	scene()->addItem(mtn);
	return mtn;
}

MeshTriangle * LevelView::createTriangle(std::array<MeshTriangleNode*, 3> verts)
{
	MeshTriangle * mt = new MeshTriangle(this, verts);
	
	for (int i : { 0, 1, 2 })
		verts[i]->attachTriangle(mt);
	
	scene()->addItem(mt);
	return mt;
}

MeshTriangleEdge * LevelView::createTriangleEdge(std::array<MeshTriangleNode*, 2> ends)
{
	MeshTriangleEdge * mte = new MeshTriangleEdge(this, ends);
	
	connect(mte, SIGNAL(clicked(MeshTriangleEdge*, const QPointF&)),
		this, SLOT(triangleEdgeClicked(MeshTriangleEdge*, const QPointF&)));
	
	scene()->addItem(mte);
	return mte;
}
