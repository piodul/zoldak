#include "LevelView.h"
#include "MeshTriangleNode.h"
#include "MeshTriangle.h"
#include "MeshTriangleEdge.h"
#include "MeshLayer.h"

#include <QtCore>
#include <QtGui>
#include <QDebug>

using namespace Zk::LevelEditor;

LevelView::LevelView(QWidget * parent)
	: QGraphicsView(parent)
{
	setScene(new QGraphicsScene());
	
	setContextMenuPolicy(Qt::CustomContextMenu);
	// connect(this, SIGNAL(customContextMenuRequested(const QPoint&)),
	// 	this, SLOT(showContextMenu(const QPoint&)));
	
	setDragMode(QGraphicsView::RubberBandDrag);
	
	mainLayer = new MeshLayer(scene(), this);
}

LevelView::~LevelView()
{
	
}

// void LevelView::showContextMenu(const QPoint & pos)
// {
// 	QPoint globalPos = mapToGlobal(pos);
	
// 	QMenu menu;
// 	QAction * addNewNode = menu.addAction("Add node");
	
// 	QAction * selectedAction = menu.exec(globalPos);
// 	if (selectedAction != nullptr)
// 	{
// 		if (selectedAction == addNewNode)
// 			createNode(mapToScene(pos));
// 	}
// }
