#pragma once

#include <QtWidgets>

namespace Zk {
namespace LevelEditor {

class LevelView;

class MainWindow : public QMainWindow
{
	Q_OBJECT;
	
public:
	MainWindow(QWidget * parent = nullptr);
	virtual ~MainWindow();

private:
	LevelView * levelView;
	
	QPushButton * exitButton;
};

}}
