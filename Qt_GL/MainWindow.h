#ifndef PRJ_MAINWINDOW_H
#define PRJ_MAINWINDOW_H

#include <QtWidgets>
#include <QGridLayout>
// #include "NonVisualSimulation.h"
#include "VisualSimulation.h"
// #include "Playback.h"


// class NonVisualSimulation;
class VisualSimulation;
// class Playback;


class MainWindow : public QWidget {

Q_OBJECT

public :

	MainWindow (QWidget *parent);

	// void nonVisualSimulationIsClosing();
	void visualSimulationIsClosing();
	// void playbackIsClosing();


private slots :
	// void startNonVisualSimulation();
	void startVisualSimulation();
	// void startPlayback();


private :

	QGridLayout* mainGrid;

	// QPushButton* nonVisualSimulationButton;
	QPushButton* visualSimulationButton;
	// QPushButton* playbackButton;


	// NonVisualSimulation* nvs;
	VisualSimulation* vs;
	// Playback* pb;
};


#endif

