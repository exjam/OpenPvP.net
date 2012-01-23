#ifndef DRAGBAR_H
#define DRAGBAR_H

#include <QWidget>
#include <QMouseEvent>

class QDragBar : public QWidget {
public:
	QDragBar(QWidget* parent = 0);

	virtual void mousePressEvent(QMouseEvent* e);
	virtual void mouseMoveEvent(QMouseEvent* e);

private:
	QPoint mDragStart;
};

#endif
