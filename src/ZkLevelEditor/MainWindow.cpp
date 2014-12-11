#include "../ZkCommon/Constants.hpp"
#include "../ZkCommon/Level.hpp"

#include "MainWindow.hpp"
#include "LevelView.hpp"
#include "ColorPaletteWidget.hpp"

#include <QtCore>
#include <QtGui>
#include <QDebug>

using namespace Zk::Common;
using namespace Zk::LevelEditor;

MainWindow::MainWindow(QWidget * parent)
	: QMainWindow(parent)
{
	paletteWidget = new ColorPaletteWidget(4);
	layerList = new QListWidget();
	levelView = new LevelView(this, paletteWidget, layerList);

	QSizePolicy layerListSizePolicy(
		QSizePolicy::Maximum,
		QSizePolicy::Preferred
	);
	layerList->setSizePolicy(layerListSizePolicy);

	connect(layerList, SIGNAL(currentRowChanged(int)),
			this, SLOT(changeActiveLayer(int)));

	QVBoxLayout * rightLayout = new QVBoxLayout();
	rightLayout->addWidget(paletteWidget, 0, Qt::AlignCenter);
	rightLayout->addWidget(layerList);
	rightLayout->addStretch();

	QHBoxLayout * mainLayout = new QHBoxLayout();
	mainLayout->addWidget(levelView);
	mainLayout->addLayout(rightLayout);

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

	Level l;
	ds >> l;
	levelView->fromCommonLevel(l);
	paletteWidget->fromColorList(l.getPalette());
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

	Level l = levelView->toCommonLevel();

	l.setPalette(paletteWidget->toColorList());

	ds << l;
}

void MainWindow::changeActiveLayer(int id)
{
	levelView->activateLayer((LayerType)id);
}
