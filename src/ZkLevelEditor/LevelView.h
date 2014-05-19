#pragma once

#include <QtWidgets>
#include <array>

namespace Zk {
namespace LevelEditor {

class MeshTriangleNode;
class MeshTriangle;
class MeshTriangleEdge;
class MeshLayer;

class BackgroundItem;

class LevelView : public QGraphicsView
{
	Q_OBJECT;
	
public:
	LevelView(QWidget * parent = nullptr);
	virtual ~LevelView();
	
private slots:
	void contextMenu(const QPoint & pos);
	
protected:
	virtual void mousePressEvent(QMouseEvent * event) override;
	virtual void mouseMoveEvent(QMouseEvent * event) override;
	virtual void mouseReleaseEvent(QMouseEvent * event) override;
	virtual void resizeEvent(QResizeEvent * event) override;
	
private:
	MeshLayer * mainLayer;
	BackgroundItem * bgItem;
	
	bool isDragging;
	QPoint oldMousePos;
};

}}
