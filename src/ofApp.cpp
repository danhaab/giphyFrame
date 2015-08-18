#include "ofApp.h"

int frame = 0;
//--------------------------------------------------------------
void ofApp::setup(){
    decoder.decode("giphy.gif");
    file = decoder.getFile();
    
    lastUpdate = ofGetElapsedTimef();
    
    float numFrames = file.getNumFrames();

    duration = file.getDuration();
    
    frameRate =  duration /numFrames ;
    
    screenHeight = ofGetScreenHeight();
    screenWidth = ofGetScreenWidth();
    
}

//--------------------------------------------------------------
void ofApp::update(){
    
    float currentTime = ofGetElapsedTimef();
    
    if (currentTime > (lastUpdate + duration))
    {
        lastUpdate = currentTime;
        frame++;
    }

    if (frame > file.getNumFrames())
        frame=0;
}

//--------------------------------------------------------------
void ofApp::draw(){
    
    file.drawFrame(frame, 0, 0, screenWidth, screenHeight);
    
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){

}

//--------------------------------------------------------------
void ofApp::keyReleased(int key){

}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y ){

}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::windowResized(int w, int h){

}

//--------------------------------------------------------------
void ofApp::gotMessage(ofMessage msg){

}

//--------------------------------------------------------------
void ofApp::dragEvent(ofDragInfo dragInfo){ 

}
