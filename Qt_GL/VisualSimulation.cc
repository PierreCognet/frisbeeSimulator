#include "MainWindow.h"
#include "VisualSimulation.h"
#include "Visual3DWindow.h"
#include "InfoWindow.h"
// #include <QString>

#include "Integrator.h"
// #include "IntegratorEuler.h"
// #include "IntegratorNewmark.h"
#include "IntegratorRK4.h"

// #include "OpenGLViewer.h"
// #include <QFileDialog>
#include <fstream>


// VisualSimulation::VisualSimulation(QWidget *parent, MainWindow* mw) : QWidget(parent), parent(mw) { // ***** deleted
// VisualSimulation::VisualSimulation(QWidget *parent, MainWindow* mw) : QWidget(parent), parent(mw), kam() { // ***** added
VisualSimulation::VisualSimulation(QWidget *parent, MainWindow* mw) : KeyActionWindow(parent, mw) {


	setWindowTitle("Visual Simulation");
	//setFixedSize(700, 500);
	setGeometry(0, 0 , 700, 500); // *** do something


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



	resetTimeButton = new QPushButton ("Reinitialize time");

	integratorGrid = new QGridLayout;
	integratorLabel = new QLabel("Change integrator:");
	// boutonIntegrateurEuler = new QPushButton("Euler");
	// boutonIntegrateurNewmark = new QPushButton("Newmark");
	rk4Button = new QPushButton("RungeKutta");

	resetTimeButton->setFixedSize(200,80);

	integratorGrid->addWidget(resetTimeButton, 1, 1, 1, 1);
	integratorGrid->addWidget(integratorLabel, 2, 1, 2, 1);
	// integratorGrid->addWidget(boutonIntegrateurEuler, 3, 0);
	// integratorGrid->addWidget(boutonIntegrateurNewmark, 3, 1);
	integratorGrid->addWidget(rk4Button, 3, 2);

	timeGrid->addLayout(integratorGrid, 4, 0, 3, 1);

	timePage->setLayout(timeGrid);



	// savePage = new QWidget;
	// saveGrid = new QGridLayout;

	// saveStateButton = new QPushButton("Save current state");
	// selectStateFileDialogButton = new QPushButton("Select file location");
	// saveStateFileNameLabel = new QLabel("");
	loadStateButton = new QPushButton("Load state from file");
	selectLoadStateFileDialogButton = new QPushButton("Select file location");
	loadStateFileNameLabel = new QLabel("");

	// saveGrid->addWidget(saveStateButton, 1, 1, 1, 2);
	// saveGrid->addWidget(selectStateFileDialogButton, 2, 1);
    // saveGrid->addWidget(saveStateFileNameLabel, 2, 2);
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


	// v3dw = new Visual3DWindow(this); 
	// v3dw->setWindowFlags(Qt::Dialog | Qt::WindowTitleHint);
	// v3dw->setGeometry(1100 , 0, 1200 , 1055);
	// v3dw->show();

	// sys = new System(v3dw->getView());
	integ = new IntegratorRK4; // RK4 by default.
	// timerId = 0;
	// playbackSpeed = 50; // To change the speed at which time flows (multiplier).
	// frisbeeTrackingCameraMode = false;



	infoWin = new InfoWindow(this); // **** added
	// infoWin = new InfoWindow(this, sys, integ);  // **** deleted
	// infoWin = new InfoWindow(this, this);
	infoWin->setWindowFlags(Qt::Dialog | Qt::WindowTitleHint);
	// infoWin->refreshLabels(sys, integ); // **** added
	infoWin->refreshLabels(sys); // **** added
	infoWin->show();


	// Must connect buttons here, so that they live in the whole class.
    QObject::connect(setFrisbeeStateButton, SIGNAL(clicked()), this, SLOT(setFrisbeeState()));
    QObject::connect(toggleUvwBodyEarthAxesButton, SIGNAL(clicked()), this, SLOT(toggleUvwBodyEarthAxes()));

	// QObject::connect(startStopButton, SIGNAL(clicked()), this, SLOT(toggleTime()));

	// QObject::connect(zButton, SIGNAL(clicked()), v3dw, SLOT(setcamZ()));
	// QObject::connect(zzButton, SIGNAL(clicked()), v3dw, SLOT(setcamZZ()));
	// QObject::connect(xButton, SIGNAL(clicked()), v3dw, SLOT(setcamX()));
	// QObject::connect(xxButton, SIGNAL(clicked()), v3dw, SLOT(setcamXX()));
	// QObject::connect(yButton, SIGNAL(clicked()), v3dw, SLOT(setcamY()));
	// QObject::connect(yyButton, SIGNAL(clicked()), v3dw, SLOT(setcamYY()));
	// QObject::connect(toggleFrisbeeTrackingCameraModeButton, SIGNAL(clicked()), this, SLOT(toggleFrisbeeTrackingCameraMode()));

	
	// QObject::connect(boutonIntegrateurEuler, SIGNAL(clicked()), this , SLOT(set_Euler()));
	// QObject::connect(boutonIntegrateurNewmark, SIGNAL(clicked()), this, SLOT(set_Newmark()));
	QObject::connect(rk4Button, SIGNAL(clicked()), this, SLOT(setRK4()));
	
	// QObject::connect(playbackSpeedSlider, SIGNAL(valueChanged(int)), this, SLOT(setPlaybackSpeed(int)) );
	
	QObject::connect(resetTimeButton, SIGNAL(clicked()), this, SLOT(resetTime()));
	
	// QObject::connect(pitchUpSetButton, SIGNAL(clicked()), this, SLOT(pitchUpSetNew()));
	// QObject::connect(pitchDownSetButton, SIGNAL(clicked()), this, SLOT(pitchDownSetNew()));
	// QObject::connect(yawLeftSetButton, SIGNAL(clicked()), this, SLOT(yawLeftSetNew()));
	// QObject::connect(yawRightSetButton, SIGNAL(clicked()), this, SLOT(yawRightSetNew()));
	// QObject::connect(rollLeftSetButton, SIGNAL(clicked()), this, SLOT(rollLeftSetNew()));
	// QObject::connect(rollRightSetButton, SIGNAL(clicked()), this, SLOT(rollRightSetNew()));
	// QObject::connect(moveUpSetButton, SIGNAL(clicked()), this, SLOT(moveUpSetNew()));
	// QObject::connect(moveDownSetButton, SIGNAL(clicked()), this, SLOT(moveDownSetNew()));
	// QObject::connect(moveLeftSetButton, SIGNAL(clicked()), this, SLOT(moveLeftSetNew()));
	// QObject::connect(moveRightSetButton, SIGNAL(clicked()), this, SLOT(moveRightSetNew()));
	// QObject::connect(moveForwardSetButton, SIGNAL(clicked()), this, SLOT(moveForwardSetNew()));
	// QObject::connect(moveBackwardSetButton, SIGNAL(clicked()), this, SLOT(moveBackwardSetNew()));
	// QObject::connect(resetPositionSetButton, SIGNAL(clicked()), this, SLOT(resetPositionSetNew()));
	// QObject::connect(startStopTimeSetButton, SIGNAL(clicked()), this, SLOT(startStopTimeSetNew()));

	// QObject::connect(selectStateFileDialogButton, SIGNAL(clicked()), this, SLOT(selectSaveCurrentStateFile()));
	// QObject::connect(saveStateButton, SIGNAL(clicked()), this, SLOT(saveCurrentState()));
	QObject::connect(selectLoadStateFileDialogButton, SIGNAL(clicked()), this, SLOT(selectLoadStateFile()));
	QObject::connect(loadStateButton, SIGNAL(clicked()), this, SLOT(loadState()));
}


VisualSimulation::~VisualSimulation() { 
	cerr << "VisualSimulation::~VisualSimulation()" << endl;
	delete integ;
	// delete sys;
	// v3dw->deleteLater();
	// infoWin->deleteLater();
}


void VisualSimulation::visual3DWindowKeyPressEvent(QKeyEvent* event) {

	KeyAction action;
	if (getMappedAction(event, action)) {

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
			throw string("VisualSimulation::visual3DWindowKeyPressEvent(...)  unknown action");
		}
		v3dw->updateGL();
	}
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
		// infoWin->refreshLabels(sys, integ); // **** added
		infoWin->refreshLabels(sys); // **** integ ?

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
	// infoWin->refreshLabels(sys, integ); // **** added
	infoWin->refreshLabels(sys); // **** added
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


void VisualSimulation::resetTime() {
	sys->resetTime();
	infoWin->refreshLabels(sys);
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
	// infoWin->refreshLabels(sys, integ); // **** added
	infoWin->refreshLabels(sys); // **** added
}



void VisualSimulation::closeEvent(QCloseEvent* event) {
	cerr << "VisualSimulation::closeEvent(QCloseEvent* event)" << endl;
	parent->visualSimulationIsClosing();
	event->accept();
}





