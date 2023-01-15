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

	mapKeyToAction(Qt::Key_Up, pitchUp);
	mapKeyToAction(Qt::Key_Down, pitchDown);
	mapKeyToAction(Qt::Key_Left, yawLeft);
	mapKeyToAction(Qt::Key_Right, yawRight);
	mapKeyToAction(Qt::Key_A, rollLeft);
	mapKeyToAction(Qt::Key_E, rollRight);
	mapKeyToAction(Qt::Key_R, moveUp);
	mapKeyToAction(Qt::Key_F, moveDown);
	mapKeyToAction(Qt::Key_Q, moveLeft);
	mapKeyToAction(Qt::Key_D, moveRight);
	mapKeyToAction(Qt::Key_Z, moveForward);
	mapKeyToAction(Qt::Key_S, moveBackward);
	mapKeyToAction(Qt::Key_Home, resetPosition);
	mapKeyToAction(Qt::Key_Space, startStopTime);

	actionTitleLabel = new QLabel("Action:");
	currentKeyTitleLabel = new QLabel("Current Key:");
	setNewKeyTitleLabel = new QLabel("Click then press new key:");
	keyboardGrid->addWidget(actionTitleLabel, 1, 1);
	keyboardGrid->addWidget(currentKeyTitleLabel, 1, 2);
	keyboardGrid->addWidget(setNewKeyTitleLabel, 1, 3);

	pitchUpLabel = new QLabel("Pitch up");
	pitchDownLabel = new QLabel("Pitch down");
	yawLeftLabel = new QLabel("Yaw left");
	yawRightLabel = new QLabel("Yaw right");
	rollLeftLabel = new QLabel("Roll left");
	rollRightLabel = new QLabel("Roll right");
	moveUpLabel = new QLabel("Move up");
	moveDownLabel = new QLabel("Move down");
	moveLeftLabel = new QLabel("Move left");
	moveRightLabel = new QLabel("Move right");
	moveForwardLabel = new QLabel("Move forwards");
	moveBackwardLabel = new QLabel("Move backwards");
	resetPositionLabel = new QLabel("Reset position");
	startStopTimeLabel = new QLabel("Toggle time");

	pitchUpCurKeyLabel = new QLabel("");
	pitchDownCurKeyLabel = new QLabel("");
	yawLeftCurKeyLabel = new QLabel("");
	yawRightCurKeyLabel = new QLabel("");
	rollLeftCurKeyLabel = new QLabel("");
	rollRightCurKeyLabel = new QLabel("");
	moveUpCurKeyLabel = new QLabel("");
	moveDownCurKeyLabel = new QLabel("");
	moveLeftCurKeyLabel = new QLabel("");
	moveRightCurKeyLabel = new QLabel("");
	moveForwardCurKeyLabel = new QLabel("");
	moveBackwardCurKeyLabel = new QLabel("");
	resetPositionCurKeyLabel = new QLabel("");
	startStopTimeCurKeyLabel = new QLabel("");

	refreshCurKeyLabels();

	pitchUpSetButton = new QPushButton("Set new key");
	pitchDownSetButton = new QPushButton("Set new key");
	yawLeftSetButton = new QPushButton("Set new key");
	yawRightSetButton = new QPushButton("Set new key");
	rollLeftSetButton = new QPushButton("Set new key");
	rollRightSetButton = new QPushButton("Set new key");
	moveUpSetButton = new QPushButton("Set new key");
	moveDownSetButton = new QPushButton("Set new key");
	moveLeftSetButton = new QPushButton("Set new key");
	moveRightSetButton = new QPushButton("Set new key");
	moveForwardSetButton = new QPushButton("Set new key");
	moveBackwardSetButton = new QPushButton("Set new key");
	resetPositionSetButton = new QPushButton("Set new key");
	startStopTimeSetButton = new QPushButton("Set new key");

	keyboardGrid->addWidget(pitchUpLabel, 2, 1);
	keyboardGrid->addWidget(pitchDownLabel, 3, 1);
	keyboardGrid->addWidget(yawLeftLabel, 4, 1);
	keyboardGrid->addWidget(yawRightLabel, 5, 1);
	keyboardGrid->addWidget(rollLeftLabel, 6, 1);
	keyboardGrid->addWidget(rollRightLabel, 7, 1);
	keyboardGrid->addWidget(moveUpLabel, 8, 1);
	keyboardGrid->addWidget(moveDownLabel, 9, 1);
	keyboardGrid->addWidget(moveLeftLabel, 10, 1);
	keyboardGrid->addWidget(moveRightLabel, 11, 1);
	keyboardGrid->addWidget(moveForwardLabel, 12, 1);
	keyboardGrid->addWidget(moveBackwardLabel, 13, 1);
	keyboardGrid->addWidget(resetPositionLabel, 14, 1);
	keyboardGrid->addWidget(startStopTimeLabel, 15, 1);

	keyboardGrid->addWidget(pitchUpCurKeyLabel, 2, 2);
	keyboardGrid->addWidget(pitchDownCurKeyLabel, 3, 2);
	keyboardGrid->addWidget(yawLeftCurKeyLabel, 4, 2);
	keyboardGrid->addWidget(yawRightCurKeyLabel, 5, 2);
	keyboardGrid->addWidget(rollLeftCurKeyLabel, 6, 2);
	keyboardGrid->addWidget(rollRightCurKeyLabel, 7, 2);
	keyboardGrid->addWidget(moveUpCurKeyLabel, 8, 2);
	keyboardGrid->addWidget(moveDownCurKeyLabel, 9, 2);
	keyboardGrid->addWidget(moveLeftCurKeyLabel, 10, 2);
	keyboardGrid->addWidget(moveRightCurKeyLabel, 11, 2);
	keyboardGrid->addWidget(moveForwardCurKeyLabel, 12, 2);
	keyboardGrid->addWidget(moveBackwardCurKeyLabel, 13, 2);
	keyboardGrid->addWidget(resetPositionCurKeyLabel, 14, 2);
	keyboardGrid->addWidget(startStopTimeCurKeyLabel, 15, 2);

	keyboardGrid->addWidget(pitchUpSetButton, 2, 3);
	keyboardGrid->addWidget(pitchDownSetButton, 3, 3);
	keyboardGrid->addWidget(yawLeftSetButton, 4, 3);
	keyboardGrid->addWidget(yawRightSetButton, 5, 3);
	keyboardGrid->addWidget(rollLeftSetButton, 6, 3);
	keyboardGrid->addWidget(rollRightSetButton, 7, 3);
	keyboardGrid->addWidget(moveUpSetButton, 8, 3);
	keyboardGrid->addWidget(moveDownSetButton, 9, 3);
	keyboardGrid->addWidget(moveLeftSetButton, 10, 3);
	keyboardGrid->addWidget(moveRightSetButton, 11, 3);
	keyboardGrid->addWidget(moveForwardSetButton, 12, 3);
	keyboardGrid->addWidget(moveBackwardSetButton, 13, 3);
	keyboardGrid->addWidget(resetPositionSetButton, 14, 3);
	keyboardGrid->addWidget(startStopTimeSetButton, 15, 3);

	keyboardPage->setLayout(keyboardGrid);

	nextKeyPressSetsAction = false;

	// vector<string> actionNames ({ "Pitch up", "Pitch down", "Yaw left", "Yaw right", "Roll left", "Roll right", "Move up", "Move down", "Move left", "Move right", "Move forwards", "Move backwards", "Reset position", "Toggle time" });
	// for (const auto action : KeyAction::All) {

	// 	actionLabels.push_back(new QLabel(actionNames[action])); // *** std:: ?
	// 	currentKeyLabels.push_back(new QLabel(findBindedKey(action))) *** findBindedKey implement
	// 	setNewKeyButtons.push_back(new QPushButton("Set new key")); // *** std:: ?

	//     keyboardGrid->addWidget(keyActionLabels[action], 2+action, 1);
	//     keyboardGrid->addWidget(currentKeyLabels[action], 2+action, 2);
	//     keyboardGrid->addWidget(setNewKeyButtons[action], 2+action, 3);
	// }



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
		
	QObject::connect(pitchUpSetButton, SIGNAL(clicked()), this, SLOT(pitchUpSetNew()));
	QObject::connect(pitchDownSetButton, SIGNAL(clicked()), this, SLOT(pitchDownSetNew()));
	QObject::connect(yawLeftSetButton, SIGNAL(clicked()), this, SLOT(yawLeftSetNew()));
	QObject::connect(yawRightSetButton, SIGNAL(clicked()), this, SLOT(yawRightSetNew()));
	QObject::connect(rollLeftSetButton, SIGNAL(clicked()), this, SLOT(rollLeftSetNew()));
	QObject::connect(rollRightSetButton, SIGNAL(clicked()), this, SLOT(rollRightSetNew()));
	QObject::connect(moveUpSetButton, SIGNAL(clicked()), this, SLOT(moveUpSetNew()));
	QObject::connect(moveDownSetButton, SIGNAL(clicked()), this, SLOT(moveDownSetNew()));
	QObject::connect(moveLeftSetButton, SIGNAL(clicked()), this, SLOT(moveLeftSetNew()));
	QObject::connect(moveRightSetButton, SIGNAL(clicked()), this, SLOT(moveRightSetNew()));
	QObject::connect(moveForwardSetButton, SIGNAL(clicked()), this, SLOT(moveForwardSetNew()));
	QObject::connect(moveBackwardSetButton, SIGNAL(clicked()), this, SLOT(moveBackwardSetNew()));
	QObject::connect(resetPositionSetButton, SIGNAL(clicked()), this, SLOT(resetPositionSetNew()));
	QObject::connect(startStopTimeSetButton, SIGNAL(clicked()), this, SLOT(startStopTimeSetNew()));

	QObject::connect(selectStateFileDialogButton, SIGNAL(clicked()), this, SLOT(selectSaveCurrentStateFile()));
	QObject::connect(saveStateButton, SIGNAL(clicked()), this, SLOT(saveCurrentState()));
}




KeyActionWindow::~KeyActionWindow() { 
	cerr << "KeyActionWindow::~KeyActionWindow()" << endl;
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


void KeyActionWindow::pitchUpSetNew() {
	nextKeyPressSetsAction = true;
	// setNewKeyTitleLabel->Focus();	
	actionToSet = pitchUp;
}

void KeyActionWindow::pitchDownSetNew() {
	nextKeyPressSetsAction = true;
	// setNewKeyTitleLabel->Focus();	
	actionToSet = pitchDown;
}

void KeyActionWindow::yawLeftSetNew() {
	nextKeyPressSetsAction = true;
	// setNewKeyTitleLabel->Focus();	
	actionToSet = yawLeft;
}

void KeyActionWindow::yawRightSetNew() {
	nextKeyPressSetsAction = true;
	// setNewKeyTitleLabel->Focus();	
	actionToSet = yawRight;
}

void KeyActionWindow::rollLeftSetNew() {
	nextKeyPressSetsAction = true;
	// setNewKeyTitleLabel->Focus();	
	actionToSet = rollLeft;
}

void KeyActionWindow::rollRightSetNew() {
	nextKeyPressSetsAction = true;
	// setNewKeyTitleLabel->Focus();	
	actionToSet = rollRight;
}

void KeyActionWindow::moveUpSetNew() {
	nextKeyPressSetsAction = true;
	// setNewKeyTitleLabel->Focus();	
	actionToSet = moveUp;
}

void KeyActionWindow::moveDownSetNew() {
	nextKeyPressSetsAction = true;
	// setNewKeyTitleLabel->Focus();	
	actionToSet = moveDown;
}

void KeyActionWindow::moveLeftSetNew() {
	nextKeyPressSetsAction = true;
	// setNewKeyTitleLabel->Focus();	
	actionToSet = moveLeft;
}

void KeyActionWindow::moveRightSetNew() {
	nextKeyPressSetsAction = true;
	// setNewKeyTitleLabel->Focus();	
	actionToSet = moveRight;
}

void KeyActionWindow::moveForwardSetNew() {
	nextKeyPressSetsAction = true;
	// setNewKeyTitleLabel->Focus();	
	actionToSet = moveForward;
}

void KeyActionWindow::moveBackwardSetNew() {
	nextKeyPressSetsAction = true;
	// setNewKeyTitleLabel->Focus();	
	actionToSet = moveBackward;
}

void KeyActionWindow::resetPositionSetNew() {
	nextKeyPressSetsAction = true;
	// setNewKeyTitleLabel->Focus();	
	actionToSet = resetPosition;
}

void KeyActionWindow::startStopTimeSetNew() {
	nextKeyPressSetsAction = true;
	// setNewKeyTitleLabel->Focus();	
	actionToSet = startStopTime;
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
	 cerr << a << endl;
}


void KeyActionWindow::refreshCurKeyLabels() {
	// QString:: ?
	pitchUpCurKeyLabel->setText(QKeySequence(findBindedKey(pitchUp)).toString());
	pitchDownCurKeyLabel->setText(QKeySequence(findBindedKey(pitchDown)).toString());
	yawLeftCurKeyLabel->setText(QKeySequence(findBindedKey(yawLeft)).toString());
	yawRightCurKeyLabel->setText(QKeySequence(findBindedKey(yawRight)).toString());
	rollLeftCurKeyLabel->setText(QKeySequence(findBindedKey(rollLeft)).toString());
	rollRightCurKeyLabel->setText(QKeySequence(findBindedKey(rollRight)).toString());
	moveUpCurKeyLabel->setText(QKeySequence(findBindedKey(moveUp)).toString());
	moveDownCurKeyLabel->setText(QKeySequence(findBindedKey(moveDown)).toString());
	moveLeftCurKeyLabel->setText(QKeySequence(findBindedKey(moveLeft)).toString());
	moveRightCurKeyLabel->setText(QKeySequence(findBindedKey(moveRight)).toString());
	moveForwardCurKeyLabel->setText(QKeySequence(findBindedKey(moveForward)).toString());
	moveBackwardCurKeyLabel->setText(QKeySequence(findBindedKey(moveBackward)).toString());
	resetPositionCurKeyLabel->setText(QKeySequence(findBindedKey(resetPosition)).toString());
	startStopTimeCurKeyLabel->setText(QKeySequence(findBindedKey(startStopTime)).toString());
}



void KeyActionWindow::keyPressEvent(QKeyEvent* event) {
	if (nextKeyPressSetsAction) {
		nextKeyPressSetsAction = false;

		if (remapKeyToAction(event->key(), actionToSet)) {
			// *** (while nextKeyPressSetsAction change the text of label or button to say that you are waiting for a keypress)
			refreshCurKeyLabels();
		} else {
			// *** dialogue box or error msg saying that this key is already attributed.
		}
	}
}


// double KeyActionWindow::getCurrentTime() {
// 		return sys->time();
// }


bool KeyActionWindow::mapKeyToAction(int key, KeyAction action) {
	keyActionMap[key] = action;
}

bool KeyActionWindow::getMappedAction(QKeyEvent* event, KeyAction& action) {

	map<int, KeyAction>::iterator it = keyActionMap.find(event->key()); // Find the action corresponding to this key press. 

	if (it != keyActionMap.end()) { 
		action = it->second;
		return true;
	} else {
		return false;
	}

}

int KeyActionWindow::findBindedKey(KeyAction const& a) {
	for (auto& it : keyActionMap) {
		if (it.second==a) {
			return it.first;
		}
	}
	throw string("KeyActionWindow::findBindedKey(...)  action doesn't have any key binding");
}


bool KeyActionWindow::remapKeyToAction(int key, KeyAction& action) {

	map<int, KeyAction>::iterator it = keyActionMap.find(key);

	if (it == keyActionMap.end()) {
		// The key is not already attributed to other action. Good, so attribute it to this action.
		bool valueNotYetFound (true);
		for (map<int, KeyAction>::iterator it=keyActionMap.begin(); it!=keyActionMap.end() && valueNotYetFound; ++it) {
			if (it->second==action) {
				keyActionMap.erase(it);
				valueNotYetFound = false;
			}
		}
		keyActionMap[key] = action;

		return true;
	} else {
		return false;
	}
}
