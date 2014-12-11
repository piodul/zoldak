#pragma once

#include <QtWidgets>

#include "ColorPaletteWidget.hpp"

namespace Zk {
namespace LevelEditor {

class LevelView;

class MainWindow : public QMainWindow
{
	Q_OBJECT;

public:
	MainWindow(QWidget * parent = nullptr);
	virtual ~MainWindow();

private slots:
	void setStatusText(QString text);

	void loadLevel();
	void saveLevel();

	void changeActiveLayer(int id);

private:
	LevelView * levelView;
	ColorPaletteWidget * paletteWidget;
	QListWidget * layerList;

	QLabel * statusLabel;
};

}}
