#include "PosInfo.h"
#include <QKeyEvent>
#include <QTimerEvent>
#include <QMatrix4x4>
#include "GLWidget.h"

void PosInfo::initializeGL() {
	view.init();
	startTimer(20);
}

void PosInfo::resizeGL(int width, int height) {
	glViewport(0, 0, width, height);
	QMatrix4x4 matrix;
	matrix.perspective(70.0, qreal(width) / qreal(height ? height : 1.0), 1e-3, 1e5);
	view.setProjection(matrix);
}

void PosInfo::timerEvent(QTimerEvent* event) {
	Q_UNUSED(event);
	updateGL();
}


void PosInfo::paintGL() {
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	switch (axisType) {
		case Z :
			view.drawZ(GetInfo->getFrisbeePosition());
			break;
		case XY :
			view.drawXY(GetInfo->getFrisbeePosition());
			break;
	}
}


