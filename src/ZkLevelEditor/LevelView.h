#pragma once

#include <QtWidgets>
#include <array>

namespace Zk {
namespace LevelEditor {

class MeshTriangleNode;
class MeshTriangle;
class MeshTriangleEdge;
class MeshLayer;

class LevelView : public QGraphicsView
{
	Q_OBJECT;
	
public:
	LevelView(QWidget * parent = nullptr);
	virtual ~LevelView();
	
private:
	MeshLayer * mainLayer;
	
};

}}
