#pragma once

#include <QtWidgets>

namespace Zk {
namespace LevelEditor {

class ColorBox : public QWidget
{
public:
	ColorBox(QWidget * parent = nullptr);
	virtual ~ColorBox();
	
	void setColor(QColor color);
	QColor getColor() const;
	
	virtual QSize sizeHint() const override;
	
signals:
	//void selected(ColorBox * me);
	
protected:
	virtual void paintEvent(QPaintEvent * event) override;
	virtual void mousePressEvent(QMouseEvent * event) override;
	
private:
	QColor color;
	
};

}}
