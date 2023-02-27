#ifndef PRJ_KEYACTIONWINDOW_H
#define PRJ_KEYACTIONWINDOW_H

#include <QtWidgets>
#include <QGridLayout>

enum KeyAction { pitchUp, pitchDown, yawLeft, yawRight, rollLeft, rollRight, moveUp, moveDown, moveLeft, moveRight, moveForward, moveBackward, resetPosition, startStopTime, oneFrameForward, oneFrameBackward };

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
	virtual ~KeyActionWindow(); // Delete dyamically allocated system and integrator.

	System* getSystem() { return sys; }
	
	// double getCurrentTime();
	void stop();
	virtual void visual3DWindowKeyPressEvent(QKeyEvent* event);

protected slots :
	void setNewAction(int i);

	void selectSaveCurrentStateFile();
	void saveCurrentState();

	void toggleFrisbeeTrackingCameraMode();

	void setPlaybackSpeed(int a);

protected :

	virtual bool executeAction(KeyAction action); // Returns true if an action has been executed.

	void initKeyboardPage();
	// virtual void timerEvent(QTimerEvent* event) override;
	virtual void keyPressEvent(QKeyEvent* event) override;
	// void closeEvent(QCloseEvent* event); // do virtual = 0 ? to make sure that the main window deletes me ? 


	QTabWidget *tabs;



	QWidget* timePage;
	QGridLayout* timeGrid;

	QPushButton* startStopButton;
	QSlider* playbackSpeedSlider;
	QLabel* playbackSpeedLabel;



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

	
	struct keyActionsStruct {
		KeyAction action;
		int key;
		QLabel* nameLabel;
		QLabel* currentKeyLabel;
		QPushButton* setNewKeyButton;
	};

	std::vector<keyActionsStruct> possibleActions;

	bool nextKeyPressSetsAction;
	KeyAction actionToSet;


	
	QWidget* savePage;
	QGridLayout* saveGrid;

	QPushButton* saveStateButton;
	QPushButton* selectStateFileDialogButton;
	QLabel* saveStateFileNameLabel;

	bool getMappedAction(QKeyEvent* event, KeyAction& action);
	bool remapKeyToAction(int key, KeyAction& action);



	Visual3DWindow* v3dw; // 3D visualalization window.  
	InfoWindow* infoWin; // Information window on current state (frisbee position, integrator type, etc).
	
	System* sys; // Objects to draw and make evolve.

	int timerId; // Timer.
	QTime chronometer; // To make objects evolve at the correct time step.
	double playbackSpeed; // To change the speed at which time flows (multiplier).

	bool frisbeeTrackingCameraMode;


	MainWindow* parent;
};


#endif

