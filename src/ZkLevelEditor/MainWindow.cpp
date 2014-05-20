#include "MainWindow.h"
#include "LevelView.h"

#include <QtCore>
#include <QtGui>

using namespace Zk::LevelEditor;

MainWindow::MainWindow(QWidget * parent)
	: QMainWindow(parent)
{
	LevelView * levelView = new LevelView(this);
	
	exitButton = new QPushButton("&Exit");
	
	QHBoxLayout * mainLayout = new QHBoxLayout();
	mainLayout->addWidget(levelView);
	mainLayout->addWidget(exitButton);
	
	QWidget * centralWidget = new QWidget();
	centralWidget->setLayout(mainLayout);
	
	setCentralWidget(centralWidget);
	
	setStatusBar(new QStatusBar());
	statusLabel = new QLabel();
	statusBar()->addWidget(statusLabel);
}

MainWindow::~MainWindow()
{
	
}

void MainWindow::setStatusText(QString text)
{
	statusLabel->setText(text);
}
