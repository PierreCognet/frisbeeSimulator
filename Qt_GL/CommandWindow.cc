#include "CommandWindow.h"
#include "GLWidget.h"
#include "InfoWindow.h"
#include <QString>
#include "Integrator.h"
// #include "IntegrateurEuler.h"
#include "OpenGLViewer.h"


CommandWindow::CommandWindow(QWidget *parent) : QWidget(parent) {

	setWindowTitle("Frisbee Simulation");
	//setFixedSize(700, 500);
	setGeometry(0, 0 , 700, 500);


	// First widget child.

	tabs = new QTabWidget(this);
	tabs->setGeometry(0, 5, 700, 495);


	// Declare Widgets.

	masterPage = new QWidget;
	frisbeePage = new QWidget;
	timePage = new QWidget;
	cameraPage = new QWidget;
	keyboardPage = new QWidget;
	
	stopButton = new QPushButton("Stop simulation");
	startButton = new QPushButton("Start simulation");


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

	startStopButton = new QPushButton("Start/stop");
	playbackSpeedSlider = new QSlider(Qt::Horizontal);

	zButton = new QPushButton("Z plus");
	zzButton = new QPushButton("Z minus");
	xButton = new QPushButton("X plus");
	xxButton = new QPushButton("X minus");
	yButton = new QPushButton("Y plus");
	yyButton = new QPushButton("Y minus");
	camPositionTitle = new QLabel ("Change camera position");
	// boutonCDM = new QPushButton ("CDM"); Set camera on frisbee ?
	

	// boutonTri = new QPushButton ("Activer/Désactiver Triangles");
	// boutonSpring = new QPushButton("Activer/Désactiver Ressorts");
	// boutonMass = new QPushButton("Activer/Désactiver Masses");
	
	resetTimeButton = new QPushButton ("Reinitialize time");
	// boutonIntegrateurEuler = new QPushButton("Euler");
	// boutonIntegrateurNewmark = new QPushButton("Newmark");
	rk4Button = new QPushButton("RungeKutta");

	//boutonOK = new QPushButton ("OK");
	
	// ChoixT = new QWidget;
	// ChoixC = new QWidget;
	// Del_Tissu =new QPushButton("Supprime le dernier Tissu");
	// Del_Contr =new QPushButton ("Supprime la dernière contrainte");
	
	// nomF = new QLabel ("nom du fichier");
	// save = new QPushButton("Sauvegarder");
	// load = new QPushButton("Charger");
	// filename = new QLineEdit();    
	// infofile = new QLabel("Entrez le nom du fichier sans l'extension , pas de '.dat'");
	
	playbackSpeedLabel = new QLabel("Vary speed:");
	

	// ClearTT = new QPushButton("Réinitialise le Système");
	integratorLabel = new QLabel("Change integrator:");
	// ToggleContr = new QPushButton("Activer/Desactiver Contraintes");
	// ToggleCass = new QPushButton("Activer/Desactiver casse ressorts");




	// Grids to position widgets.

	masterGrid = new QGridLayout;
	masterGrid->addWidget(stopButton, 2, 1, 2, 1);
	masterGrid->addWidget(startButton, 1, 1, 2, 1);
	// masterGrid->addWidget(ClearTT , 3 , 1 , 2, 1);

	frisbeeGrid = new QGridLayout;
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

	integratorGrid = new QGridLayout;
	integratorGrid->addWidget(resetTimeButton, 1, 1, 1, 1);
	integratorGrid->addWidget(integratorLabel, 2, 1, 2, 1);
	// integratorGrid->addWidget(boutonIntegrateurEuler, 3, 0);
	// integratorGrid->addWidget(boutonIntegrateurNewmark, 3, 1);
	integratorGrid->addWidget(rk4Button, 3, 2);


	timeGrid = new QGridLayout;
	timeGrid->addWidget(startStopButton, 1, 0);
	timeGrid->addWidget(playbackSpeedLabel, 2, 0);
	timeGrid->addLayout(integratorGrid, 4, 0, 3, 1);
	timeGrid->addWidget(playbackSpeedSlider, 3, 0);


	cameraGrid = new QGridLayout;
	//cameraGrid->addWidget(boutonCDM,3,1);
	cameraGrid->addWidget(camPositionTitle, 0, 1);
	cameraGrid->addWidget(zButton, 2, 1);
	cameraGrid->addWidget(zzButton, 4, 1);
	cameraGrid->addWidget(xButton, 1, 1);
	cameraGrid->addWidget(xxButton, 5, 1);
	cameraGrid->addWidget(yButton, 3, 0);
	cameraGrid->addWidget(yyButton, 3, 2);


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

	nextKeyPressSetsAction = false;
	// actionToSet = null;

	// vector<string> actionNames ({ "Pitch up", "Pitch down", "Yaw left", "Yaw right", "Roll left", "Roll right", "Move up", "Move down", "Move left", "Move right", "Move forwards", "Move backwards", "Reset position", "Toggle time" });
	// for (const auto action : KeyAction::All) {

	// 	actionLabels.push_back(new QLabel(actionNames[action])); // *** std:: ?
	// 	currentKeyLabels.push_back(new QLabel(findBindedKey(action))) *** findBindedKey implement
	// 	setNewKeyButtons.push_back(new QPushButton("Set new key")); // *** std:: ?

	//     keyboardGrid->addWidget(keyActionLabels[action], 2+action, 1);
	//     keyboardGrid->addWidget(currentKeyLabels[action], 2+action, 2);
	//     keyboardGrid->addWidget(setNewKeyButtons[action], 2+action, 3);
	// }




	// box4 = new QGridLayout;
	// box4->addWidget(boutonMass , 1 , 0);
	// box4->addWidget(boutonSpring , 2 , 0);
	// box4->addWidget(boutonTri , 3 , 0 );
	// box4->addWidget(ToggleContr ,4 , 0 );


	// ChoixTissu = new QGridLayout;
	// ChoixT->setLayout(ChoixTissu);
	// ChoixContraintes = new QGridLayout;
	// ChoixC->setLayout(ChoixContraintes);


	// box7 = new QGridLayout;

	// box5 = new QGridLayout;
	// box5->addWidget(TypeTissu , 0 , 0 );
	// box5->addWidget(Del_Tissu , 1 , 0);
	// box7->addWidget(Del_Contr, 1 , 1);
	//box5->addWidget(boutonOK , 0 , 1);
	// box5->addWidget(ChoixT, 2 , 0 );
	// box5->addWidget(ToggleCass , 3 , 0);
	// box7->addWidget(TypeContraintes , 0 , 1);
	// box7->addWidget(ChoixC , 2 , 1);


	// fileSaveLoadGrid = new QGridLayout;
	// fileSaveLoadGrid->addWidget(infofile , 4,0);
	// fileSaveLoadGrid->addWidget(nomF , 0 , 0);
	// fileSaveLoadGrid->addWidget(save , 2, 1);
	// fileSaveLoadGrid->addWidget(load , 3 , 1);
	// fileSaveLoadGrid->addWidget(filename , 0 , 1);

	// QObject::connect(save , SIGNAL(clicked()), this , SLOT(saveFile()));
	// QObject::connect(load , SIGNAL(clicked()), this , SLOT(loadFile()));




	// Modify objects.

	
	startButton->setFixedHeight(120);
	stopButton->setFixedHeight(120);
	

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


	startStopButton->setFixedHeight(120);
	playbackSpeedSlider->setValue(50);
	playbackSpeedSlider->setRange(1, 100);
	resetTimeButton->setFixedSize(200,80);

	zButton->setFixedSize(200,100);
	zzButton->setFixedSize(200,100);
	xButton->setFixedSize(200,100);
	xxButton->setFixedSize(200,100);
	yButton->setFixedSize(200,100);
	yyButton->setFixedSize(200,100);
	camPositionTitle->setAutoFillBackground(true);

	// ClearTT->setFixedHeight(60);

	// boutonMass->setFixedSize(450 , 100);
	// boutonSpring->setFixedSize(450 , 100);
	// boutonTri->setFixedSize(450 , 100);
	// ToggleContr->setFixedSize(450, 100);

	// filename->setSizeIncrement(100 , 30);

	// TypeTissu->addItem("Chaîne");
	// TypeTissu->addItem("Carré");
	// TypeTissu->addItem("Carré2");
	// TypeTissu->addItem("Hexagone");
	// TypeTissu->addItem("Disque");
	// TypeTissu->addItem("Rectangle");
	// TypeTissu->addItem("Libre");
	// TypeTissu->addItem("TissuComposé");


	// TypeContraintes->addItem("Crochet");
	// TypeContraintes->addItem("Impulsion");
	// TypeContraintes->addItem("Impulsion sinusoidale");
	// TypeContraintes->addItem("Lévitateur");
	// TypeContraintes->addItem("Boule Rigide");
	// TypeContraintes->addItem("Trou Noir");



	// Fill the layouts with objects.

	masterPage->setLayout(masterGrid);
	frisbeePage->setLayout(frisbeeGrid);
	timePage->setLayout(timeGrid);
	cameraPage->setLayout(cameraGrid);
	keyboardPage->setLayout(keyboardGrid);


	// Fill the tabs.

	tabs->addTab(masterPage, "Command Window");
	tabs->addTab(frisbeePage, "Frisbee");
	tabs->addTab(timePage, " Time");
	tabs->addTab(cameraPage, " Camera");
	tabs->addTab(keyboardPage, " Keyboard Bindings");




	// Connect buttons to slots (not directly linked to w).

	QObject::connect(startButton, SIGNAL(clicked()), this, SLOT(simulate()));

	// // QObject::connect(boutonOK , SIGNAL(clicked()), this , SLOT(choix_tissu()));
	// QObject::connect(TypeTissu , SIGNAL(currentIndexChanged(int)), this , SLOT(choix_tissu(int)));
	// QObject::connect(TypeContraintes , SIGNAL(currentIndexChanged(int)), this , SLOT(choix_Contraintes(int)));







	// All that is linked to w.

	// Create/set parameter of OpenGL window.
	w = new GLWidget(RungeKutta, this); // RK4 by default.
	w->setWindowFlags(Qt::Dialog | Qt::WindowTitleHint);
	w->setGeometry(1100 , 0, 1200 , 1055 );


	// Frist create information window (+ parameters).
	infoWin = new InfoWindow(this, w);
	infoWin->setWindowFlags(Qt::Dialog | Qt::WindowTitleHint);


	// Must connect buttons here, so that they live in the whole class.
	QObject::connect(stopButton, SIGNAL(clicked()), w, SLOT(close()));
	QObject::connect(stopButton, SIGNAL(clicked()), infoWin, SLOT(close()));

    QObject::connect(setFrisbeeStateButton, SIGNAL(clicked()), this, SLOT(setFrisbeeState()));
    QObject::connect(toggleUvwBodyEarthAxesButton, SIGNAL(clicked()), this, SLOT(toggleUvwBodyEarthAxes()));

	QObject::connect(startStopButton, SIGNAL(clicked()), w, SLOT(toggleTime()));

	QObject::connect(zButton, SIGNAL(clicked()), w, SLOT(setcamZ()));
	QObject::connect(zzButton, SIGNAL(clicked()), w, SLOT(setcamZZ()));
	QObject::connect(xButton, SIGNAL(clicked()), w, SLOT(setcamX()));
	QObject::connect(xxButton, SIGNAL(clicked()), w, SLOT(setcamXX()));
	QObject::connect(yButton, SIGNAL(clicked()), w, SLOT(setcamY()));
	QObject::connect(yyButton, SIGNAL(clicked()), w, SLOT(setcamYY()));

	// QObject::connect(boutonMass ,SIGNAL(clicked()) , w , SLOT(toggle_Mass()));
	// QObject::connect(boutonSpring ,SIGNAL(clicked()) , w , SLOT(toggle_springs()));
	// QObject::connect(boutonTri ,SIGNAL(clicked()) , w , SLOT(toggle_tri()));
	
	// QObject::connect(boutonIntegrateurEuler ,SIGNAL(clicked()) , w , SLOT(set_Euler()));
	// QObject::connect(boutonIntegrateurNewmark ,SIGNAL(clicked()) , w , SLOT(set_Newmark()));
	QObject::connect(rk4Button, SIGNAL(clicked()), w ,SLOT(setRK4()));
	
	QObject::connect(playbackSpeedSlider, SIGNAL(valueChanged(int)), w, SLOT(setPlaybackSpeed(int)) );
	
	// QObject::connect(boutonCDM ,SIGNAL(clicked(bool)) , w , SLOT(setcamCDM()));7  // *** set camera of frisbee ?

	// QObject::connect(Del_Tissu, SIGNAL(clicked()), w ,SLOT(delete_last_tissu()));
	// QObject::connect(Del_Contr, SIGNAL(clicked()), w ,SLOT(delete_last_contrainte()));

	QObject::connect(resetTimeButton, SIGNAL(clicked()), w ,SLOT(resetTime()));
	

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

	// QObject::connect(ClearTT , SIGNAL(clicked()), w , SLOT(clear_tissu()));
	// QObject::connect(ToggleContr, SIGNAL(clicked()) , w , SLOT (Toggle_Contr()));
	// QObject::connect(ToggleCass, SIGNAL(clicked()) , w , SLOT (Toggle_Cassures()));

	// choix_tissu(0);
	// choix_Contraintes(0);

}



void CommandWindow::setFrisbeeState() {
	try {
    	w->setFrisbeeState(Vector3(xSpinBox->value(), ySpinBox->value(), zSpinBox->value()),
    						Vector3(phiSpinBox->value(), thetaSpinBox->value(), psiSpinBox->value()),
    						Vector3(uSpinBox->value(), vSpinBox->value(), wSpinBox->value()),
    						Vector3(pSpinBox->value(), qSpinBox->value(), rSpinBox->value()),
    						uvwIsBodyNotEarthAxes);
    	w->coutSystem();
    }catch (std::string s) {
        QMessageBox::information(this, "Problem", QString::fromStdString(s));
    }
}

void CommandWindow::toggleUvwBodyEarthAxes() {
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

void CommandWindow::pitchUpSetNew() {
	nextKeyPressSetsAction = true;
	// setNewKeyTitleLabel->Focus();	
	actionToSet = pitchUp;
}

void CommandWindow::pitchDownSetNew() {
	nextKeyPressSetsAction = true;
	// setNewKeyTitleLabel->Focus();	
	actionToSet = pitchDown;
}

void CommandWindow::yawLeftSetNew() {
	nextKeyPressSetsAction = true;
	// setNewKeyTitleLabel->Focus();	
	actionToSet = yawLeft;
}

void CommandWindow::yawRightSetNew() {
	nextKeyPressSetsAction = true;
	// setNewKeyTitleLabel->Focus();	
	actionToSet = yawRight;
}

void CommandWindow::rollLeftSetNew() {
	nextKeyPressSetsAction = true;
	// setNewKeyTitleLabel->Focus();	
	actionToSet = rollLeft;
}

void CommandWindow::rollRightSetNew() {
	nextKeyPressSetsAction = true;
	// setNewKeyTitleLabel->Focus();	
	actionToSet = rollRight;
}

void CommandWindow::moveUpSetNew() {
	nextKeyPressSetsAction = true;
	// setNewKeyTitleLabel->Focus();	
	actionToSet = moveUp;
}

void CommandWindow::moveDownSetNew() {
	nextKeyPressSetsAction = true;
	// setNewKeyTitleLabel->Focus();	
	actionToSet = moveDown;
}

void CommandWindow::moveLeftSetNew() {
	nextKeyPressSetsAction = true;
	// setNewKeyTitleLabel->Focus();	
	actionToSet = moveLeft;
}

void CommandWindow::moveRightSetNew() {
	nextKeyPressSetsAction = true;
	// setNewKeyTitleLabel->Focus();	
	actionToSet = moveRight;
}

void CommandWindow::moveForwardSetNew() {
	nextKeyPressSetsAction = true;
	// setNewKeyTitleLabel->Focus();	
	actionToSet = moveForward;
}

void CommandWindow::moveBackwardSetNew() {
	nextKeyPressSetsAction = true;
	// setNewKeyTitleLabel->Focus();	
	actionToSet = moveBackward;
}

void CommandWindow::resetPositionSetNew() {
	nextKeyPressSetsAction = true;
	// setNewKeyTitleLabel->Focus();	
	actionToSet = resetPosition;
}

void CommandWindow::startStopTimeSetNew() {
	nextKeyPressSetsAction = true;
	// setNewKeyTitleLabel->Focus();	
	actionToSet = startStopTime;
}



bool CommandWindow::getMappedAction(QKeyEvent* event, KeyAction& action) {

	map<int, KeyAction>::iterator it = keyActionMap.find(event->key()); // Find the action corresponding to this key press. 

	if (it != keyActionMap.end()) { 
		action = it->second;
		return true;
	} else {
		return false;
	}

}

int CommandWindow::findBindedKey(KeyAction const& a) {
	for (auto& it : keyActionMap) {
		if (it.second==a) {
			return it.first;
		}
	}
	throw string("CommandWindow::findBindedKey(...)  action doesn't have any key binding");
}

void CommandWindow::refreshCurKeyLabels() {
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


void CommandWindow::keyPressEvent(QKeyEvent* event) {
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


//==============SLots poyur la creation=================================================


// void CommandWindow::createTissuDisque() { try {
//     w->create_tissuDisque( MasseGet->value()
//                            ,Vecteur3D (VecXGet1->value(),VecYGet1->value(), VecZGet1->value())
//                            ,Vecteur3D (VecXGet->value(),VecYGet->value(), VecZGet->value())
//                            ,PasRadialGet->value()
//                            ,LambdaGet->value()
//                            ,KGet->value()
//                            ,PasAngulaireGet->value()  );
//     }catch (std::string s) {
//         QMessageBox::information(this, "Problem", QString::fromStdString(s));
//     }
// }


// void CommandWindow::Add_Masse(){
// 	try {
// 	 Masses.push_back(Masse(MasseGet->value(),Vecteur3D(VecXGet->value(),VecYGet->value(),VecZGet->value()), Vecteur3D(VecXGet1->value(),VecYGet1->value(),VecZGet1->value()),LambdaGet->value() ,nullptr));
// 	}catch (std::string s) {
// 		QMessageBox::information(this, "Problem", QString::fromStdString(s));
// 	quit();}
// }

// void CommandWindow::Add_Liason(){
// 	try {
// 	Liasons.push_back(Liaison(massedep->value(),{massearr->value()},KGet->value(),loGet->value()));
// 	}catch (std::string s) {
// 		QMessageBox::information(this, "Problem", QString::fromStdString(s));
// 	quit();}
// }

// void CommandWindow::tissuLibre(){
// 	try {

// 	w->create_tissu(Masses , Liasons);

// 	}catch (std::string s) {
// 		QMessageBox::information(this, "Problem", QString::fromStdString(s));}

// 	Masses.clear();
// 	Liasons.clear();

// 	delete PopUp;
// }

// void CommandWindow::saveFile(){
//     try {
//     w->sauvegarderFichier((filename->text()).toStdString());
//     }catch (std::string s) {
//         QMessageBox::information(this, "Problem", QString::fromStdString(s));}
//     w->updateGL();
// }

// void CommandWindow::loadFile(){
//     try {
//     w->chargerFichier((filename->text().toStdString()));
//     }catch (std::string s) {
//         QMessageBox::information(this, "Problem", QString::fromStdString(s));}
//     w->updateGL();
// }

// void CommandWindow::quit(){
// 	Masses.clear();
// 	Liasons.clear();

// 	delete PopUp;

// }

// void CommandWindow::quit2(){

// 	for ( auto& el : Tissus) {delete el;}
// 	Tissus.clear();
// 	delete PopUp;
// 	// ChoixT = new QWidget;
// 	// ChoixTissu = new QGridLayout;
// 	// choix_tissu(7);


// }


//===============Creation des champs Variables pour les tissus==========================


// void CommandWindow::tissuDisque(){



//     QLabel* Rnormal = new QLabel ("Rayon Normal",ChoixT);

//     QLabel* PasRad = new QLabel ("Pas Radial",ChoixT);
//     QLabel* PasAng = new QLabel ("Pas Angulaire",ChoixT);


//     PasAngulaireGet = new QDoubleSpinBox(ChoixT);
//     PasRadialGet = new QDoubleSpinBox(ChoixT);
//     PasAngulaireGet->setRange(1 , 360);
//     PasRadialGet->setRange(1,1000);
//     PasAngulaireGet->setValue(20);

//     VecXGet = new QDoubleSpinBox (ChoixT);
//     VecYGet = new QDoubleSpinBox (ChoixT);
//     VecZGet = new QDoubleSpinBox (ChoixT);

//     VecXGet->setRange(-1000 , 1000);
//     VecYGet->setRange(-1000 , 1000);
//     VecZGet->setRange(-1000 , 1000);
//     VecZGet->setValue(1);




//     create = new QPushButton ("Créer le Tissu",ChoixT);


//     ChoixTissu->addWidget(Rnormal , 5 ,0);
//     ChoixTissu->addWidget(VecXGet , 5 , 1 );
//     ChoixTissu->addWidget(VecYGet , 5 , 2 );
//     ChoixTissu->addWidget(VecZGet , 5 , 3 );
//     ChoixTissu->addWidget(PasRad , 7, 0 );
//     ChoixTissu->addWidget(PasAng , 8 , 0 );
//     ChoixTissu->addWidget(PasRadialGet , 7, 1 );
//     ChoixTissu->addWidget(PasAngulaireGet , 8 , 1);
//     ChoixTissu->addWidget(create , 9 , 0);

//     QObject::connect(create , SIGNAL(clicked()), this , SLOT(createTissuDisque()));

// }


void CommandWindow::simulate() {
	infoWin->show();
	w->show();
}
