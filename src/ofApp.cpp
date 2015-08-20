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
    ofAddListener( stt.COMMAND_COMPLETE, this, &ofApp::sttCompleteHandler );
    
    gifPlayer.setLoopState(OF_LOOP_NORMAL);
    
    stt.recordAndConvert();
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
void ofApp::update()
{
    
    gifPlayer.update();
    timer.update( ) ;
}

//--------------------------------------------------------------
void ofApp::draw()
{    
    gifPlayer.draw(0, 0, screenWidth, screenHeight);
    
    
    ofSetColor(255, 255, 0);
    for(int i = 0; i < recognizedWords.size(); i++){
        ofDrawBitmapString(recognizedWords[i], 10, 10 + i * 14); //draw each lines of text 14 pixels bellow the other
    }
    
}

void ofApp::timerCompleteHandler( int &args )
{
    getImageForText("funny+cat");
    
}

void ofApp::sttCompleteHandler( int &args )
{
    ifstream fin;
    
    fin.open( ofToDataPath("stt.txt").c_str() );
    
    recognizedWords.clear();
    
    while(fin!=NULL)
    {
        string str;
        getline(fin, str);
        recognizedWords.push_back(str);
        
        remove(ofToDataPath("stt.txt").c_str());
    }
    
    
    
    stt.recordAndConvert();
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
