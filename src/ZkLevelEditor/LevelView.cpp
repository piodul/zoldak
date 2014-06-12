#include "../ZkCommon/Constants.h"
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

using namespace Zk::Common;
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
	
	bgItem = new BackgroundItem(this);
	scene()->addItem(bgItem);
	
	for (int i = 0; i < (int)LayerType::MAX_LAYER; i++)
		layers << new MeshLayer(scene(), palette, i, this);
	
	activateLayer(LayerType::MIDGROUND);
	
	for (MeshLayer * ml : layers)
	{
		connect(ml, SIGNAL(statusTextChanged(QString)),
				window, SLOT(setStatusText(QString)));
		connect(bgItem, SIGNAL(contextMenuOpened(const QPoint&, const QPointF&)),
				ml, SLOT(contextMenu(const QPoint&, const QPointF&)));
		connect(bgItem, SIGNAL(clicked()),
				ml, SLOT(backgroundClicked()));
	}
	
	scale(Constants::PIXELS_PER_METER, Constants::PIXELS_PER_METER);
	
	isDragging = false;
}

LevelView::~LevelView()
{
	
}

bool LevelView::fromCommonLevel(const Common::Level & l)
{
	const std::vector<Common::LevelLayer*> & lls = l.getLayers();
	
	for (int i = 0; i < (int)lls.size(); i++)
		layers[i]->fromCommonLevelLayer(*lls[i]);
	
	return true;
}

void LevelView::toCommonLevel(Common::Level & l) const
{
	//Śliskie - nie wiadomo kto ma usunąć warstwy
	l.clear();
	
	std::vector<Common::LevelLayer*> lls;
	
	for (int i = 0; i < layers.size(); i++)
	{
		lls.push_back(new Common::LevelLayer());
		layers[i]->toCommonLevelLayer(*lls[i]);
	}
	
	l.setLayers(lls);
}

void LevelView::activateLayer(LayerType id)
{
	if ((int)id < 0 || (int)id >= layers.size())
		return;
	
	for (MeshLayer * ml : layers)
		ml->setActivated(false);
	
	layers[(int)id]->setActivated(true);
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
		QPointF delta =
			QPointF(event->pos() - oldMousePos) * Constants::METERS_PER_PIXEL;
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

const char * Zk::LevelEditor::layerTypeToName(LayerType lt)
{
	switch (lt)
	{
	case LayerType::MEDKIT_SPAWN:	return "Medkit spawn";
	case LayerType::GRENADES_SPAWN:	return "Grenades spawn";
	case LayerType::PLAYER_A_SPAWN:	return "Player A spawn";
	case LayerType::PLAYER_B_SPAWN:	return "Player B spawn";
	case LayerType::PLAYER_A_FLAG:	return "Player A flag spawn";
	case LayerType::PLAYER_B_FLAG:	return "Player B flag spawn";
	case LayerType::FOREGROUND:		return "Foreground";
	case LayerType::MIDGROUND:		return "Midground (collidable)";
	case LayerType::BACKGROUND:		return "Background";
	default:						return "???";
	}
}
