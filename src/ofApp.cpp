#include "ofApp.h"

int frame = 0;
//--------------------------------------------------------------
void ofApp::setup()
{
    
    getImageForText("funny+cat");
    
    lastUpdate = ofGetElapsedTimef();
    
    screenHeight = ofGetScreenHeight();
    screenWidth = ofGetScreenWidth();

    timer.setup( 15000 );
    timer.start( true ) ;
    
    ofAddListener( timer.TIMER_COMPLETE , this, &ofApp::timerCompleteHandler ) ;
    
    gifPlayer.setLoopState(OF_LOOP_NORMAL);
}

void ofApp::getImageForText (string query)
{
    string url = "http://api.giphy.com/v1/gifs/search?q=";
    
    url += query;
    
    url += "&api_key=dc6zaTOxFJmzC";

    ofxJSONElement response;
    
    if (!response.open(url))
    {
        ofLogNotice("ofApp::setup") << "Failed to parse JSON";
    }

    int numImages = response["data"].size();
    
    if (numImages > 0)
    {
        int selection = ofRandom(0, numImages-1);
        
        string imageUrl = response["data"][selection]["images"]["original"]["mp4"].asString();
        
        if (imageUrl.empty())
            return;
        
        gifPlayer.loadMovie(imageUrl);
        
        gifPlayer.play();
        
    }

    
}

//--------------------------------------------------------------
void ofApp::update(){
    
    gifPlayer.update();
    
    float currentTime = ofGetElapsedTimef();
    
    if (currentTime > (lastUpdate + duration))
    {
        lastUpdate = currentTime;
        frame++;
    }

    if (frame > file.getNumFrames()-1)
        frame=0;
    
    timer.update( ) ;
}

//--------------------------------------------------------------
void ofApp::draw(){
    
    //file.drawFrame(frame, 0, 0, screenWidth, screenHeight);
    
    gifPlayer.draw(0, 0, screenWidth, screenHeight);
    
}

void ofApp::timerCompleteHandler( int &args )
{
    getImageForText("funny+cat");
    
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
