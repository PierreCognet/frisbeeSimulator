#ifndef PRJ_VISUALSIMULATION_H
#define PRJ_VISUALSIMULATION_H

#include "KeyActionWindow.h"
#include "MovieRecorder.h"

class Integrator;


class VisualSimulation : public KeyActionWindow  {

Q_OBJECT

public :

	VisualSimulation (QWidget* parent, MainWindow* mw);
	virtual ~VisualSimulation();  // Delete dyamically allocated system and integrator.
	
	// *** virtual void visual3DWindowKeyPressEvent(QKeyEvent* event) override;

	// IntegratorType getIntegratorType() { return integ->getType(); }

private slots :

	void setFrisbeeState();
	void toggleUvwBodyEarthAxes();

	void selectLoadStateFile();
	void loadState();

	void selectMovieFile();
	void beginRecordMovie();
	void endRecordMovie();

	// void set_Euler();
	// void set_Newmark();
	void setRK4();
	void resetTime();


private :

	virtual bool executeAction(KeyAction action) override; // Returns true if an action has been executed.

	virtual void timerEvent(QTimerEvent* event) override;
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
	Integrator* integ; // To make system evolve.

	
	QPushButton* loadStateButton;
	QPushButton* selectLoadStateFileDialogButton;
	QLabel* loadStateFileNameLabel;

	QPushButton* beginRecordMovieButton;
	QPushButton* endRecordMovieButton;
	QPushButton* selectMovieFileDialogButton;
	QLabel* movieFileNameLabel;
	MovieRecorder mr;

};


#endif

