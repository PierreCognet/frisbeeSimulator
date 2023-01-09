#include "VisualSimulation.h"
#include "Visual3DWindow.h"
#include "InfoWindow.h"
#include <QString>
#include "Integrator.h"
// #include "IntegratorEuler.h"
// #include "IntegratorNewmark.h"
#include "IntegratorRK4.h"
#include "OpenGLViewer.h"
#include <QFileDialog>
#include <fstream>


VisualSimulation::VisualSimulation(QWidget *parent, MainWindow* mw) : QWidget(parent), parent(mw) {


	setWindowTitle("Visual Simulation");
	//setFixedSize(700, 500);
	setGeometry(0, 0 , 700, 500);

	tabs = new QTabWidget(this);
	tabs->setGeometry(0, 5, 700, 495);


	// Declare Widgets.
	frisbeePage = new QWidget;
	frisbeeGrid = new QGridLayout;

	xSpinBox = new QDoubleSpinBox();
    ySpinBox = new QDoubleSpinBox();
    zSpinBox = new QDoubleSpinBox();
    phiSpinBox = new QDoubleSpinBox();
    thetaSpinBox = new QDoubleSpinBox();
    psiSpinBox = new QDoubleSpinBox();
    uSpinBox = new QDoubleSpinBox();
    vSpinBox = new QDoubleSpinBox();
    wSpinBox = new QDoubleSpinBox();
    pSpinBox = new QDoubleSpinBox();
    qSpinBox = new QDoubleSpinBox();
    rSpinBox = new QDoubleSpinBox();
	xLabel = new QLabel("x:");
    yLabel = new QLabel("y:");
    zLabel = new QLabel("z:");
    phiLabel = new QLabel("phi:");
    thetaLabel = new QLabel("theta:");
    psiLabel = new QLabel("psi:");
    uLabel = new QLabel("u:");
    vLabel = new QLabel("v:");
    wLabel = new QLabel("w:");
    pLabel = new QLabel("p:");
    qLabel = new QLabel("q:");
    rLabel = new QLabel("r:");
	setFrisbeeStateButton = new QPushButton("Set values");
	toggleUvwBodyEarthAxesButton = new QPushButton("Toogle between earth and body axes for velocity");
	uvwIsBodyNotEarthAxes = true;

	xSpinBox->setValue(0.01);
    ySpinBox->setValue(0.01);
    zSpinBox->setValue(0.01);
    phiSpinBox->setValue(0.01);
    thetaSpinBox->setValue(0.01);
    psiSpinBox->setValue(0.01);
    uSpinBox->setValue(1);
    vSpinBox->setValue(0.01);
    wSpinBox->setValue(0.01);
    pSpinBox->setValue(0.01);
    qSpinBox->setValue(0.01);
    rSpinBox->setValue(1);

	xSpinBox->setRange(-1000, 1000);
    ySpinBox->setRange(-1000, 1000);
    zSpinBox->setRange(-1000, 1000);
    phiSpinBox->setRange(-1000, 1000);
    thetaSpinBox->setRange(-1000, 1000);
    psiSpinBox->setRange(-1000, 1000);
    uSpinBox->setRange(-1000, 1000);
    vSpinBox->setRange(-1000, 1000);
    wSpinBox->setRange(-1000, 1000);
    pSpinBox->setRange(-1000, 1000);
    qSpinBox->setRange(-1000, 1000);
    rSpinBox->setRange(-1000, 1000);

	frisbeeGrid->addWidget(xSpinBox, 2, 2);
    frisbeeGrid->addWidget(ySpinBox, 3, 2);
    frisbeeGrid->addWidget(zSpinBox, 4, 2);
    frisbeeGrid->addWidget(phiSpinBox, 5, 2);
    frisbeeGrid->addWidget(thetaSpinBox, 6, 2);
    frisbeeGrid->addWidget(psiSpinBox, 7, 2);
    frisbeeGrid->addWidget(uSpinBox, 9, 2);
    frisbeeGrid->addWidget(vSpinBox, 10, 2);
    frisbeeGrid->addWidget(wSpinBox, 11, 2);
    frisbeeGrid->addWidget(pSpinBox, 12, 2);
    frisbeeGrid->addWidget(qSpinBox, 13, 2);
    frisbeeGrid->addWidget(rSpinBox, 14, 2);
	frisbeeGrid->addWidget(xLabel, 2, 1);
    frisbeeGrid->addWidget(yLabel, 3, 1);
    frisbeeGrid->addWidget(zLabel, 4, 1);
    frisbeeGrid->addWidget(phiLabel, 5, 1);
    frisbeeGrid->addWidget(thetaLabel, 6, 1);
    frisbeeGrid->addWidget(psiLabel, 7, 1);
    frisbeeGrid->addWidget(uLabel, 9, 1);
    frisbeeGrid->addWidget(vLabel, 10, 1);
    frisbeeGrid->addWidget(wLabel, 11, 1);
    frisbeeGrid->addWidget(pLabel, 12, 1);
    frisbeeGrid->addWidget(qLabel, 13, 1);
    frisbeeGrid->addWidget(rLabel, 14, 1);
    frisbeeGrid->addWidget(setFrisbeeStateButton, 1, 1, 1, 2);
    frisbeeGrid->addWidget(toggleUvwBodyEarthAxesButton, 8, 1, 1, 2);

	frisbeePage->setLayout(frisbeeGrid);



	timePage = new QWidget;
	timeGrid = new QGridLayout;

	startStopButton = new QPushButton("Start/stop");
	resetTimeButton = new QPushButton ("Reinitialize time");
	playbackSpeedSlider = new QSlider(Qt::Horizontal);
	playbackSpeedLabel = new QLabel("Vary speed:");

	integratorGrid = new QGridLayout;
	integratorLabel = new QLabel("Change integrator:");
	// boutonIntegrateurEuler = new QPushButton("Euler");
	// boutonIntegrateurNewmark = new QPushButton("Newmark");
	rk4Button = new QPushButton("RungeKutta");

	startStopButton->setFixedHeight(120);
	resetTimeButton->setFixedSize(200,80);
	playbackSpeedSlider->setValue(50);
	playbackSpeedSlider->setRange(1, 100);

	integratorGrid->addWidget(resetTimeButton, 1, 1, 1, 1);
	integratorGrid->addWidget(integratorLabel, 2, 1, 2, 1);
	// integratorGrid->addWidget(boutonIntegrateurEuler, 3, 0);
	// integratorGrid->addWidget(boutonIntegrateurNewmark, 3, 1);
	integratorGrid->addWidget(rk4Button, 3, 2);


	timeGrid->addWidget(startStopButton, 1, 0);
	timeGrid->addWidget(playbackSpeedLabel, 2, 0);
	timeGrid->addWidget(playbackSpeedSlider, 3, 0);
	timeGrid->addLayout(integratorGrid, 4, 0, 3, 1);

	timePage->setLayout(timeGrid);




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

	keyActionMap[Qt::Key_Up] = pitchUp;
	keyActionMap[Qt::Key_Down] = pitchDown;
	keyActionMap[Qt::Key_Left] = yawLeft;
	keyActionMap[Qt::Key_Right] = yawRight;
	keyActionMap[Qt::Key_A] = rollLeft;
	keyActionMap[Qt::Key_E] = rollRight;
	keyActionMap[Qt::Key_R] = moveUp;
	keyActionMap[Qt::Key_F] = moveDown;
	keyActionMap[Qt::Key_Q] = moveLeft;
	keyActionMap[Qt::Key_D] = moveRight;
	keyActionMap[Qt::Key_Z] = moveForward;
	keyActionMap[Qt::Key_S] = moveBackward;
	keyActionMap[Qt::Key_Home] = resetPosition;
	keyActionMap[Qt::Key_Space] = startStopTime;

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
	// pitchUpCurKeyLabel = new QLabel(QKeySequence(findBindedKey(pitchUp)).toString());
	// pitchDownCurKeyLabel = new QLabel(QKeySequence(findBindedKey(pitchDown)).toString());
	// yawLeftCurKeyLabel = new QLabel(QKeySequence(findBindedKey(yawLeft)).toString());
	// yawRightCurKeyLabel = new QLabel(QKeySequence(findBindedKey(yawRight)).toString());
	// rollLeftCurKeyLabel = new QLabel(QKeySequence(findBindedKey(rollLeft)).toString());
	// rollRightCurKeyLabel = new QLabel(QKeySequence(findBindedKey(rollRight)).toString());
	// moveUpCurKeyLabel = new QLabel(QKeySequence(findBindedKey(moveUp)).toString());
	// moveDownCurKeyLabel = new QLabel(QKeySequence(findBindedKey(moveDown)).toString());
	// moveLeftCurKeyLabel = new QLabel(QKeySequence(findBindedKey(moveLeft)).toString());
	// moveRightCurKeyLabel = new QLabel(QKeySequence(findBindedKey(moveRight)).toString());
	// moveForwardCurKeyLabel = new QLabel(QKeySequence(findBindedKey(moveForward)).toString());
	// moveBackwardCurKeyLabel = new QLabel(QKeySequence(findBindedKey(moveBackward)).toString());
	// resetPositionCurKeyLabel = new QLabel(QKeySequence(findBindedKey(resetPosition)).toString());
	// startStopTimeCurKeyLabel = new QLabel(QKeySequence(findBindedKey(startStopTime)).toString());
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
	loadStateButton = new QPushButton("Load state from file");
	selectLoadStateFileDialogButton = new QPushButton("Select file location");
	loadStateFileNameLabel = new QLabel("");

	saveGrid->addWidget(saveStateButton, 1, 1, 1, 2);
	saveGrid->addWidget(selectStateFileDialogButton, 2, 1);
    saveGrid->addWidget(saveStateFileNameLabel, 2, 2);
	saveGrid->addWidget(loadStateButton, 4, 1, 1, 2);
	saveGrid->addWidget(selectLoadStateFileDialogButton, 5, 1);
    saveGrid->addWidget(loadStateFileNameLabel, 5, 2);

	savePage->setLayout(saveGrid);



	// Fill the tabs.
	tabs->addTab(frisbeePage, "Frisbee");
	tabs->addTab(timePage, " Time");
	tabs->addTab(cameraPage, " Camera");
	tabs->addTab(keyboardPage, " Keyboard Bindings");
	tabs->addTab(savePage, " Save File");


	v3dw = new Visual3DWindow(this); 
	v3dw->setWindowFlags(Qt::Dialog | Qt::WindowTitleHint);
	v3dw->setGeometry(1100 , 0, 1200 , 1055);
	v3dw->show();

	sys = new System(v3dw->getView());
	integ = new IntegratorRK4; // RK4 by default.
	timerId = 0;
	playbackSpeed = 50; // To change the speed at which time flows (multiplier).
	frisbeeTrackingCameraMode = false;



	infoWin = new InfoWindow(this, this);
	infoWin->setWindowFlags(Qt::Dialog | Qt::WindowTitleHint);
	infoWin->show();


	// Must connect buttons here, so that they live in the whole class.
    QObject::connect(setFrisbeeStateButton, SIGNAL(clicked()), this, SLOT(setFrisbeeState()));
    QObject::connect(toggleUvwBodyEarthAxesButton, SIGNAL(clicked()), this, SLOT(toggleUvwBodyEarthAxes()));

	QObject::connect(startStopButton, SIGNAL(clicked()), this, SLOT(toggleTime()));

	QObject::connect(zButton, SIGNAL(clicked()), v3dw, SLOT(setcamZ()));
	QObject::connect(zzButton, SIGNAL(clicked()), v3dw, SLOT(setcamZZ()));
	QObject::connect(xButton, SIGNAL(clicked()), v3dw, SLOT(setcamX()));
	QObject::connect(xxButton, SIGNAL(clicked()), v3dw, SLOT(setcamXX()));
	QObject::connect(yButton, SIGNAL(clicked()), v3dw, SLOT(setcamY()));
	QObject::connect(yyButton, SIGNAL(clicked()), v3dw, SLOT(setcamYY()));
	QObject::connect(toggleFrisbeeTrackingCameraModeButton, SIGNAL(clicked()), this, SLOT(toggleFrisbeeTrackingCameraMode()));

	
	// QObject::connect(boutonIntegrateurEuler, SIGNAL(clicked()), this , SLOT(set_Euler()));
	// QObject::connect(boutonIntegrateurNewmark, SIGNAL(clicked()), this, SLOT(set_Newmark()));
	QObject::connect(rk4Button, SIGNAL(clicked()), this, SLOT(setRK4()));
	
	QObject::connect(playbackSpeedSlider, SIGNAL(valueChanged(int)), this, SLOT(setPlaybackSpeed(int)) );
	
	QObject::connect(resetTimeButton, SIGNAL(clicked()), this, SLOT(resetTime()));
	
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
	QObject::connect(selectLoadStateFileDialogButton, SIGNAL(clicked()), this, SLOT(selectLoadStateFile()));
	QObject::connect(loadStateButton, SIGNAL(clicked()), this, SLOT(loadState()));
}


VisualSimulation::~VisualSimulation() { 
	cerr << "VisualSimulation::~VisualSimulation" << endl;
	delete integ;
	delete sys;
	v3dw->deleteLater();
	infoWin->deleteLater();
}



void VisualSimulation::toggleFrisbeeTrackingCameraMode() {
	frisbeeTrackingCameraMode = !frisbeeTrackingCameraMode;
}



void VisualSimulation::setFrisbeeState() {
	try {
    	sys->setFrisbeeState(Vector3(xSpinBox->value(), ySpinBox->value(), zSpinBox->value()),
    						Vector3(phiSpinBox->value(), thetaSpinBox->value(), psiSpinBox->value()),
    						Vector3(uSpinBox->value(), vSpinBox->value(), wSpinBox->value()),
    						Vector3(pSpinBox->value(), qSpinBox->value(), rSpinBox->value()),
    						uvwIsBodyNotEarthAxes);
		stop();
		v3dw->updateGL();

		// cout << *sys << endl;
    	
    }catch (std::string s) {
        QMessageBox::information(this, "Problem", QString::fromStdString(s));
    }
}

void VisualSimulation::toggleUvwBodyEarthAxes() {
	uvwIsBodyNotEarthAxes = !uvwIsBodyNotEarthAxes;
	if (uvwIsBodyNotEarthAxes) {
		uLabel->setText("u:");
		vLabel->setText("v:");
		wLabel->setText("w:");
	} else {
		uLabel->setText("xDot (Earth axes):");
		vLabel->setText("yDot (Earth axes):");
		wLabel->setText("zDot (Earth axes):");
	}
}

void VisualSimulation::pitchUpSetNew() {
	nextKeyPressSetsAction = true;
	// setNewKeyTitleLabel->Focus();	
	actionToSet = pitchUp;
}

void VisualSimulation::pitchDownSetNew() {
	nextKeyPressSetsAction = true;
	// setNewKeyTitleLabel->Focus();	
	actionToSet = pitchDown;
}

void VisualSimulation::yawLeftSetNew() {
	nextKeyPressSetsAction = true;
	// setNewKeyTitleLabel->Focus();	
	actionToSet = yawLeft;
}

void VisualSimulation::yawRightSetNew() {
	nextKeyPressSetsAction = true;
	// setNewKeyTitleLabel->Focus();	
	actionToSet = yawRight;
}

void VisualSimulation::rollLeftSetNew() {
	nextKeyPressSetsAction = true;
	// setNewKeyTitleLabel->Focus();	
	actionToSet = rollLeft;
}

void VisualSimulation::rollRightSetNew() {
	nextKeyPressSetsAction = true;
	// setNewKeyTitleLabel->Focus();	
	actionToSet = rollRight;
}

void VisualSimulation::moveUpSetNew() {
	nextKeyPressSetsAction = true;
	// setNewKeyTitleLabel->Focus();	
	actionToSet = moveUp;
}

void VisualSimulation::moveDownSetNew() {
	nextKeyPressSetsAction = true;
	// setNewKeyTitleLabel->Focus();	
	actionToSet = moveDown;
}

void VisualSimulation::moveLeftSetNew() {
	nextKeyPressSetsAction = true;
	// setNewKeyTitleLabel->Focus();	
	actionToSet = moveLeft;
}

void VisualSimulation::moveRightSetNew() {
	nextKeyPressSetsAction = true;
	// setNewKeyTitleLabel->Focus();	
	actionToSet = moveRight;
}

void VisualSimulation::moveForwardSetNew() {
	nextKeyPressSetsAction = true;
	// setNewKeyTitleLabel->Focus();	
	actionToSet = moveForward;
}

void VisualSimulation::moveBackwardSetNew() {
	nextKeyPressSetsAction = true;
	// setNewKeyTitleLabel->Focus();	
	actionToSet = moveBackward;
}

void VisualSimulation::resetPositionSetNew() {
	nextKeyPressSetsAction = true;
	// setNewKeyTitleLabel->Focus();	
	actionToSet = resetPosition;
}

void VisualSimulation::startStopTimeSetNew() {
	nextKeyPressSetsAction = true;
	// setNewKeyTitleLabel->Focus();	
	actionToSet = startStopTime;
}

void VisualSimulation::selectSaveCurrentStateFile() {
	saveStateFileNameLabel->setText(QFileDialog::getSaveFileName(this,tr("Select file location to save current state"),"",tr("State Files (*.state)")));
}

void VisualSimulation::saveCurrentState() {
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

void VisualSimulation::selectLoadStateFile() {
	loadStateFileNameLabel->setText(QFileDialog::getOpenFileName(this,QString::fromLocal8Bit("Select state file to load"),"",tr("State Files (*.state)")));
}

void VisualSimulation::loadState() {
	try {
		string fileName (loadStateFileNameLabel->text().toStdString());


		ifstream input(fileName);
		if (input.fail()) {
			throw string("Visual3DWindow::loadState(...)  impossible to load '"+fileName+"' in read mode");
		}
		
		if (input.is_open()) {

			try {
				System* tmpSyst ( new System(v3dw->getView(), input) );	// Create new system. Note that this process can fail if there are format errors.
				delete sys;	// If successfully loaded, delete and replace the old System.
				sys = tmpSyst;	//on garde le nouveau
			} catch (std::string s) {
			    QMessageBox::information(this, "Exception caught", QString::fromStdString(s));
			} catch (const std::exception& e) {
			    QMessageBox::information(this, "Exception caught", QString::fromStdString(e.what()));
			}

			input.close();
		}




	}catch (std::string s) {
		QMessageBox::information(this, "Problem", QString::fromStdString(s));}

	v3dw->updateGL();
}





bool VisualSimulation::getMappedAction(QKeyEvent* event, KeyAction& action) {

	map<int, KeyAction>::iterator it = keyActionMap.find(event->key()); // Find the action corresponding to this key press. 

	if (it != keyActionMap.end()) { 
		action = it->second;
		return true;
	} else {
		return false;
	}

}

int VisualSimulation::findBindedKey(KeyAction const& a) {
	for (auto& it : keyActionMap) {
		if (it.second==a) {
			return it.first;
		}
	}
	throw string("VisualSimulation::findBindedKey(...)  action doesn't have any key binding");
}

void VisualSimulation::refreshCurKeyLabels() {
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


void VisualSimulation::keyPressEvent(QKeyEvent* event) {
	if (nextKeyPressSetsAction) {
		nextKeyPressSetsAction = false;

		map<int, KeyAction>::iterator it = keyActionMap.find(event->key());

		if (it == keyActionMap.end()) {
			// The key is not already attributed to other action. Good, so attribute it to this action.
			bool valueNotYetFound (true);
			for (map<int, KeyAction>::iterator it=keyActionMap.begin(); it!=keyActionMap.end() && valueNotYetFound; ++it) {
				if (it->second==actionToSet) {
					keyActionMap.erase(it);
					valueNotYetFound = false;
				}
			}
			keyActionMap[event->key()] = actionToSet;

			// *** (while nextKeyPressSetsAction change the text of label or button to say that you are waiting for a keypress)

			refreshCurKeyLabels();

		} else {
			// *** dialogue box or error msg saying that this key is already attributed.
		}

	}
}

const Vector3 VisualSimulation::getFrisbeePosition() const {
	return sys->getFrisbeePosition();
}





// void VisualSimulation::set_Euler(){
//     if (integ->get_type() != Euler) {
//         delete integ;
//         integ = new IntegrateurEuler;}
//     }

// void VisualSimulation::set_Newmark(){
//     if (integ->get_type() != Newmark){
//         delete integ;
//         integ = new IntegrateurNewmark;}
//     }

void VisualSimulation::setRK4(){
	if (integ->getType() != RungeKutta) {
		delete integ;
		integ = new IntegratorRK4;
	}
}


void VisualSimulation::toggleTime() {
	if (timerId == 0) { // In this case, the timer is not running, so start it.
		timerId = startTimer(20);
		chronometer.restart();
	} else { // The timer is running so stop it.
		killTimer(timerId);
		timerId = 0;
	}
}

double VisualSimulation::getCurrentTime() {
		return sys->time();
}


void VisualSimulation::resetTime() {
	sys->resetTime();
}

void VisualSimulation::stop() {
	if (timerId != 0) {
		killTimer(timerId);
		timerId = 0;
	}
}

void VisualSimulation::timerEvent(QTimerEvent* event) {
	Q_UNUSED(event);

	double dt = chronometer.restart()/1000.;

	// playbackSpeed = 50 means normal playack speed.

	if (playbackSpeed < 50) { // 0 < playbackSpeed < 50 means slower than normal, so make smaller time steps.
			double coef (playbackSpeed/50.); // Linear function of playbackSpeed, passes through (0,0) and (50,1).
			sys->evolve(*integ, dt*coef); 
	}
	else { // 50 < playbackSpeed < 100 means faster than normal. Warning, big time steps cause errors, so make multiple smaller time steps.
		double coef (playbackSpeed*(5./50.)-4.); // Linear function of playbackSpeed, passes through (50,1) and (100,6). This means that at maximal "playbackSpeed=100" the simulation is 6 times normal speed.
		int nbLoops (coef);
		if (playbackSpeed!=50) ++nbLoops;     // "nbLoops" is the integer greater than "coef".
		//cerr << coef << " " << nbLoops << endl;
		for (int i(0); i<nbLoops; ++i ) {
				sys->evolve(*integ, dt*coef/nbLoops); // coef/nbLoops<=1, so all time steps are smaller or equal to dt.
		}
	}

	if (frisbeeTrackingCameraMode) {
		v3dw->lookAt(sys);
	}

	v3dw->updateGL();
}



void VisualSimulation::closeEvent(QCloseEvent* event) {
	cerr << "VisualSimulation::closeEvent(QCloseEvent* event)" << endl;
	parent->visualSimulationIsClosing();
	event->accept();
}


void VisualSimulation::setPlaybackSpeed(int a){
	 playbackSpeed = a;
	 cerr << a << endl;
}

