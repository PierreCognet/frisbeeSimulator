#ifndef PRJ_COMMANDWINDOW_H
#define PRJ_COMMANDWINDOW_H

#include <QtWidgets>
#include <QGridLayout>
#include "GLWidget.h"
#include "InfoWindow.h"
#include <map>

class GLWidget;
class InfoWindow;

enum KeyAction { pitchUp, pitchDown, yawLeft, yawRight, rollLeft, rollRight, moveUp, moveDown, moveLeft, moveRight, moveForward, moveBackward, resetPosition, startStopTime };


class CommandWindow : public QWidget {

Q_OBJECT

public :

	CommandWindow (QWidget *parent);

	bool getMappedAction(QKeyEvent* event, KeyAction& action);

private slots :

	void simulate();              // Needed to display and quit window (OpenGL).

	void setFrisbeeState();
	void toggleUvwBodyEarthAxes();

	// void saveFile();

	// void loadFile();

	// void quit();

	// void quit2();

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

private :

	int findBindedKey(KeyAction const& a);
	void refreshCurKeyLabels();

	// Methods for event handling. 
	virtual void keyPressEvent(QKeyEvent* event) override;


	QTabWidget *tabs;


	QWidget* masterPage;
	QGridLayout* masterGrid;


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
	QPushButton* stopButton;
	QPushButton* startButton;
	QPushButton* resetTimeButton;
	QSlider* playbackSpeedSlider;
	QLabel* playbackSpeedLabel;

	QGridLayout* integratorGrid;
	// QPushButton *boutonIntegrateurEuler;
	// QPushButton *boutonIntegrateurNewmark;
	QPushButton* rk4Button;
	QLabel* integratorLabel;



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
	// string saveStateFileName;
	
	QPushButton* loadStateButton;
	QPushButton* selectLoadStateFileDialogButton;
	QLabel* loadStateFileNameLabel;

	// *** add save movie file

	// *** add open movie file ? no actually in the other menu type




	

	// QPushButton* ClearTT;
	// QLineEdit* filename;
	// QLabel* infofile;

	// QPushButton *Del_Tissu;
	// QPushButton *Del_Contr;

	// QGridLayout *ChoixTissu;
	// QWidget *ChoixT;







	// QDoubleSpinBox* MasseGet ;
	// QDoubleSpinBox* MasseGet1;
	// QDoubleSpinBox* LambdaGet ;
	// QDoubleSpinBox* loGet  ;
	// QDoubleSpinBox* KGet  ;
	// QSpinBox* tailleGet;
	// QDoubleSpinBox* PasRadialGet;
	// QDoubleSpinBox* PasAngulaireGet;

	// QDoubleSpinBox* VecXGet ;
	// QDoubleSpinBox* VecYGet ;
	// QDoubleSpinBox* VecZGet ;
	// QDoubleSpinBox* VecXGet1 ;
	// QDoubleSpinBox* VecYGet1 ;
	// QDoubleSpinBox* VecZGet1 ;
	// QDoubleSpinBox* VecXGet2 ;
	// QDoubleSpinBox* VecYGet2 ;
	// QDoubleSpinBox* VecZGet2 ;

	// // For the popup window
	// QPushButton* create;
	// QPushButton* Compose;
	// QPushButton* pop;
	// QPushButton* Quit;

	// void tissuchaine();                 //Fonctions pour les champs variables
	// void tissuCarre();
	// void tissuHexagone();
	// void tissuDisque();
	// void tissuRectangle();
	// void tissulibre();
	// void tissuCarre2();
	// void tissuComp();




	// QGridLayout* ChoixContraintes;
	// QWidget* ChoixC;
	// QGridLayout* set;

	// QDoubleSpinBox* CentreGet1;
	// QDoubleSpinBox* CentreGet2;
	// QDoubleSpinBox* CentreGet3;
	// QDoubleSpinBox* RayonGet;
	// QDoubleSpinBox* GetTpDebut;
	// QDoubleSpinBox* GetTpFin;
	// QDoubleSpinBox* Force1;
	// QDoubleSpinBox* Force2;
	// QDoubleSpinBox* Force3;
	// QDoubleSpinBox* Freq;
	// QPushButton* CreateC;
	// QDialog* PopUp;
	// QSpinBox* massedep;
	// QSpinBox* massearr;



	// void crochet();
	// void Impulsion();
	// void Sinusoidale();
	// void levitateur();
	// void Boule();
	// void trounoir();

	// std::vector <Liaison> Liasons;
	// std::vector <Masse> Masses;
	// std::vector <Tissu*> Tissus;


	// void Init_champC();
	// void Init_champT(QGridLayout* Q);           //Pour un code plus comprehensible


	GLWidget* w;
	InfoWindow* infoWin; // Information window.


};


#endif

