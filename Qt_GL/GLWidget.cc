#include <vector>
#include <QKeyEvent>
#include <QTimerEvent>
#include <QMatrix4x4>
#include "GLWidget.h"
#include <fstream>
// #include "IntegratorEuler.h"
// #include "IntegratorNewmark.h"
#include "IntegratorRK4.h"
// #include "InfoWindow.h"

using namespace std;


// GLWidget::GLWidget(IntegratorType type, QWidget* parent)
GLWidget::GLWidget(IntegratorType type, CommandWindow* parent)
	: QGLWidget(parent), s(new System(&view)), playbackSpeed(50), parent(parent) { // Dynamically allocated because we may want to change the System.
	switch (type) {
		// case Euler:
		// 	integrator =  new IntegrateurEuler;
		// 	break;
		// case Newmark:
		// 	integrator = new IntegrateurNewmark;
		// 	break;
		case RungeKutta:
			integrator = new IntegratorRK4;
			break;
	}

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

GLWidget::~GLWidget() { 
	delete integrator;
	delete s;
}




//------------------------Enregistrer le système------------------------
// void GLWidget::sauvegarderFichier(std::string const& nomFichierSANSLExtension) const{
	
// 	ofstream sortie( nomFichierSANSLExtension + ".dat" );	//ouverture du flot
// 	if (sortie.fail()) {
// 		throw string("GLWidget::enregistreFichier(...)  impossible d'ouvrir '"+nomFichierSANSLExtension+".dat' en ecriture");
// 	}
	
// 	s->sauvegarderFichier(sortie);
	
// 	sortie.close();


// }

// void GLWidget::chargerFichier(std::string const& nomFichierSANSLExtension){
	
// 	ifstream entree( nomFichierSANSLExtension + ".dat" );	//ouverture du flot
// 	if (entree.fail()) {
// 		throw string("GLWidget::chargerFichier(...)  impossible d'ouvrir '"+nomFichierSANSLExtension+".dat' en lecture");
// 	}
	
// 	Systeme* systTemp ( new Systeme (&view,entree) );	//creer un nouveau systeme (il pourrait y avoir des problèmes de format!)
// 	delete s;	//s'il s'est chargé correctement on supprime l'ancien
// 	s = systTemp;	//on garde le nouveau

// }
	
	
	
	

// void GLWidget::Toggle_Cassures(){
// 		s->toggle_ressortsCassable();
// }


// void GLWidget::Toggle_Contr(){
// 		view.toggle_Contr();
// 		updateGL();
// }

	
void GLWidget::setcamX() {
	view.setPOV("Xplus");
	updateGL();
}

void GLWidget::setcamXX() {
	view.setPOV("Xminus");
	updateGL();
}

void GLWidget::setcamY() {
	view.setPOV("Yplus");
	updateGL();
}

void GLWidget::setcamYY() {
	view.setPOV("Yminus");
	updateGL();
}

void GLWidget::setcamZ() {
	view.setPOV("Zplus");
	updateGL();
}

void GLWidget::setcamZZ() {
	view.setPOV("Zminus");
	updateGL();
}


// void GLWidget::toggle_tri (){view.toggle_tri();
															 // updateGL(); }

// void GLWidget::toggle_Mass(){view.toggle_mas();
//                                 updateGL();}

// void GLWidget::toggle_springs(){view.toggle_springs();
//                                  updateGL();}



// void GLWidget::set_Euler(){
//     if (integrator->get_type() != Euler) {
//         delete integrator;
//         integrator = new IntegrateurEuler;}
//     }

// void GLWidget::set_Newmark(){
//     if (integrator->get_type() != Newmark){
//         delete integrator;
//         integrator = new IntegrateurNewmark;}
//     }

void GLWidget::setRK4(){
	if (integrator->getType() != RungeKutta) {
		delete integrator;
		integrator = new IntegratorRK4;
	}
}



void GLWidget::toggleTime() {
	if (timerId == 0) { // In this case, the timer is not running, so start it.
		timerId = startTimer(20);
		chronometer.restart();
	} else { // The timer is running so stop it.
		killTimer(timerId);
		timerId = 0;
	}
}

void GLWidget::setPlaybackSpeed(int a){
	 playbackSpeed = a;
	 //cerr << playbackSpeed;
}

double GLWidget::getCurrentTime() {
		return s->time();
}

void GLWidget::resetTime() {
	s->resetTime();
}




void GLWidget::setFrisbeeState(Vector3 const& xyz, Vector3 const& phiThetaPsi, Vector3 const& uvw, Vector3 const& pqr, bool const& uvwIsBodyNotEarthAxes) {
	s->setFrisbeeState(xyz, phiThetaPsi, uvw, pqr, uvwIsBodyNotEarthAxes);
	stop();
	updateGL();
}

System* GLWidget::getSystem() {
	return s;
}


const Vector3 GLWidget::getFrisbeePosition() const {
	return s->getFrisbeePosition();
}


void GLWidget::saveCurrentState(std::string fileName) const{
	
	string extension (".state");
	size_t extSiz (extension.size());
	if (fileName.size()>=extSiz) {
		if (fileName.substr(fileName.size()-extSiz,extSiz)!=extension) {
			fileName += extension;
		}
	}

	ofstream output(fileName);	// Open flow.
	if (output.fail()) {
		throw string("GLWidget::saveCurrentState(...)  impossible to open '"+fileName+"' in write mode");
	}
	
	// s->saveCurrentState(output);
	output << s->getHeaders() << endl << s->getCurrentState();
	
	output.close();
}


void GLWidget::loadState(std::string const& fileName) {
	ifstream input(fileName);
	if (input.fail()) {
		throw string("GLWidget::loadState(...)  impossible to load '"+fileName+"' in read mode");
	}
	
	if (input.is_open()) {

		try {
			System* tmpSyst ( new System(&view, input) );	// Create new system. Note that this process can fail if there are format errors.
			delete s;	// If successfully loaded, delete and replace the old System.
			s = tmpSyst;	//on garde le nouveau
		} catch (std::string s) {
		    QMessageBox::information(this, "Exception caught", QString::fromStdString(s));
		} catch (const std::exception& e) {
		    QMessageBox::information(this, "Exception caught", QString::fromStdString(e.what()));
		}

		input.close();
	}
}





void GLWidget::initializeGL() {
	view.init();
	timerId = 0; // So that time is paused after a reinitialization.
}

void GLWidget::resizeGL(int width, int height) {
	glViewport(0, 0, width, height);
	QMatrix4x4 matrice;
	matrice.perspective(70.0, qreal(width) / qreal(height ? height : 1.0), 1e-3, 1e5);
	view.setProjection(matrice);
}

void GLWidget::paintGL() {
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	s->draw();
}

void GLWidget::keyPressEvent(QKeyEvent* event) {
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
			toggleTime();
		} else {
			throw string("GLWidget::keyPressEvent(...)  unknown action");
		}
	}
	updateGL(); // put this line inside the if brackets ?
}


void GLWidget::timerEvent(QTimerEvent* event) {
	Q_UNUSED(event);

	double dt = chronometer.restart()/1000.;

	// playbackSpeed = 50 means normal playack speed.

	if (playbackSpeed < 50) { // 0 < playbackSpeed < 50 means slower than normal, so make smaller time steps.
			double coef (playbackSpeed/50.); // Linear function of playbackSpeed, passes through (0,0) and (50,1).
			s->evolve(*integrator, dt*coef); 
	}
	else { // 50 < playbackSpeed < 100 means faster than normal. Warning, big time steps cause errors, so make multiple smaller time steps.
		double coef (playbackSpeed*(5./50.)-4.); // Linear function of playbackSpeed, passes through (50,1) and (100,6). This means that at maximal "playbackSpeed=100" the simulation is 6 times normal speed.
		int nbLoops (coef);
		if (playbackSpeed!=50) ++nbLoops;     // "nbLoops" is the integer greater than "coef".
		//cerr << coef << " " << nbLoops << endl;
		for (int i(0); i<nbLoops; ++i ) {
				s->evolve(*integrator, dt*coef/nbLoops); // coef/nbLoops<=1, so all time steps are smaller or equal to dt.
		}
	}

	view.lookAt(s); // *** check booleans, in which camera evolution mode we are


	// cout << *s << endl;
	updateGL();
}

void GLWidget::coutSystem() {
	cout << *s << endl;
}

void GLWidget::mousePressEvent(QMouseEvent* event) {
	lastMousePosition = event->pos();
}

void GLWidget::mouseMoveEvent(QMouseEvent* event) {
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

void GLWidget::stop() {
	if (timerId != 0) {
		killTimer(timerId);
		timerId = 0;
	}
}

