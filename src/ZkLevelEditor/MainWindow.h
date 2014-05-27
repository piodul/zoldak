#pragma once

#include <QtWidgets>

#include "ColorPaletteWidget.h"

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

private:
	LevelView * levelView;
	ColorPaletteWidget * paletteWidget;
	
	QLabel * statusLabel;
};

}}
