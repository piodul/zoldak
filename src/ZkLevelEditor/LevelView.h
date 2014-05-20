#pragma once

#include <QtWidgets>
#include <array>

namespace Zk {
namespace LevelEditor {

class MainWindow;

class MeshTriangleNode;
class MeshTriangle;
class MeshTriangleEdge;
class MeshLayer;

class BackgroundItem;

class LevelView : public QGraphicsView
{
	Q_OBJECT;
	
public:
	LevelView(MainWindow * mw, QWidget * parent = nullptr);
	virtual ~LevelView();
	
private slots:
	void contextMenu(const QPoint & pos);
	
protected:
	virtual void mousePressEvent(QMouseEvent * event) override;
	virtual void mouseMoveEvent(QMouseEvent * event) override;
	virtual void mouseReleaseEvent(QMouseEvent * event) override;
	virtual void resizeEvent(QResizeEvent * event) override;
	
private:
	MainWindow * window;
	MeshLayer * mainLayer;
	BackgroundItem * bgItem;
	
	bool isDragging;
	QPoint oldMousePos;
};

}}
