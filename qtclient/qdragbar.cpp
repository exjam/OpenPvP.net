#include "mainwindow.h"
#include "qdragbar.h"

QDragBar::QDragBar(QWidget* parent)
	: QWidget(parent)
{
}
	
void QDragBar::mousePressEvent(QMouseEvent* e){
	if(e->button() == Qt::LeftButton){
		mDragStart = e->globalPos() - gMainWindow->frameGeometry().topLeft();
		e->accept();
	}
}
 
void QDragBar::mouseMoveEvent(QMouseEvent* e){
	if(e->buttons() & Qt::LeftButton){
		QPoint dp = e->globalPos() - mDragStart;
		gMainWindow->move(dp);
	}
}
