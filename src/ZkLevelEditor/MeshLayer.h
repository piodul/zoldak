#pragma once

#include <QtWidgets>
#include <array>

namespace Zk {
namespace LevelEditor {

//TODO: Doxygen

class MeshLayer : public QObject
{
	Q_OBJECT;
	
public:
	MeshLayer(QObject * parent = nullptr);
	virtual ~MeshLayer();
	
	//Ustawia czy daną warstwę można edytować
	//i odpowiednio zmienia jej wygląd
	void setActivated(bool activated);
	
private slots:
	
	
private:
	
	
};

}}
