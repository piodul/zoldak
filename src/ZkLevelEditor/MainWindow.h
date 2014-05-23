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
	
public slots:
	void setStatusText(QString text);
	
	void loadLevel();
	void saveLevel();

private:
	LevelView * levelView;
	
	QPushButton * exitButton;
	QLabel * statusLabel;
};

}}
