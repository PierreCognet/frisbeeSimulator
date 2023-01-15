#include <vector>
#include <QKeyEvent>
#include <QTimerEvent>
#include <QMatrix4x4>
#include "Visual3DWindow.h"
// #include "InfoWindow.h"

using namespace std;


// Visual3DWindow::Visual3DWindow(IntegratorType type, QWidget* parent)
// Visual3DWindow::Visual3DWindow(VisualSimulation* parent)
// 	: QGLWidget(parent), parent(parent) { // Dynamically allocated because we may want to change the System.
Visual3DWindow::Visual3DWindow(KeyActionWindow* parent) : QGLWidget(parent), parent(parent) { }


Visual3DWindow::~Visual3DWindow() {
	cerr << "Visual3DWindow::~Visual3DWindow()" << endl;
}


void Visual3DWindow::lookAt(System* s) {
	view.lookAt(s);
	// *** add updateGL(); ?
}

// void Visual3DWindow::rotate(double const& angle, Vector3 const& v) {
// 	view.rotate(angle, v);	
// }

// void Visual3DWindow::translate(Vector3 const& v) {
// 	view.translate(v);	
// }
	
void Visual3DWindow::setcamX() {
	view.setPOV("Xplus");
	updateGL();
}

void Visual3DWindow::setcamXX() {
	view.setPOV("Xminus");
	updateGL();
}

void Visual3DWindow::setcamY() {
	view.setPOV("Yplus");
	updateGL();
}

void Visual3DWindow::setcamYY() {
	view.setPOV("Yminus");
	updateGL();
}

void Visual3DWindow::setcamZ() {
	view.setPOV("Zplus");
	updateGL();
}

void Visual3DWindow::setcamZZ() {
	view.setPOV("Zminus");
	updateGL();
}



void Visual3DWindow::initializeGL() {
	view.init();
	parent->stop(); // *** added this
}

void Visual3DWindow::resizeGL(int width, int height) {
	glViewport(0, 0, width, height);
	QMatrix4x4 matrice;
	matrice.perspective(70.0, qreal(width) / qreal(height ? height : 1.0), 1e-3, 1e5);
	view.setProjection(matrice);
}

void Visual3DWindow::paintGL() {
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	parent->getSystem()->draw();
}

void Visual3DWindow::keyPressEvent(QKeyEvent* event) {
	parent->visual3DWindowKeyPressEvent(event);
}





void Visual3DWindow::mousePressEvent(QMouseEvent* event) {
	lastMousePosition = event->pos();
}

void Visual3DWindow::mouseMoveEvent(QMouseEvent* event) {
	/* If mouse tracking is disabled (the default), the widget only receives
	 * mouse move events when at least one mouse button is pressed while the
	 * mouse is being moved.
	 *
	 * Pour activer le "mouse tracking" if faut lancer setMouseTracking(true)
	 * par exemple dans le constructeur de cette classe.
	 */

	if (event->buttons() & Qt::LeftButton) {
		constexpr double smallAngle(.4); // In degrees.

		// Gets the movement relative to the last mouse position.
		QPointF d = event->pos() - lastMousePosition;
		lastMousePosition = event->pos();

		view.rotate(smallAngle * d.manhattanLength(), Vector3(d.y(), d.x(), 0) );

		update();
	}
}

void Visual3DWindow::closeEvent(QCloseEvent* event) {
	cerr << "Visual3DWindow::closeEvent(QCloseEvent* event)" << endl;
	parent->close();
	event->accept();
}


