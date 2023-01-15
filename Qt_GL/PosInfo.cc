#include "PosInfo.h"
#include <QKeyEvent>
#include <QTimerEvent>
#include <QMatrix4x4>

void PosInfo::initializeGL() {
	view.init();
	// startTimer(20); **** deleted
}

void PosInfo::resizeGL(int width, int height) {
	glViewport(0, 0, width, height);
	QMatrix4x4 matrix;
	matrix.perspective(70.0, qreal(width) / qreal(height ? height : 1.0), 1e-3, 1e5);
	view.setProjection(matrix);
}


// **** added function
void PosInfo::updateData(Vector3 const& vec) {
	v = vec;
	updateGL();
}

void PosInfo::paintGL() {
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	switch (axisType) {
		case Z :
			view.drawZ(v); // *** added
			// view.drawZ(sys->getFrisbeePosition()); // *** deleted
			// view.drawZ(vs->getFrisbeePosition());
			break;
		case XY :
			view.drawXY(v); // *** added
			// view.drawXY(sys->getFrisbeePosition()); // *** deleted
			// view.drawXY(vs->getFrisbeePosition());
			break;
	}
}

// **** deleted fct
// void PosInfo::timerEvent(QTimerEvent* event) {
// 	Q_UNUSED(event);
// 	updateGL();
// }


