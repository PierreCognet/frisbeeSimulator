#ifndef PRJ_KEYACTIONWINDOW_H
#define PRJ_KEYACTIONWINDOW_H

#include <QtWidgets>
#include <QGridLayout>
#include <map>

enum KeyAction { pitchUp, pitchDown, yawLeft, yawRight, rollLeft, rollRight, moveUp, moveDown, moveLeft, moveRight, moveForward, moveBackward, resetPosition, startStopTime };

class MainWindow;
class System;
class Visual3DWindow;
class InfoWindow;

class KeyActionWindow : public QWidget {

Q_OBJECT

public slots :
	void toggleChrono();

public :

	KeyActionWindow (QWidget* parent, MainWindow* mw);
	virtual ~KeyActionWindow();  // Delete dyamically allocated system and integrator.

	// bool getMappedAction(QKeyEvent* event, KeyAction& action); // ***** deleted

	System* getSystem() { return sys; }
	
	// double getCurrentTime();
	void stop();
	virtual void visual3DWindowKeyPressEvent(QKeyEvent* event) = 0;

protected slots :

	void pitchUpSetNew();
	void pitchDownSetNew();
	void yawLeftSetNew();
	void yawRightSetNew();
	void rollLeftSetNew();
	void rollRightSetNew();
	void moveUpSetNew();
	void moveDownSetNew();
	void moveLeftSetNew();
	void moveRightSetNew();
	void moveForwardSetNew();
	void moveBackwardSetNew();
	void resetPositionSetNew();
	void startStopTimeSetNew();

	void selectSaveCurrentStateFile();
	void saveCurrentState();

	void toggleFrisbeeTrackingCameraMode();

	void setPlaybackSpeed(int a);
	// void resetTime();


protected :

	// int findBindedKey(KeyAction const& a); // ***** deleted
	void refreshCurKeyLabels();
	// virtual void timerEvent(QTimerEvent* event) override;
	virtual void keyPressEvent(QKeyEvent* event) override;
	// void closeEvent(QCloseEvent* event);




	QTabWidget *tabs;



	// QWidget* frisbeePage;
	// QGridLayout* frisbeeGrid;

	// QDoubleSpinBox* xSpinBox;
	// QDoubleSpinBox* ySpinBox;
	// QDoubleSpinBox* zSpinBox;
	// QDoubleSpinBox* phiSpinBox;
	// QDoubleSpinBox* thetaSpinBox;
	// QDoubleSpinBox* psiSpinBox;
	// QDoubleSpinBox* uSpinBox;
	// QDoubleSpinBox* vSpinBox;
	// QDoubleSpinBox* wSpinBox;
	// QDoubleSpinBox* pSpinBox;
	// QDoubleSpinBox* qSpinBox;
	// QDoubleSpinBox* rSpinBox;

	// QLabel* xLabel;
	// QLabel* yLabel;
	// QLabel* zLabel;
	// QLabel* phiLabel;
	// QLabel* thetaLabel;
	// QLabel* psiLabel;
	// QLabel* uLabel;
	// QLabel* vLabel;
	// QLabel* wLabel;
	// QLabel* pLabel;
	// QLabel* qLabel;
	// QLabel* rLabel;

	// QPushButton* setFrisbeeStateButton;
	// QPushButton* toggleUvwBodyEarthAxesButton;
	// bool uvwIsBodyNotEarthAxes;



	QWidget* timePage;
	QGridLayout* timeGrid;

	QPushButton* startStopButton;
	// QPushButton* resetTimeButton;
	QSlider* playbackSpeedSlider;
	QLabel* playbackSpeedLabel;

	// QGridLayout* integratorGrid;
	// QLabel* integratorLabel;
	// // QPushButton *boutonIntegrateurEuler;
	// // QPushButton *boutonIntegrateurNewmark;
	// QPushButton* rk4Button;



	QWidget* cameraPage;
	QGridLayout* cameraGrid;

	QLabel* camPositionTitle;
	QPushButton* zButton;
	QPushButton* zzButton;
	QPushButton* xButton;
	QPushButton* xxButton;
	QPushButton* yButton;
	QPushButton* yyButton;
	QPushButton* toggleFrisbeeTrackingCameraModeButton;
	


	QWidget* keyboardPage;
	QGridLayout* keyboardGrid;

    QLabel* actionTitleLabel;
    QLabel* currentKeyTitleLabel;
    QLabel* setNewKeyTitleLabel;
	// vector<QLabel*> actionLabels; // std:: ?
	// vector<QLabel*> currentKeyLabels; // std:: ?
	// vector<QPushButton*> setNewKeyButtons; // std:: ?

	QLabel* pitchUpLabel;
	QLabel* pitchDownLabel;
	QLabel* yawLeftLabel;
	QLabel* yawRightLabel;
	QLabel* rollLeftLabel;
	QLabel* rollRightLabel;
	QLabel* moveUpLabel;
	QLabel* moveDownLabel;
	QLabel* moveLeftLabel;
	QLabel* moveRightLabel;
	QLabel* moveForwardLabel;
	QLabel* moveBackwardLabel;
	QLabel* resetPositionLabel;
	QLabel* startStopTimeLabel;

	QLabel* pitchUpCurKeyLabel;
	QLabel* pitchDownCurKeyLabel;
	QLabel* yawLeftCurKeyLabel;
	QLabel* yawRightCurKeyLabel;
	QLabel* rollLeftCurKeyLabel;
	QLabel* rollRightCurKeyLabel;
	QLabel* moveUpCurKeyLabel;
	QLabel* moveDownCurKeyLabel;
	QLabel* moveLeftCurKeyLabel;
	QLabel* moveRightCurKeyLabel;
	QLabel* moveForwardCurKeyLabel;
	QLabel* moveBackwardCurKeyLabel;
	QLabel* resetPositionCurKeyLabel;
	QLabel* startStopTimeCurKeyLabel;

	QPushButton* pitchUpSetButton;
	QPushButton* pitchDownSetButton;
	QPushButton* yawLeftSetButton;
	QPushButton* yawRightSetButton;
	QPushButton* rollLeftSetButton;
	QPushButton* rollRightSetButton;
	QPushButton* moveUpSetButton;
	QPushButton* moveDownSetButton;
	QPushButton* moveLeftSetButton;
	QPushButton* moveRightSetButton;
	QPushButton* moveForwardSetButton;
	QPushButton* moveBackwardSetButton;
	QPushButton* resetPositionSetButton;
	QPushButton* startStopTimeSetButton;

	bool nextKeyPressSetsAction;
	KeyAction actionToSet;


	
	QWidget* savePage;
	QGridLayout* saveGrid;

	QPushButton* saveStateButton;
	QPushButton* selectStateFileDialogButton;
	QLabel* saveStateFileNameLabel;
	
	// QPushButton* loadStateButton;
	// QPushButton* selectLoadStateFileDialogButton;
	// QLabel* loadStateFileNameLabel;

	// QPushButton* loadMovieButton;
	// QPushButton* selectLoadMovieFileDialogButton;
	// QLabel* loadMovieFileNameLabel;


	std::map<int, KeyAction> keyActionMap; // For each key, maps to the corresponding action. Would be cleaner to use Qt::Key, as key type. // ***** deleted
	// KeyActionMapper kam; // For each key, maps to the corresponding action. Would be cleaner to use Qt::Key, as key type. // ***** added
	bool mapKeyToAction(int key, KeyAction action);
	bool getMappedAction(QKeyEvent* event, KeyAction& action);
	int findBindedKey(KeyAction const& a);
	bool remapKeyToAction(int key, KeyAction& action);



	Visual3DWindow* v3dw; // 3D visualalization window.  
	InfoWindow* infoWin; // Information window on current state (frisbee position, integrator type, etc).
	
	System* sys; // Objects to draw and make evolve.
	// Integrator* integ; // To make system evolve.

	int timerId; // Timer.
	QTime chronometer; // To make objects evolve at the correct time step.
	double playbackSpeed; // To change the speed at which time flows (multiplier).

	bool frisbeeTrackingCameraMode;


	MainWindow* parent;
};


#endif

