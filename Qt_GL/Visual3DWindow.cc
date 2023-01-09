#include <vector>
#include <QKeyEvent>
#include <QTimerEvent>
#include <QMatrix4x4>
#include "Visual3DWindow.h"
// #include "InfoWindow.h"

using namespace std;


// Visual3DWindow::Visual3DWindow(IntegratorType type, QWidget* parent)
Visual3DWindow::Visual3DWindow(VisualSimulation* parent)
	: QGLWidget(parent), parent(parent) { // Dynamically allocated because we may want to change the System.

	// keyActionMap[Qt::Key_Up] = pitchUp;
	// keyActionMap[Qt::Key_Down] = pitchDown;
	// keyActionMap[Qt::Key_Left] = yawLeft;
	// keyActionMap[Qt::Key_Right] = yawRight;
	// keyActionMap[Qt::Key_A] = rollLeft;
	// keyActionMap[Qt::Key_E] = rollRight;
	// keyActionMap[Qt::Key_R] = moveUp;
	// keyActionMap[Qt::Key_F] = moveDown;
	// keyActionMap[Qt::Key_Q] = moveLeft;
	// keyActionMap[Qt::Key_D] = moveRight;
	// keyActionMap[Qt::Key_Z] = moveForward;
	// keyActionMap[Qt::Key_S] = moveBackward;
	// keyActionMap[Qt::Key_Home] = resetPosition;
	// keyActionMap[Qt::Key_Space] = startStopTime;
}

Visual3DWindow::~Visual3DWindow() {
	cerr << "Visual3DWindow::~Visual3DWindow()" << endl;
}


void Visual3DWindow::lookAt(System* s) {
	view.lookAt(s);
	// *** add updateGL(); ?
}

	
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
	// parent->stop(); // *** added this
	// timerId = 0; // So that time is paused after a reinitialization.
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
	constexpr double smallAngle(5.0); // In degrees.
	constexpr double smallStep(1.0);

	KeyAction action;


	// map<int, KeyAction>::iterator it = keyActionMap.find(event->key()); // Find the action correesponding to this key press; 
	// // map<Qt::Key, KeyAction>::iterator it = keyActionMap.find(event->key()); // Find the action correesponding to this key press; 

	// if (it != keyActionMap.end()) { 
		
	// 	action = it->second;

	if (parent->getMappedAction(event, action)) {
		if (action==pitchUp) {
			view.rotate(smallAngle, Vector3(-1.0, 0.0, 0.0));	
		} else if (action==pitchDown) {
			view.rotate(smallAngle, Vector3(+1.0, 0.0, 0.0));
		} else if (action==yawLeft) {
			view.rotate(smallAngle, Vector3(0.0, -1.0, 0.0));	
		} else if (action==yawRight) {
			view.rotate(smallAngle, Vector3(0.0, +1.0, 0.0));
		} else if (action==rollLeft) {
			view.rotate(smallAngle, Vector3(0.0, 0.0, -1.0));
		} else if (action==rollRight) {
			view.rotate(smallAngle, Vector3(0.0, 0.0, +1.0));
		} else if (action==moveUp) {
			view.translate(Vector3(0.0, -smallStep, 0.0));
		} else if (action==moveDown) {
			view.translate(Vector3(0.0,  smallStep, 0.0));
		} else if (action==moveLeft) {
			view.translate( Vector3(smallStep, 0.0, 0.0));
		} else if (action==moveRight) {
			view.translate(Vector3(-smallStep, 0.0, 0.0));
		} else if (action==moveForward) {
			view.translate(Vector3(0.0, 0.0,  smallStep));	
		} else if (action==moveBackward) {
			view.translate(Vector3(0.0, 0.0, -smallStep));
		} else if (action==resetPosition) {
			view.initializePosition();
		} else if (action==startStopTime) {
			parent->toggleTime();
		} else {
			throw string("Visual3DWindow::keyPressEvent(...)  unknown action");
		}
	}
	updateGL(); // put this line inside the if brackets ?
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


