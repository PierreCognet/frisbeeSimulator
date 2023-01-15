#include "MainWindow.h"
#include <QString>
#include "Integrator.h"
// #include "IntegrateurEuler.h"
#include "OpenGLViewer.h"
#include <QFileDialog>
// #include "NonVisualSimulation.h"
#include "VisualSimulation.h"
// #include "Playback.h"



MainWindow::MainWindow(QWidget *parent) : QWidget(parent) {


	setWindowTitle("Main Window");
	//setFixedSize(700, 500);
	setGeometry(0, 0 , 700, 500);


	// nonVisualSimulationButton = new QPushButton("Open non visual simulation mode");
	visualSimulationButton = new QPushButton("Open visual simulation mode");
	// playbackButton = new QPushButton("Open playback mode");

	mainGrid = new QGridLayout;
	// mainGrid->addWidget(nonVisualSimulationButton, 1, 1);
	mainGrid->addWidget(visualSimulationButton, 1, 1);
	// mainGrid->addWidget(playbackButton, 2, 1);

	this->setLayout(mainGrid);


	// QObject::connect(nonVisualSimulationButton, SIGNAL(clicked()), this, SLOT(startNonVisualSimulation()));
	QObject::connect(visualSimulationButton, SIGNAL(clicked()), this, SLOT(startVisualSimulation()));
	// QObject::connect(playbackButton, SIGNAL(clicked()), this, SLOT(startPlayback()));
}




// void MainWindow::startNonVisualSimulation() { ... }
// void MainWindow::nonVisualSimulationIsClosing() { ... }

void MainWindow::startVisualSimulation() {
	if (vs==nullptr) {	
		vs = new VisualSimulation(this, this);
		vs->setWindowFlags(Qt::Dialog | Qt::WindowTitleHint);
		// QObject::connect(vs, SIGNAL(finished(int)), vs, SLOT(deleteLater()));
		// QObject::connect(vs, SIGNAL(closeEvent(int)), this, SLOT(visualSimulationIsClosing()));
		// vs->setGeometry(1100 , 0, 1200 , 1055 ); // *** delete this ? no fixed size ? or a percentage of screen size 
		vs->show();



		// *** use this on the sub windows to
		// void MainWindow::closeEvent(QCloseEvent* event) {
		// 	emit MySignalToIndicateThatTheWindowIsClosing();    (which makes it point to nullptr)
		// 	event->accept();
		// }

		// or
		// ***
		// ChildWindow * d = new ChildWindow(this);
		// connect(d, SIGNAL(finished(int)), d, SLOT(deleteLater()));
		// d->show();
	}
}

void MainWindow::visualSimulationIsClosing() {
	// vs->deleteLater() // no need because it is connected to the finished slot
	vs->deleteLater();
	vs = nullptr;
	cerr << "MainWindow::visualSimulationIsClosing()" << endl;
}


// void MainWindow::startPlayback() {
// 	if (pb==nullptr) {	
// 		pb = new Playback(this);
// 		pb->setWindowFlags(Qt::Dialog | Qt::WindowTitleHint);
// 		QObject::connect(pb, SIGNAL(finished(int)), pb, SLOT(deleteLater()));
// 		// pb->setGeometry(1100 , 0, 1200 , 1055 ); // *** delete this ? no fixed size ? or a percentage of screen size 
// 		pb->show();
// 	}
// }

// void MainWindow::playbackIsClosing() {
// 	// pb->deleteLater() // no need because it is connected to the finished slot
// 	pb = nullptr;
// }
