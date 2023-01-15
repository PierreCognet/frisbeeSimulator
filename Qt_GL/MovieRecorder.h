#ifndef PRJ_MOVIERECORDER_H
#define PRJ_MOVIERECORDER_H

#include <string>
#include <fstream>

class System;

using namespace std;

class MovieRecorder {
	
	public:
		MovieRecorder();
		~MovieRecorder();
		
		bool isRecording();
		
		void beginRecording(string const& fileName_, System* sys);
		string endRecording();
		void addFrame(System* sys);

	private:
		void writeTmpMovieToFile();

		bool isRecording_;

		ofstream output;
		string fileName;

		unsigned int lineCount;
		string tmpMovie; // Writing to file is slow, so only do it every ?100? frames.
};


#endif
