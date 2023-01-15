#include "MovieRecorder.h"
#include "System.h"


MovieRecorder::MovieRecorder() : isRecording_(false) { }

MovieRecorder::~MovieRecorder() {
	if (isRecording_) {
		endRecording();
	}
}

bool MovieRecorder::isRecording() {
	return isRecording_;
}

void MovieRecorder::beginRecording(string const& fileName_, System* sys) {
	fileName = fileName_;
	output = ofstream(fileName); // Open flow.
	if (output.fail()) {
		throw string("MovieRecorder::beginRecording(...)  impossible to open '"+fileName+"' in write mode");
	}

	isRecording_ = true;
	lineCount = 0;
	tmpMovie = sys->getHeaders();
	addFrame(sys);
}

string MovieRecorder::endRecording() {
	writeTmpMovieToFile();
	output.close();
	isRecording_ = false;
	return fileName;
}

void MovieRecorder::addFrame(System* sys) {
	tmpMovie += '\n'+sys->getCurrentState();
	lineCount++;
	if (lineCount>100) {
		writeTmpMovieToFile();
	}
}

void MovieRecorder::writeTmpMovieToFile() {
	output << tmpMovie;
	lineCount = 0;	
	tmpMovie = "";	
}
