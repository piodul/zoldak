#include "../ZkCommon/Level.h"

#include "MainWindow.h"
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

LevelView::LevelView(
	MainWindow * mw,
	ColorPaletteWidget * palette,
	QWidget * parent
)
	: QGraphicsView(parent)
{
	window = mw;
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
	
	mainLayer = new MeshLayer(scene(), palette, this);
	connect(mainLayer, SIGNAL(statusTextChanged(QString)),
		window, SLOT(setStatusText(QString)));
	
	bgItem = new BackgroundItem(this);
	connect(bgItem, SIGNAL(contextMenuOpened(const QPoint&, const QPointF&)),
		mainLayer, SLOT(contextMenu(const QPoint&, const QPointF&)));
	connect(bgItem, SIGNAL(clicked()),
		mainLayer, SLOT(backgroundClicked()));
	scene()->addItem(bgItem);
	
	isDragging = false;
}

LevelView::~LevelView()
{
	
}

bool LevelView::fromCommonLevel(const Common::Level & l)
{
	const std::vector<Common::LevelLayer*> & lls = l.getLayers();
	
	//Na razie ładujemy tylko jedną warstwę
	return mainLayer->fromCommonLevelLayer(*lls[0]);
}

void LevelView::toCommonLevel(Common::Level & l) const
{
	l.clear();
	
	std::vector<Common::LevelLayer*> lls;
	lls.push_back(new Common::LevelLayer());
	mainLayer->toCommonLevelLayer(*lls[0]);
	
	l.setLayers(lls);
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
