#include "../ZkCommon/Level.h"

#include "MainWindow.h"
#include "LevelView.h"

#include <QtCore>
#include <QtGui>
#include <QDebug>

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
	
	//--- Menu ---//
	QMenu * fileMenu = new QMenu("&File");
	QAction * loadAction = fileMenu->addAction("&Load level...");
	QAction * saveAction = fileMenu->addAction("&Save level...");
	menuBar()->addMenu(fileMenu);
	
	connect(loadAction, SIGNAL(triggered(bool)),
		this, SLOT(loadLevel()));
	connect(saveAction, SIGNAL(triggered(bool)),
		this, SLOT(saveLevel()));
}

MainWindow::~MainWindow()
{
	
}

void MainWindow::setStatusText(QString text)
{
	statusLabel->setText(text);
}

void MainWindow::loadLevel()
{
	QString path = QFileDialog::getOpenFileName(
		this,
		"Open level",
		QString(),
		"Zoldak level files (*.zvl)"
	);
	
	if (path.isNull())
		return;
	
	QFile f(path);
	if (!f.open(QIODevice::ReadOnly))
	{
		qDebug() << "Failed to open file for reading:" << path;
		return;
	}
	
	QDataStream ds(&f);
	
	Common::Level l;
	ds >> l;
	levelView->fromCommonLevel(l);
}

void MainWindow::saveLevel()
{
	QString path = QFileDialog::getSaveFileName(
		this,
		"Save level",
		QString(),
		"Zoldak level files (*.zvl)"
	);
	
	if (path.isNull())
		return;
	
	QFile f(path);
	if (!f.open(QIODevice::WriteOnly))
	{
		qDebug() << "Failed to open file for writing:" << path;
		return;
	}
		
	QDataStream ds(&f);
	
	Common::Level l;
	levelView->toCommonLevel(l);
	ds << l;
}
