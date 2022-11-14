// Example 7: Background Subtraction 
// This is ofApp.h

#pragma once
#include "ofMain.h"
#include "ofxOpenCv.h"

class ofApp : public ofBaseApp{
	public:
		void setup();
		void update();
		void draw();
		void keyPressed(int key);
	
		ofVideoGrabber			vidPlayer;
	
		ofxCvColorImage			colorImg;
		ofxCvGrayscaleImage 	grayImage;
		ofxCvGrayscaleImage 	grayBg;
		ofxCvGrayscaleImage 	grayDiff;
		ofxCvContourFinder		contourFinder;

		int						thresholdValue;
		bool					bLearnBackground;
};
