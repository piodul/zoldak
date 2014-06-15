#pragma once

#include <QtWidgets>
#include <array>

#include "../ZkCommon/Constants.h"
#include "../ZkCommon/Level.h"

namespace Zk {
namespace LevelEditor {

class MainWindow;

class MeshTriangleNode;
class MeshTriangle;
class MeshTriangleEdge;
class MeshLayer;

class ColorPaletteWidget;

class BackgroundItem;

class LevelView : public QGraphicsView
{
	Q_OBJECT;

public:
	LevelView(
		MainWindow * mw,
		ColorPaletteWidget * palette,
		QWidget * parent = nullptr
	);
	virtual ~LevelView();

	bool fromCommonLevel(const Common::Level & l);
	void toCommonLevel(Common::Level & l) const;

	void activateLayer(Common::LayerType id);

protected:
	virtual void mousePressEvent(QMouseEvent * event) override;
	virtual void mouseMoveEvent(QMouseEvent * event) override;
	virtual void mouseReleaseEvent(QMouseEvent * event) override;
	virtual void resizeEvent(QResizeEvent * event) override;

private:
	MainWindow * window;
	QList<MeshLayer*> layers;
	BackgroundItem * bgItem;

	bool isDragging;
	QPoint oldMousePos;
};

const char * layerTypeToName(Common::LayerType lt);

}}
