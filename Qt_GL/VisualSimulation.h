#ifndef PRJ_VISUALSIMULATION_H
#define PRJ_VISUALSIMULATION_H

// #include <QtWidgets>
// #include <QGridLayout>
// #include <QTime>
// #include "MainWindow.h"
#include "KeyActionWindow.h"
// #include "Visual3DWindow.h"
// #include "InfoWindow.h"
// #include "KeyActionMapper.h" // ***** added
// #include <map> // ***** deleted

// class MainWindow;
// class KeyActionWindow;
class Integrator;



class VisualSimulation : public KeyActionWindow  { // ***** make it a subclass

Q_OBJECT

public :

	VisualSimulation (QWidget* parent, MainWindow* mw);
	virtual ~VisualSimulation();  // Delete dyamically allocated system and integrator.
	
	virtual void visual3DWindowKeyPressEvent(QKeyEvent* event) override;

	// IntegratorType getIntegratorType() { return integ->getType(); }

private slots :

	void setFrisbeeState();
	void toggleUvwBodyEarthAxes();

	void selectLoadStateFile();
	void loadState();

	// void set_Euler();
	// void set_Newmark();	
	void setRK4();
	void resetTime();


private :

	virtual void timerEvent(QTimerEvent* event)  override;
	void closeEvent(QCloseEvent* event);


	// QTabWidget *tabs;



	QWidget* frisbeePage;
	QGridLayout* frisbeeGrid;

	QDoubleSpinBox* xSpinBox;
	QDoubleSpinBox* ySpinBox;
	QDoubleSpinBox* zSpinBox;
	QDoubleSpinBox* phiSpinBox;
	QDoubleSpinBox* thetaSpinBox;
	QDoubleSpinBox* psiSpinBox;
	QDoubleSpinBox* uSpinBox;
	QDoubleSpinBox* vSpinBox;
	QDoubleSpinBox* wSpinBox;
	QDoubleSpinBox* pSpinBox;
	QDoubleSpinBox* qSpinBox;
	QDoubleSpinBox* rSpinBox;

	QLabel* xLabel;
	QLabel* yLabel;
	QLabel* zLabel;
	QLabel* phiLabel;
	QLabel* thetaLabel;
	QLabel* psiLabel;
	QLabel* uLabel;
	QLabel* vLabel;
	QLabel* wLabel;
	QLabel* pLabel;
	QLabel* qLabel;
	QLabel* rLabel;

	QPushButton* setFrisbeeStateButton;
	QPushButton* toggleUvwBodyEarthAxesButton;
	bool uvwIsBodyNotEarthAxes;



	QPushButton* resetTimeButton;

	QGridLayout* integratorGrid;
	QLabel* integratorLabel;
	// QPushButton *boutonIntegrateurEuler;
	// QPushButton *boutonIntegrateurNewmark;
	QPushButton* rk4Button;



	// QWidget* cameraPage;
	// QGridLayout* cameraGrid;

	// QLabel* camPositionTitle;
	// QPushButton* zButton;
	// QPushButton* zzButton;
	// QPushButton* xButton;
	// QPushButton* xxButton;
	// QPushButton* yButton;
	// QPushButton* yyButton;
	// QPushButton* toggleFrisbeeTrackingCameraModeButton;
	


	// QWidget* keyboardPage;
	// QGridLayout* keyboardGrid;

	// // std::map<int, KeyAction> keyActionMap; // For each key, maps to the corresponding action. Would be cleaner to use Qt::Key, as key type. // ***** deleted
	// KeyActionMapper kam; // For each key, maps to the corresponding action. Would be cleaner to use Qt::Key, as key type. // ***** added
    // QLabel* actionTitleLabel;
    // QLabel* currentKeyTitleLabel;
    // QLabel* setNewKeyTitleLabel;
	// // vector<QLabel*> actionLabels; // std:: ?
	// // vector<QLabel*> currentKeyLabels; // std:: ?
	// // vector<QPushButton*> setNewKeyButtons; // std:: ?

	// QLabel* pitchUpLabel;
	// QLabel* pitchDownLabel;
	// QLabel* yawLeftLabel;
	// QLabel* yawRightLabel;
	// QLabel* rollLeftLabel;
	// QLabel* rollRightLabel;
	// QLabel* moveUpLabel;
	// QLabel* moveDownLabel;
	// QLabel* moveLeftLabel;
	// QLabel* moveRightLabel;
	// QLabel* moveForwardLabel;
	// QLabel* moveBackwardLabel;
	// QLabel* resetPositionLabel;
	// QLabel* startStopTimeLabel;

	// QLabel* pitchUpCurKeyLabel;
	// QLabel* pitchDownCurKeyLabel;
	// QLabel* yawLeftCurKeyLabel;
	// QLabel* yawRightCurKeyLabel;
	// QLabel* rollLeftCurKeyLabel;
	// QLabel* rollRightCurKeyLabel;
	// QLabel* moveUpCurKeyLabel;
	// QLabel* moveDownCurKeyLabel;
	// QLabel* moveLeftCurKeyLabel;
	// QLabel* moveRightCurKeyLabel;
	// QLabel* moveForwardCurKeyLabel;
	// QLabel* moveBackwardCurKeyLabel;
	// QLabel* resetPositionCurKeyLabel;
	// QLabel* startStopTimeCurKeyLabel;

	// QPushButton* pitchUpSetButton;
	// QPushButton* pitchDownSetButton;
	// QPushButton* yawLeftSetButton;
	// QPushButton* yawRightSetButton;
	// QPushButton* rollLeftSetButton;
	// QPushButton* rollRightSetButton;
	// QPushButton* moveUpSetButton;
	// QPushButton* moveDownSetButton;
	// QPushButton* moveLeftSetButton;
	// QPushButton* moveRightSetButton;
	// QPushButton* moveForwardSetButton;
	// QPushButton* moveBackwardSetButton;
	// QPushButton* resetPositionSetButton;
	// QPushButton* startStopTimeSetButton;

	// bool nextKeyPressSetsAction;
	// KeyAction actionToSet;


	
	// QWidget* savePage;
	// QGridLayout* saveGrid;

	// QPushButton* saveStateButton;
	// QPushButton* selectStateFileDialogButton;
	// QLabel* saveStateFileNameLabel;
	
	QPushButton* loadStateButton;
	QPushButton* selectLoadStateFileDialogButton;
	QLabel* loadStateFileNameLabel;

	// QPushButton* startStartRecordingMovieButton; // ***** save movie
	// QPushButton* startStopRecordingAndSaveMovieButton; // ***** save movie
	// QPushButton* selectSaveMovieFileDialogButton;
	// QLabel* loadStateFileNameLabel;



	Integrator* integ; // To make system evolve.

};


#endif

