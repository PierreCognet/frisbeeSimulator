#include "MainWindow.h"
#include "Playback.h"
#include "Visual3DWindow.h"
#include "InfoWindow.h"


// #include <QFileDialog>
#include <fstream>

using namespace std;

Playback::Playback(QWidget *parent, MainWindow* mw) : KeyActionWindow(parent, mw) {

	setWindowTitle("Movie Player");
	//setFixedSize(700, 500);
	setGeometry(0, 0 , 700, 500); // *** do something


	// Declare Widgets.
	timePage->setLayout(timeGrid);

	

	// mapKeyToAction(Qt::Key_N, oneFrameForward);
	// mapKeyToAction(Qt::Key_B, oneFrameBackward);
	// oneFrameForwardLabel = new QLabel("One frame forwards");
	// oneFrameBackwardLabel = new QLabel("One frame backwards");
	// keyboardGrid->addWidget(oneFrameForwardLabel, 16, 1);
	// keyboardGrid->addWidget(oneFrameBackwardLabel, 17, 1);

	possibleActions.push_back({ oneFrameForward,	Qt::Key_N, new QLabel("One frame forwards"),	new QLabel(""), new QPushButton("Set new key") });
	possibleActions.push_back({ oneFrameBackward,	Qt::Key_B, new QLabel("One frame backwards"),	new QLabel(""), new QPushButton("Set new key") });
	// *** Implement : tenFramesForward tenFramesBackward
	initKeyboardPage();




	loadMovieButton = new QPushButton("Load movie from file");
	selectLoadMovieFileDialogButton = new QPushButton("Select file location");
	loadMovieFileNameLabel = new QLabel("");



	saveGrid->addWidget(loadMovieButton, 4, 1, 1, 2);
	saveGrid->addWidget(selectLoadMovieFileDialogButton, 5, 1);
    saveGrid->addWidget(loadMovieFileNameLabel, 5, 2);
	QObject::connect(selectLoadMovieFileDialogButton, SIGNAL(clicked()), this, SLOT(selectLoadMovieFile()));
	QObject::connect(loadMovieButton, SIGNAL(clicked()), this, SLOT(loadMovie()));




	savePage->setLayout(saveGrid);



	// Fill the tabs.
	tabs->addTab(timePage, " Time");
	tabs->addTab(cameraPage, " Camera");
	tabs->addTab(keyboardPage, " Keyboard Bindings");
	tabs->addTab(savePage, " Save File");	

	movieCurIdx = 0;
	moviePlaybackTime = 0.;
}


Playback::~Playback() { 
	cerr << "Playback::~Playback()" << endl;
}



void Playback::selectLoadMovieFile() {
	loadMovieFileNameLabel->setText(QFileDialog::getOpenFileName(this,QString::fromLocal8Bit("Select movie file to load"),"",tr("Movie Files (*.movie)")));
}

void Playback::loadMovie() {
	try {
		string fileName (loadMovieFileNameLabel->text().toStdString());


		ifstream input(fileName);
		if (input.fail()) {
			throw string("Visual3DWindow::loadState(...)  impossible to load '"+fileName+"' in read mode");
		}
		
		if (input.is_open()) {

			try {

				string tmp;
				if (!getline(input, tmp)) { throw string("Playback::loadMovie() loaded movie file has 0 lines instead of 2 or more'"); }
				if (input.eof()) { throw string("Playback::loadMovie() loaded movie file 1 line instead of 2 or more"); }
				movieHeadersLine = tmp;
				movieValueLines.clear();
				while(getline(input, tmp)) {
					movieValueLines.push_back(tmp);
				}
				movieCurIdx = 0;

				// *** verify that all the lines are correct ? then get rid of tmp ?

				loadMovieFrameToSys();
				moviePlaybackTime = sys->time();

			} catch (std::string s) {
			    QMessageBox::information(this, "Exception caught", QString::fromStdString(s));
			} catch (const std::exception& e) {
			    QMessageBox::information(this, "Exception caught", QString::fromStdString(e.what()));
			}

			input.close();
		}


	}catch (std::string s) {
		QMessageBox::information(this, "Problem", QString::fromStdString(s));}
}


bool Playback::executeAction(KeyAction action) { // Returns true if an action has been executed.
	// Improvement : using function pointeers directly in the possibleActions structure

	if (KeyActionWindow::executeAction(action)) { // Check whether is one of the common actions.
		return true;
	} else {
		// If not one of common actions, look for specific actions.
		if (action==oneFrameForward) {
			if (movieCurIdx+1<movieValueLines.size()) {
				movieCurIdx++;
				loadMovieFrameToSys();
				moviePlaybackTime = sys->time();
			}
		} else if (action==oneFrameBackward) {
			if (movieCurIdx>0) {
				movieCurIdx--;
				loadMovieFrameToSys();
				moviePlaybackTime = sys->time();
			}
		} else {
			return false;
		}
		return true;
	}
}

void Playback::timerEvent(QTimerEvent* event) {

	Q_UNUSED(event);

	if (movieCurIdx+1 >= movieValueLines.size()) { // If end of movie reached.
		toggleChrono();
		return;
	}

	double coef;
	if (playbackSpeed < 50) { // 0 < playbackSpeed < 50 means slower than normal, so make smaller time steps.
		coef = playbackSpeed/50.; // Linear function of playbackSpeed, passes through (0,0) and (50,1).
	}
	else { // 50 < playbackSpeed < 100 means faster than normal.
		coef = playbackSpeed*(5./50.)-4.; // Linear function of playbackSpeed, passes through (50,1) and (100,6). This means that at maximal "playbackSpeed=100" the simulation is 6 times normal speed.
	}


	double dt = chronometer.restart()/1000.;
	moviePlaybackTime += dt*coef;

	bool done = false;
	bool idxHasChanged = false;
	while(!done) {
		double nextFrameTime = sys->time(movieValueLines[movieCurIdx+1]);
		if (moviePlaybackTime<nextFrameTime) {
			done = true;
		} else {
			movieCurIdx+=1;
			idxHasChanged = true;
			if (movieCurIdx+1==movieValueLines.size()) {
				done = true;
				moviePlaybackTime = nextFrameTime;
			}
		}
	}

	if (idxHasChanged) {
		loadMovieFrameToSys();
	}
}



void Playback::closeEvent(QCloseEvent* event) {
	cerr << "Playback::closeEvent(QCloseEvent* event)" << endl;
	parent->playbackIsClosing();
	event->accept();
}


void Playback::loadMovieFrameToSys() {
	try {
		System* tmpSyst ( new System(v3dw->getView(), movieHeadersLine, movieValueLines[movieCurIdx]) ); // Create new system. Note that this process can fail if there are format errors.
		delete sys;	// If successfully loaded, delete and replace the old System.
		sys = tmpSyst;	//on garde le nouveau
		
		if (frisbeeTrackingCameraMode) { v3dw->lookAt(sys); }
		v3dw->updateGL();
		infoWin->refreshLabels(sys);
	} catch (std::string s) {
	    QMessageBox::information(this, "Exception caught", QString::fromStdString(s));
	} catch (const std::exception& e) {
	    QMessageBox::information(this, "Exception caught", QString::fromStdString(e.what()));
	}
}





