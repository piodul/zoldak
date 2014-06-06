#pragma once

#include <QtWidgets>

namespace Zk {
namespace Game {

class PlayTab : public QWidget
{
	Q_OBJECT;
	
public:
	PlayTab(QWidget * parent = nullptr);
	virtual ~PlayTab();
	
private:
	QListView * levelListView;
	QStringListModel * levelListModel;
	
	QPushButton * startGameButton;
};

}}
