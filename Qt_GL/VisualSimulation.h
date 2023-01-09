#ifndef PRJ_VISUALSIMULATION_H
#define PRJ_VISUALSIMULATION_H

#include <QtWidgets>
#include <QGridLayout>
#include <QTime>
#include "MainWindow.h"
#include "Visual3DWindow.h"
#include "InfoWindow.h"
#include <map>

class MainWindow;
class Visual3DWindow;
class InfoWindow;

enum KeyAction { pitchUp, pitchDown, yawLeft, yawRight, rollLeft, rollRight, moveUp, moveDown, moveLeft, moveRight, moveForward, moveBackward, resetPosition, startStopTime };


class VisualSimulation : public QWidget {

Q_OBJECT

public slots :
	void toggleTime();

public :

	VisualSimulation (QWidget* parent, MainWindow* mw);
	virtual ~VisualSimulation();  // Delete dyamically allocated system and integrator.

	bool getMappedAction(QKeyEvent* event, KeyAction& action);

	System* getSystem() { return sys; }
	

	IntegratorType getIntegratorType() { return integ->getType(); }
	const Vector3 getFrisbeePosition() const;
	double getCurrentTime();
	void stop();

private slots :

	void setFrisbeeState();
	void toggleUvwBodyEarthAxes();

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
	void selectLoadStateFile();
	void loadState();

	void toggleFrisbeeTrackingCameraMode();

	// void set_Euler();
	// void set_Newmark();	
	void setRK4();
	void setPlaybackSpeed(int a);
	void resetTime();


private :

	int findBindedKey(KeyAction const& a);
	void refreshCurKeyLabels();
	virtual void timerEvent(QTimerEvent* event)  override;
	virtual void keyPressEvent(QKeyEvent* event) override;
	void closeEvent(QCloseEvent* event);




	QTabWidget *tabs;



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



	QWidget* timePage;
	QGridLayout* timeGrid;

	QPushButton* startStopButton;
	QPushButton* resetTimeButton;
	QSlider* playbackSpeedSlider;
	QLabel* playbackSpeedLabel;

	QGridLayout* integratorGrid;
	QLabel* integratorLabel;
	// QPushButton *boutonIntegrateurEuler;
	// QPushButton *boutonIntegrateurNewmark;
	QPushButton* rk4Button;



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

	std::map<int, KeyAction> keyActionMap; // For each key, maps to the corresponding action. Would be cleaner to use Qt::Key, as key type.
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
	
	QPushButton* loadStateButton;
	QPushButton* selectLoadStateFileDialogButton;
	QLabel* loadStateFileNameLabel;



	Visual3DWindow* v3dw; // 3D visualalization window.  
	InfoWindow* infoWin; // Information window on current state (frisbee position, inteegrator type, etc).
	
	System* sys; // Objects to draw and make evolve.
	Integrator* integ; // To make system evolve.

	int timerId; // Timer.
	QTime chronometer; // To make objects evolve at the correct time step.
	double playbackSpeed; // To change the speed at which time flows (multiplier).

	bool frisbeeTrackingCameraMode;


	MainWindow* parent;
};


#endif

