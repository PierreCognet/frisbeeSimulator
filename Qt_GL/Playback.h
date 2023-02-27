#ifndef PRJ_PLAYBACK_H
#define PRJ_PLAYBACK_H

#include "KeyActionWindow.h"

class Playback : public KeyActionWindow  {

Q_OBJECT

public :

	Playback (QWidget* parent, MainWindow* mw);
	virtual ~Playback();  // Delete dyamically allocated system and integrator.
	
	// *** virtual void visual3DWindowKeyPressEvent(QKeyEvent* event) override;

private slots :

	void selectLoadMovieFile();
	void loadMovie();

	// void resetTime();


private :

	virtual bool executeAction(KeyAction action) override; // Returns true if an action has been executed.

	virtual void timerEvent(QTimerEvent* event) override;
	void closeEvent(QCloseEvent* event);

	void loadMovieFrameToSys();


	// QLabel* oneFrameForwardLabel;
	// QLabel* oneFrameBackwardLabel;
	// QLabel* oneFrameForwardCurKeyLabel;
	// QLabel* oneFrameBackwardCurKeyLabel;
	// QPushButton* oneFrameForwardSetButton;
	// QPushButton* oneFrameBackwardSetButton;


	QPushButton* loadMovieButton;
	QPushButton* selectLoadMovieFileDialogButton;
	QLabel* loadMovieFileNameLabel;

	std::string movieHeadersLine;
	std::vector<std::string> movieValueLines;
	size_t movieCurIdx; // Idx within the vector movieValueLines.
	double moviePlaybackTime;

};


#endif

