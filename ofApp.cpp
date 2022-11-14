// Example 7: Background Subtraction
// This is ofApp.cpp
#include "ofApp.h"

//---------------------
void ofApp::setup(){
    vector<ofVideoDevice> devices = vidPlayer.listDevices();
        for(size_t i = 0; i < devices.size(); i++){
                if(devices[i].bAvailable){
                        //log the device
                        ofLogNotice() << devices[i].id << ": " << devices[i].deviceName;
                }else{
                        //log the device and note it as unavailable
                        ofLogNotice() << devices[i].id << ": " << devices[i].deviceName << " - unavailable ";
                }
        }

        vidPlayer.setDeviceID(0);
        vidPlayer.setDesiredFrameRate(30);
        vidPlayer.initGrabber(320,240);
       colorImg.allocate(320,240);
        grayImage.allocate(320,240);
        grayBg.allocate(320,240);
        grayDiff.allocate(320,240);

        bLearnBackground = true;
        thresholdValue = 80;
}

//---------------------
void ofApp::update(){

        // Ask the video player to update itself.
        vidPlayer.update();

        if (vidPlayer.isFrameNew()){ // If there is fresh data...

                // Copy the data from the video player into an ofxCvColorImage
                colorImg.setFromPixels(vidPlayer.getPixels());

                // Make a grayscale version of colorImg in grayImage
                grayImage = colorImg;

                // I it's time to learn the background;
                // copy the data from grayImage into grayBg
                if (bLearnBackground == true){
                        grayBg = grayImage; // Note: this is 'operator overloading'
                        bLearnBackground = false; // Latch: only learn it once.
                }

                // Take the absolute value of the difference
                // between the background and incoming images.
                grayDiff.absDiff(grayBg, grayImage);

                // Perform an in-place thresholding of the difference image.
                grayDiff.threshold(thresholdValue);

                // Find contours whose areas are betweeen 20 and 25000 pixels.
                // "Find holes" is true, so we'll also get interior contours.
                contourFinder.findContours(grayDiff, 20, 25000, 10, true);
        }
}

//---------------------
void ofApp::draw(){
        ofBackground(100,100,100);

        ofSetHexColor(0xffffff);
        colorImg.draw(20,20);    // The incoming color image
        grayImage.draw(360,20);  // A gray version of the incoming video
        grayBg.draw(20,280);     // The stored background image
        grayDiff.draw(360,280);  // The thresholded difference image

        ofNoFill();
        ofDrawRectangle(360,540,320,240);

        // Draw each blob individually from the blobs vector
        int numBlobs = contourFinder.nBlobs;
        for (int i=0; i<numBlobs; i++){
                contourFinder.blobs[i].draw(360,540);
        }
}

//---------------------
void ofApp::keyPressed(int key){
        bLearnBackground = true;
}
