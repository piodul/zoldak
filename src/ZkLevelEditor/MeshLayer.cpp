#include "../ZkCommon/Level.h"

#include "MeshLayer.h"
#include "MeshTriangle.h"
#include "MeshTriangleNode.h"
#include "MeshTriangleEdge.h"
#include "ColorPaletteWidget.h"
#include "EditState.h"

#include <SFML/Graphics.hpp>

#include <QtCore>
#include <QtGui>
#include <QDebug>

#include <algorithm>

using namespace Zk::LevelEditor;

MeshLayer::MeshLayer(
	QGraphicsScene * scene,
	ColorPaletteWidget * palette,
	QObject * parent
)
	: QObject(parent), scene(scene), palette(palette)
{
	// MeshTriangleNode * na = createNode(QPoint(0, 0));
	// MeshTriangleNode * nb = createNode(QPoint(0, 200));
	// MeshTriangleNode * nc = createNode(QPoint(200, 0));
	
	// MeshTriangleEdge * ea = createEdge({ na, nb });
	// MeshTriangleEdge * eb = createEdge({ nb, nc });
	// MeshTriangleEdge * ec = createEdge({ nc, na });
	
	// createTriangle({ na, nb, nc }, { ea, eb, ec });

	// na->setColor(QColor(255, 0, 0));
	// nb->setColor(QColor(0, 255, 0));
	// nc->setColor(QColor(0, 0, 255));
	
	createFullTriangle(QPointF(0.0, 0.0));
	
	editState = EditState::IDLE;
}

MeshLayer::~MeshLayer()
{
	
}

void MeshLayer::setActivated(bool activated)
{
	//TODO: Zaimplementować mechanizm włączania/wyłączania warstw
	isActive = true;
}

void MeshLayer::clear()
{
	for (MeshTriangle * mt : triangles)
		delete mt;
	triangles.clear();
	
	//Węzłów i krawędzi nie trzeba usuwać, gdyż robią to za nas
	//trójkąty w destruktorze
	nodes.clear();
	edges.clear();
	
	for (MeshTriangleNode* & n : nodesToConnect)
		n = nullptr;
	editState = EditState::IDLE;
}

bool MeshLayer::fromCommonLevelLayer(const Common::LevelLayer & ll)
{
	clear();
	
	const std::vector<sf::Vertex> & vs = ll.getVertices();
	for (const sf::Vertex & v : vs)
		createNode(QPoint(v.position.x, v.position.y));
	
	const std::vector<Common::triangleDesc_t> & tds = ll.getTriangleDescriptions();
	for (const Common::triangleDesc_t & td : tds)
		formTriangle(
			{
				nodes[td.vert[0]],
				nodes[td.vert[1]],
				nodes[td.vert[2]]
			}
		);
	
	return true;
}

void MeshLayer::toCommonLevelLayer(Common::LevelLayer & ll) const
{
	std::vector<sf::Vertex> vs;
	vs.reserve(nodes.size());
	
	ll.clear();
	for (MeshTriangleNode * mtn : nodes)
	{
		QPointF pos = mtn->pos();
		sf::Vector2f v(pos.x(), pos.y());
		vs.push_back(sf::Vertex(v));
	}
	
	ll.setVertices(vs);
	
	QHash<MeshTriangleNode*, qint16> nodeIndexes;
	qint16 id = 0;
	for (MeshTriangleNode * mtn : nodes)
		nodeIndexes.insert(mtn, id++);
	
	std::vector<Common::triangleDesc_t> tds;
	tds.reserve(triangles.size());
	for (MeshTriangle * mt : triangles)
	{
		const std::array<MeshTriangleNode*, 3> & mtns = mt->getLinkedNodes();
		tds.push_back(
			{
				nodeIndexes[mtns[0]],
				nodeIndexes[mtns[1]],
				nodeIndexes[mtns[2]]
			}
		);
	}
	
	ll.setTriangleDescriptions(tds);
}

EditState MeshLayer::getState() const
{
	return editState;
}

QColor MeshLayer::getSelectedColor() const
{
	return palette->getSelectedColor();
}

void MeshLayer::setState(EditState es)
{
	//Sprzątanie dla poprzedniego stanu
	switch (editState)
	{
	case EditState::IDLE:
	case EditState::TRIANGLE_PAINTING:
		break;
		
	case EditState::MAKE_TRIANGLE_SELECTED_1:
	case EditState::MAKE_TRIANGLE_SELECTED_2:
		for (auto & n : nodesToConnect)
			n = nullptr;
		break;
	}
	
	editState = es;
	switch (es)
	{
	case EditState::IDLE:
	case EditState::TRIANGLE_PAINTING:
		break;
		
	case EditState::MAKE_TRIANGLE_SELECTED_1:
	case EditState::MAKE_TRIANGLE_SELECTED_2:
		qDebug() << "WARNING: Attempted to set an invalid state!";
		editState = EditState::IDLE;
		break;
	}
}

void MeshLayer::triangleNodeClicked(MeshTriangleNode * mtn, const QGraphicsSceneMouseEvent * event)
{
	qDebug() << "MTN clicked";
	
	if ((event->modifiers() & Qt::AltModifier) && !mtn->isMarked())
	{
		switch (editState)
		{
		case EditState::IDLE:
			nodesToConnect[0] = mtn;
			mtn->setMarked(true);
			editState = EditState::MAKE_TRIANGLE_SELECTED_1;
			break;
			
		case EditState::MAKE_TRIANGLE_SELECTED_1:
			nodesToConnect[1] = mtn;
			mtn->setMarked(true);
			editState = EditState::MAKE_TRIANGLE_SELECTED_2;
			break;
			
		case EditState::MAKE_TRIANGLE_SELECTED_2:
			nodesToConnect[2] = mtn;
			formTriangle(nodesToConnect);
			nodesToConnect[0]->setMarked(false);
			nodesToConnect[1]->setMarked(false);
			
			for (auto & n : nodesToConnect)
				n = nullptr;
			
			editState = EditState::IDLE;
			break;
			
		default:
			break;
		}
	}
}

void MeshLayer::triangleEdgeClicked(MeshTriangleEdge * mte, const QGraphicsSceneMouseEvent * event)
{
	qDebug() << "MTE clicked";
	
	if (!mte->canExtrude())
		return;
	
	std::array<MeshTriangleNode*, 2> ends = mte->getEnds();
	
	//Create triangle "protruding" form the edge
	// MeshTriangleNode * mtn = new MeshTriangleNode(this);
	// mtn->setPos(event->pos());
	MeshTriangleNode * mtn = createNode(event->pos());
	MeshTriangleEdge * ea = createEdge({ mtn, ends[0] });
	MeshTriangleEdge * eb = createEdge({ mtn, ends[1] });
	createTriangle(
		{ mtn, ends[0], ends[1] },
		{ mte, ea, eb }
	);
}

void MeshLayer::triangleDestroyed(MeshTriangle * mt)
{
	qDebug() << "MT destroyed";
	triangles.removeOne(mt);
}

void MeshLayer::nodeUnlinked(MeshTriangleNode * mtn)
{
	qDebug() << "MTN unlinked, destroying";
	nodes.removeOne(mtn);
	delete mtn;
}

void MeshLayer::edgeUnlinked(MeshTriangleEdge * mte)
{
	qDebug() << "MTE unlinked, destroying";
	edges.removeOne(mte);
	delete mte;
}

void MeshLayer::backgroundClicked()
{
	switch (editState)
	{
	case EditState::MAKE_TRIANGLE_SELECTED_2:
		nodesToConnect[1]->setMarked(false);
	case EditState::MAKE_TRIANGLE_SELECTED_1:
		nodesToConnect[0]->setMarked(false);
		editState = EditState::IDLE;
		break;
		
	default:
		break;
	}
	
	for (int i : { 0, 1, 2 })
		nodesToConnect[i] = nullptr;
}

void MeshLayer::contextMenu(const QPoint & pos, const QPointF & scenePos)
{
	QMenu menu;
	qDebug() << "DUPA";
	QAction * createTriangleAction = menu.addAction("&New triangle");
	QAction * choice = menu.exec(pos);
	
	if (choice == createTriangleAction)
		createFullTriangle(scenePos);
}

MeshTriangleNode * MeshLayer::createNode(const QPointF & pos)
{
	MeshTriangleNode * mtn = new MeshTriangleNode(this);
	mtn->setPos(pos);
	
	connect(mtn, SIGNAL(clicked(MeshTriangleNode*, const QGraphicsSceneMouseEvent*)),
		this, SLOT(triangleNodeClicked(MeshTriangleNode*, const QGraphicsSceneMouseEvent*)));
	
	connect(mtn, SIGNAL(unlinked(MeshTriangleNode*)),
		this, SLOT(nodeUnlinked(MeshTriangleNode*)));
	
	nodes << mtn;
	scene->addItem(mtn);
	return mtn;
}

MeshTriangle * MeshLayer::createTriangle(
	std::array<MeshTriangleNode*, 3> verts,
	std::array<MeshTriangleEdge*, 3> edges
)
{
	MeshTriangle * mt = new MeshTriangle(this, verts, edges);
	mt->setColors({ getSelectedColor(), getSelectedColor(), getSelectedColor() });
	
	connect(mt, SIGNAL(destroyed(MeshTriangle*)),
		this, SLOT(triangleDestroyed(MeshTriangle*)));
	
	triangles << mt;
	scene->addItem(mt);
	return mt;
}

MeshTriangleEdge * MeshLayer::createEdge(std::array<MeshTriangleNode*, 2> ends)
{
	MeshTriangleEdge * mte = new MeshTriangleEdge(this, ends);
	
	connect(mte, SIGNAL(clicked(MeshTriangleEdge*, const QGraphicsSceneMouseEvent*)),
		this, SLOT(triangleEdgeClicked(MeshTriangleEdge*, const QGraphicsSceneMouseEvent*)));
	
	connect(mte, SIGNAL(unlinked(MeshTriangleEdge*)),
		this, SLOT(edgeUnlinked(MeshTriangleEdge*)));
	
	edges << mte;
	scene->addItem(mte);
	return mte;
}

MeshTriangle * MeshLayer::formTriangle(std::array<MeshTriangleNode*, 3> verts)
{
	//TODO: Może dodać jakieś struktury pozwalające
	//na szybsze szukanie takich rzeczy?
	
	//Sprawdzamy czy wierzchołki nie tworzą już trójkąta
	const QList<MeshTriangle*> & tris = verts[0]->getLinkedTriangles();
	
	for (MeshTriangle * tri : tris)
	{
		const std::array<MeshTriangleNode*, 3> & triverts = tri->getLinkedNodes();
		int numOK = 1;
		for (MeshTriangleNode * vert : { verts[1], verts[2] })
		{
			if (std::find(triverts.begin(), triverts.end(), vert) != triverts.end())
				numOK++;
		}
		
		if (numOK == 3)
			return nullptr;	//Trójkąt o podanych wierzchołkach już istnieje
	}
	
	//Sprawdzamy czy są jakieś połączenia pomiędzy vertexami
	std::array<MeshTriangleEdge*, 3> triedges;
	int id = 0;
	
	std::initializer_list<std::array<MeshTriangleNode*, 2>> pairs {
		{ verts[0], verts[1] },
		{ verts[0], verts[2] },
		{ verts[1], verts[2] }
	};
	
	for (const auto & pair : pairs)
	{
		const QList<MeshTriangleEdge*> & edges = pair[0]->getLinkedEdges();
		MeshTriangleEdge * datEdge = nullptr;
		for (MeshTriangleEdge * edge : edges)
		{
			const std::array<MeshTriangleNode*, 2> ends = edge->getEnds();
			if (ends[0] == pair[1] || ends[1] == pair[1])
			{
				datEdge = edge;
				break;
			}
		}
		
		if (datEdge)
			triedges[id] = datEdge;
		else
			triedges[id] = createEdge(pair);
		
		id++;
	}
	
	return createTriangle(verts, triedges);
}

MeshTriangle * MeshLayer::createFullTriangle(const QPointF & pos)
{
	QPointF offPos(0.0, 128.0);
	QTransform transform = QTransform().rotate(120.0);
	
	MeshTriangleNode * na = createNode(pos + offPos);
	offPos = transform.map(offPos);
	MeshTriangleNode * nb = createNode(pos + offPos);
	offPos = transform.map(offPos);
	MeshTriangleNode * nc = createNode(pos + offPos);
	
	MeshTriangleEdge * ea = createEdge({ na, nb });
	MeshTriangleEdge * eb = createEdge({ nb, nc });
	MeshTriangleEdge * ec = createEdge({ nc, na });
	
	return createTriangle({ na, nb, nc }, { ea, eb, ec });
}
