#include "LevelView.h"
#include "TriangleNode.h"
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
	
	TriangleNode * na = createNode(QPoint(0, 0));
	TriangleNode * nb = createNode(QPoint(0, 200));
	TriangleNode * nc = createNode(QPoint(200, 0));
	
	//TriangleNode * verts[3] = { na, nb, nc };
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

void LevelView::triangleNodeClicked(TriangleNode * tn)
{
	qDebug() << "TN clicked";
}

void LevelView::triangleEdgeClicked(MeshTriangleEdge * mte, const QPointF & pos)
{
	qDebug() << "MTE clicked";
	
	std::array<TriangleNode*, 2> ends = mte->getEnds();
	
	//Create triangle "protruding" form the edge
	// TriangleNode * tn = new TriangleNode(this);
	// tn->setPos(pos);
	TriangleNode * tn = createNode(pos);
	createTriangle({ tn, ends[0], ends[1] });
	//createTriangleEdge(ends); //Include it or not?
	createTriangleEdge({ tn, ends[0] });
	createTriangleEdge({ tn, ends[1] });
}

TriangleNode * LevelView::createNode(const QPointF & pos)
{
	TriangleNode * tn = new TriangleNode(this);
	tn->setPos(pos);
	
	connect(tn, SIGNAL(clicked(TriangleNode*)),
		this, SLOT(triangleNodeClicked(TriangleNode*)));
	
	scene()->addItem(tn);
	return tn;
}

MeshTriangle * LevelView::createTriangle(std::array<TriangleNode*, 3> verts)
{
	MeshTriangle * mt = new MeshTriangle(this, verts);
	
	for (int i : { 0, 1, 2 })
		verts[i]->attachTriangle(mt);
	
	scene()->addItem(mt);
	return mt;
}

MeshTriangleEdge * LevelView::createTriangleEdge(std::array<TriangleNode*, 2> ends)
{
	MeshTriangleEdge * mte = new MeshTriangleEdge(this, ends);
	
	connect(mte, SIGNAL(clicked(MeshTriangleEdge*, const QPointF&)),
		this, SLOT(triangleEdgeClicked(MeshTriangleEdge*, const QPointF&)));
	
	scene()->addItem(mte);
	return mte;
}
