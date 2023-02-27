#include "KeyActionWindow.h"
#include "MainWindow.h"
#include "System.h"
#include "Visual3DWindow.h"
#include "InfoWindow.h"
#include <fstream>



void KeyActionWindow::toggleChrono() {
	if (timerId == 0) { // In this case, the timer is not running, so start it.
		timerId = startTimer(20);
		chronometer.restart();
	} else { // The timer is running so stop it.
		killTimer(timerId);
		timerId = 0;
	}
}

KeyActionWindow::KeyActionWindow(QWidget* parent, MainWindow* mw) : QWidget(parent), parent(mw) {


	tabs = new QTabWidget(this);
	tabs->setGeometry(0, 5, 700, 495);


	timePage = new QWidget;
	timeGrid = new QGridLayout;

	startStopButton = new QPushButton("Start/stop");
	playbackSpeedSlider = new QSlider(Qt::Horizontal);
	playbackSpeedLabel = new QLabel("Vary speed:");

	startStopButton->setFixedHeight(120);
	playbackSpeedSlider->setValue(50);
	playbackSpeedSlider->setRange(1, 100);

	timeGrid->addWidget(startStopButton, 1, 0);
	timeGrid->addWidget(playbackSpeedLabel, 2, 0);
	timeGrid->addWidget(playbackSpeedSlider, 3, 0);




	cameraPage = new QWidget;
	cameraGrid = new QGridLayout;

	camPositionTitle = new QLabel ("Change camera position");
	zButton = new QPushButton("Z plus");
	zzButton = new QPushButton("Z minus");
	xButton = new QPushButton("X plus");
	xxButton = new QPushButton("X minus");
	yButton = new QPushButton("Y plus");
	yyButton = new QPushButton("Y minus");
	toggleFrisbeeTrackingCameraModeButton = new QPushButton("Toggle frisbee tracking camera mode");

	// zButton->setFixedSize(200,100);
	// zzButton->setFixedSize(200,100);
	// xButton->setFixedSize(200,100);
	// xxButton->setFixedSize(200,100);
	// yButton->setFixedSize(200,100);
	// yyButton->setFixedSize(200,100);
	// camPositionTitle->setAutoFillBackground(true);

	cameraGrid->addWidget(camPositionTitle, 0, 1);
	cameraGrid->addWidget(zButton, 2, 1);
	cameraGrid->addWidget(zzButton, 4, 1);
	cameraGrid->addWidget(xButton, 1, 1);
	cameraGrid->addWidget(xxButton, 5, 1);
	cameraGrid->addWidget(yButton, 3, 0);
	cameraGrid->addWidget(yyButton, 3, 2);
	cameraGrid->addWidget(toggleFrisbeeTrackingCameraModeButton, 6, 0, 1, 3);
	
	cameraPage->setLayout(cameraGrid);
	


	keyboardPage = new QWidget;
	keyboardGrid = new QGridLayout;

	// These actions are common to all subclasses. Subclasses can add their own specifics.
	possibleActions.push_back({ pitchUp,		Qt::Key_Up,		new QLabel("Pitch up"),			new QLabel(""), new QPushButton("Set new key") });
	possibleActions.push_back({ pitchDown,		Qt::Key_Down,	new QLabel("Pitch down"),		new QLabel(""), new QPushButton("Set new key") });
	possibleActions.push_back({ yawLeft,		Qt::Key_Left,	new QLabel("Yaw left"),			new QLabel(""), new QPushButton("Set new key") });
	possibleActions.push_back({ yawRight,		Qt::Key_Right,	new QLabel("Yaw right"),		new QLabel(""), new QPushButton("Set new key") });
	possibleActions.push_back({ rollLeft,		Qt::Key_A,		new QLabel("Roll left"),		new QLabel(""), new QPushButton("Set new key") });
	possibleActions.push_back({ rollRight,		Qt::Key_E,		new QLabel("Roll right"),		new QLabel(""), new QPushButton("Set new key") });
	possibleActions.push_back({ moveUp,			Qt::Key_R,		new QLabel("Move up"),			new QLabel(""), new QPushButton("Set new key") });
	possibleActions.push_back({ moveDown,		Qt::Key_F,		new QLabel("Move down"),		new QLabel(""), new QPushButton("Set new key") });
	possibleActions.push_back({ moveLeft,		Qt::Key_Q,		new QLabel("Move left"),		new QLabel(""), new QPushButton("Set new key") });
	possibleActions.push_back({ moveRight,		Qt::Key_D,		new QLabel("Move right"),		new QLabel(""), new QPushButton("Set new key") });
	possibleActions.push_back({ moveForward,	Qt::Key_Z,		new QLabel("Move forwards"),	new QLabel(""), new QPushButton("Set new key") });
	possibleActions.push_back({ moveBackward,	Qt::Key_S,		new QLabel("Move backwards"),	new QLabel(""), new QPushButton("Set new key") });
	possibleActions.push_back({ resetPosition,	Qt::Key_Home,	new QLabel("Reset position"),	new QLabel(""), new QPushButton("Set new key") });
	possibleActions.push_back({ startStopTime,	Qt::Key_Space,	new QLabel("Toggle time"),		new QLabel(""), new QPushButton("Set new key") });

	actionTitleLabel = new QLabel("Action:");
	currentKeyTitleLabel = new QLabel("Current Key:");
	setNewKeyTitleLabel = new QLabel("Click then press new key:");
	keyboardGrid->addWidget(actionTitleLabel, 1, 1);
	keyboardGrid->addWidget(currentKeyTitleLabel, 1, 2);
	keyboardGrid->addWidget(setNewKeyTitleLabel, 1, 3);

	nextKeyPressSetsAction = false;



	savePage = new QWidget;
	saveGrid = new QGridLayout;

	saveStateButton = new QPushButton("Save current state");
	selectStateFileDialogButton = new QPushButton("Select file location");
	saveStateFileNameLabel = new QLabel("");

	saveGrid->addWidget(saveStateButton, 1, 1, 1, 2);
	saveGrid->addWidget(selectStateFileDialogButton, 2, 1);
    saveGrid->addWidget(saveStateFileNameLabel, 2, 2);

	v3dw = new Visual3DWindow(this); 
	v3dw->setWindowFlags(Qt::Dialog | Qt::WindowTitleHint);
	v3dw->setGeometry(1100, 0, 1200, 1055);
	v3dw->show();

	sys = new System(v3dw->getView());

	timerId = 0;
	playbackSpeed = 50; // To change the speed at which time flows (multiplier).
	frisbeeTrackingCameraMode = false;


	infoWin = new InfoWindow(this); // **** added
	// infoWin = new InfoWindow(this, sys, integ);  // **** deleted
	// infoWin = new InfoWindow(this, this);
	infoWin->setWindowFlags(Qt::Dialog | Qt::WindowTitleHint);
	// infoWin->refreshLabels(sys, integ); // **** added
	infoWin->refreshLabels(sys); // **** added
	infoWin->show();


	// Must connect buttons here, so that they live in the whole class.
	QObject::connect(startStopButton, SIGNAL(clicked()), this, SLOT(toggleChrono()));
	QObject::connect(playbackSpeedSlider, SIGNAL(valueChanged(int)), this, SLOT(setPlaybackSpeed(int)) );

	QObject::connect(zButton, SIGNAL(clicked()), v3dw, SLOT(setcamZ()));
	QObject::connect(zzButton, SIGNAL(clicked()), v3dw, SLOT(setcamZZ()));
	QObject::connect(xButton, SIGNAL(clicked()), v3dw, SLOT(setcamX()));
	QObject::connect(xxButton, SIGNAL(clicked()), v3dw, SLOT(setcamXX()));
	QObject::connect(yButton, SIGNAL(clicked()), v3dw, SLOT(setcamY()));
	QObject::connect(yyButton, SIGNAL(clicked()), v3dw, SLOT(setcamYY()));
	QObject::connect(toggleFrisbeeTrackingCameraModeButton, SIGNAL(clicked()), this, SLOT(toggleFrisbeeTrackingCameraMode()));
	
	QObject::connect(selectStateFileDialogButton, SIGNAL(clicked()), this, SLOT(selectSaveCurrentStateFile()));
	QObject::connect(saveStateButton, SIGNAL(clicked()), this, SLOT(saveCurrentState()));
}




KeyActionWindow::~KeyActionWindow() { 
	// cerr << "KeyActionWindow::~KeyActionWindow()" << endl;
	delete sys;
	v3dw->deleteLater();
	infoWin->deleteLater();
}


void KeyActionWindow::stop() {
	if (timerId != 0) {
		killTimer(timerId);
		timerId = 0;
	}
}

void KeyActionWindow::visual3DWindowKeyPressEvent(QKeyEvent* event) {
	KeyAction action;
	if (getMappedAction(event, action)) {
		if (!executeAction(action)) { // Virtual method.
			throw string("VisualSimulation::visual3DWindowKeyPressEvent(...)  unknown action");
		} // Else: action was found and executed.
	} // Else: not a mapped key, do nothing.
}


bool KeyActionWindow::executeAction(KeyAction action) {	

	double smallAngle(5.0); // In degrees.
	double smallStep(1.0);

	if (action==pitchUp) {
		v3dw->getView()->rotate(smallAngle, Vector3(-1.0, 0.0, 0.0));
	} else if (action==pitchDown) {
		v3dw->getView()->rotate(smallAngle, Vector3(+1.0, 0.0, 0.0));
	} else if (action==yawLeft) {
		v3dw->getView()->rotate(smallAngle, Vector3(0.0, -1.0, 0.0));	
	} else if (action==yawRight) {
		v3dw->getView()->rotate(smallAngle, Vector3(0.0, +1.0, 0.0));
	} else if (action==rollLeft) {
		v3dw->getView()->rotate(smallAngle, Vector3(0.0, 0.0, -1.0));
	} else if (action==rollRight) {
		v3dw->getView()->rotate(smallAngle, Vector3(0.0, 0.0, +1.0));
	} else if (action==moveUp) {
		v3dw->getView()->translate(Vector3(0.0, -smallStep, 0.0));
	} else if (action==moveDown) {
		v3dw->getView()->translate(Vector3(0.0,  smallStep, 0.0));
	} else if (action==moveLeft) {
		v3dw->getView()->translate( Vector3(smallStep, 0.0, 0.0));
	} else if (action==moveRight) {
		v3dw->getView()->translate(Vector3(-smallStep, 0.0, 0.0));
	} else if (action==moveForward) {
		v3dw->getView()->translate(Vector3(0.0, 0.0,  smallStep));	
	} else if (action==moveBackward) {
		v3dw->getView()->translate(Vector3(0.0, 0.0, -smallStep));
	} else if (action==resetPosition) {
		v3dw->getView()->initializePosition();
	} else if (action==startStopTime) {
		toggleChrono();
	} else {
		return false;
	}
	v3dw->updateGL();
	return true;
}

void KeyActionWindow::setNewAction(int i) {
	nextKeyPressSetsAction = true;
	actionToSet = possibleActions[i].action;
}


void KeyActionWindow::selectSaveCurrentStateFile() {
	saveStateFileNameLabel->setText(QFileDialog::getSaveFileName(this,tr("Select file location to save current state"),"",tr("State Files (*.state)")));
}

void KeyActionWindow::saveCurrentState() {
	try {
		string fileName (saveStateFileNameLabel->text().toStdString());

		string extension (".state");
		size_t extSiz (extension.size());
		if (fileName.size()>=extSiz) {
			if (fileName.substr(fileName.size()-extSiz,extSiz)!=extension) {
				fileName += extension;
			}
		}

		ofstream output(fileName);	// Open flow.
		if (output.fail()) {
			throw string("Visual3DWindow::saveCurrentState(...)  impossible to open '"+fileName+"' in write mode");
		}
		
		output << sys->getHeaders() << endl << sys->getCurrentState();		
		output.close();

		QMessageBox msgBox;
		msgBox.setText(QString::fromStdString("Current state successfully saved to file : "+fileName));
		msgBox.exec();

	}catch (std::string s) {
		QMessageBox::information(this, "Problem", QString::fromStdString(s));
	}
}


void KeyActionWindow::toggleFrisbeeTrackingCameraMode() {
	frisbeeTrackingCameraMode = !frisbeeTrackingCameraMode;
}

void KeyActionWindow::setPlaybackSpeed(int a){
	playbackSpeed = a;
	// cerr << a << endl;
}

void KeyActionWindow::initKeyboardPage() {

	QSignalMapper* signalMapper = new QSignalMapper(this);

	for (size_t i=0; i<possibleActions.size(); ++i) {
		keyboardGrid->addWidget(possibleActions[i].nameLabel, i+2, 1);
		keyboardGrid->addWidget(possibleActions[i].currentKeyLabel, i+2, 2);
		keyboardGrid->addWidget(possibleActions[i].setNewKeyButton, i+2, 3);
		
		possibleActions[i].currentKeyLabel->setText(QKeySequence( possibleActions[i].key ).toString());

		QObject::connect(possibleActions[i].setNewKeyButton, SIGNAL(clicked()), signalMapper, SLOT(map()));
		signalMapper->setMapping(possibleActions[i].setNewKeyButton, i);
	}

	QObject::connect(signalMapper, SIGNAL(mapped(int)), this, SLOT(setNewAction(int)));

	keyboardPage->setLayout(keyboardGrid);
}



void KeyActionWindow::keyPressEvent(QKeyEvent* event) {
	if (nextKeyPressSetsAction) {
		nextKeyPressSetsAction = false;

		if (remapKeyToAction(event->key(), actionToSet)) {
			// *** (while nextKeyPressSetsAction change the text of label or button to say that you are waiting for a keypress)
		} else {
			// *** dialogue box or error msg saying that this key is already attributed.
		}
	}
}


bool KeyActionWindow::getMappedAction(QKeyEvent* event, KeyAction& action) {
	for (auto& el : possibleActions) {
		if (event->key()==el.key) {
			action = el.action;
			return true;
		}
	}
	return false;
}


bool KeyActionWindow::remapKeyToAction(int key, KeyAction& action) {
	for (auto& el : possibleActions) {
		if (key==el.key) {
			return false; // The key is already used for another action. So ignore this request.
		}
	}
	// The key is not already attributed to other action. Good, so attribute it to this action.
	for (auto& el : possibleActions){
		if (el.action==action) {
			el.key = key;
			el.currentKeyLabel->setText(QKeySequence(key).toString());
			return true;
		}
	}
	throw string("KeyActionWindow::remapKeyToAction(...)  KeyAction not found");
}
