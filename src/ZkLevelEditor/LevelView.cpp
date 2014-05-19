#include "LevelView.h"
#include "MeshTriangleNode.h"
#include "MeshTriangle.h"
#include "MeshTriangleEdge.h"
#include "MeshLayer.h"
#include "BackgroundItem.h"

#include <QtCore>
#include <QtGui>
#include <QGLWidget>
#include <QDebug>

using namespace Zk::LevelEditor;

LevelView::LevelView(QWidget * parent)
	: QGraphicsView(parent)
{
	setScene(new QGraphicsScene());
	
	//Włączamy OpenGL (dla rysowania trójkątów)
	setViewport(new QGLWidget());
	
	//setContextMenuPolicy(Qt::CustomContextMenu);
	// connect(this, SIGNAL(customContextMenuRequested(const QPoint&)),
	// 	this, SLOT(showContextMenu(const QPoint&)));
	
	setDragMode(QGraphicsView::RubberBandDrag);
	
	setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
	setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
	
	setSceneRect(QRect(0, 0, 1, 1));
	
	mainLayer = new MeshLayer(scene(), this);
	bgItem = new BackgroundItem(this);
	connect(bgItem, SIGNAL(contextMenuOpened(const QPoint&)),
		this, SLOT(contextMenu(const QPoint&)));
	scene()->addItem(bgItem);
}

LevelView::~LevelView()
{
	
}

void LevelView::contextMenu(const QPoint & pos)
{
	QMenu menu;
	qDebug() << "DUPA";
	QAction * removeAction = menu.addAction("&Dummy");
	menu.exec(pos);
}

void LevelView::mousePressEvent(QMouseEvent * event)
{
	if (event->modifiers() & Qt::ShiftModifier)
	{
		isDragging = true;
		oldMousePos = event->pos();
		qDebug() << "Started dragging!";
	}
	else
		QGraphicsView::mousePressEvent(event);
}

void LevelView::mouseMoveEvent(QMouseEvent * event)
{
	if (isDragging)
	{
		QPoint delta = event->pos() - oldMousePos;
		//translate(delta.x(), delta.y());
		setSceneRect(sceneRect().translated(-delta));
		bgItem->updateSceneView();
		
		oldMousePos = event->pos();
		
		qDebug() << delta;
	}
	else
		QGraphicsView::mouseMoveEvent(event);
}

void LevelView::resizeEvent(QResizeEvent * event)
{
	QGraphicsView::resizeEvent(event);
	bgItem->updateSceneView();
}

void LevelView::mouseReleaseEvent(QMouseEvent * event)
{
	isDragging = false;
	QGraphicsView::mouseReleaseEvent(event);
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
