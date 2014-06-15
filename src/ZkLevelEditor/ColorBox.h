#pragma once

#include <QtWidgets>

namespace Zk {
namespace LevelEditor {

class ColorBox : public QWidget
{
	Q_OBJECT;

public:
	ColorBox(QWidget * parent = nullptr);
	virtual ~ColorBox();

	void select();

	void setColor(QColor color);
	QColor getColor() const;

	virtual QSize sizeHint() const override;

public slots:
	void deselect();

signals:
	void colorSelected(QColor color);

protected:
	virtual void paintEvent(QPaintEvent * event) override;
	virtual void mousePressEvent(QMouseEvent * event) override;

private:
	QColor color;
	bool selected;

};

}}
